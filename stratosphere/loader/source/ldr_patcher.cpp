/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stratosphere.hpp>
#include "ldr_patcher.hpp"
#include "ldr_pcv_patch.hpp"

namespace ams::ldr {

    namespace {

        constexpr u8 PcvModuleId[0x20] = {
            /* 11.0.0 */
            //0x91, 0xD6, 0x1D, 0x59, 0xD7, 0x00, 0x23, 0x78, 0xE3, 0x55, 0x84, 0xFC, 0x0B, 0x38, 0xC7, 0x69,
            //0x3A, 0x3A, 0xBA, 0xB5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

            /* 12.0.0 */
            0xC5, 0x03, 0xE9, 0x65, 0x50, 0xF3, 0x02, 0xE1, 0x21, 0x87, 0x31, 0x36, 0xB8, 0x14, 0xA5, 0x29,
            0x86, 0x3D, 0x94, 0x9B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };

        constexpr const char *NsoPatchesDirectory = "exefs_patches";

        /* Exefs patches want to prevent modification of header, */
        /* and also want to adjust offset relative to mapped location. */
        constexpr size_t NsoPatchesProtectedSize   = sizeof(NsoHeader);
        constexpr size_t NsoPatchesProtectedOffset = sizeof(NsoHeader);

        constexpr const char * const LoaderSdMountName = "#amsldr-sdpatch";
        static_assert(sizeof(LoaderSdMountName) <= fs::MountNameLengthMax);

        constinit os::SdkMutex g_ldr_sd_lock;
        constinit bool g_mounted_sd;

        constinit os::SdkMutex g_embedded_patch_lock;
        constinit bool g_got_embedded_patch_settings;
        constinit bool g_force_enable_usb30;

        bool EnsureSdCardMounted() {
            std::scoped_lock lk(g_ldr_sd_lock);

            if (g_mounted_sd) {
                return true;
            }

            if (!cfg::IsSdCardInitialized()) {
                return false;
            }

            if (R_FAILED(fs::MountSdCard(LoaderSdMountName))) {
                return false;
            }

            return (g_mounted_sd = true);
        }

        bool IsUsb30ForceEnabled() {
            std::scoped_lock lk(g_embedded_patch_lock);

            if (!g_got_embedded_patch_settings) {
                g_force_enable_usb30 = spl::IsUsb30ForceEnabled();
                g_got_embedded_patch_settings = true;
            }

            return g_force_enable_usb30;
        }

        consteval u8 ParseNybble(char c) {
            AMS_ASSUME(('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f'));
            if ('0' <= c && c <= '9') {
                return c - '0' + 0x0;
            } else if ('A' <= c && c <= 'F') {
                return c - 'A' + 0xA;
            } else /* if ('a' <= c && c <= 'f') */ {
                return c - 'a' + 0xa;
            }
        }

        consteval ro::ModuleId ParseModuleId(const char *str) {
            /* Parse a static module id. */
            ro::ModuleId module_id = {};

            size_t ofs = 0;
            while (str[0] != 0) {
                AMS_ASSUME(ofs < sizeof(module_id));
                AMS_ASSUME(str[1] != 0);

                module_id.build_id[ofs] = (ParseNybble(str[0]) << 4) | (ParseNybble(str[1]) << 0);

                str += 2;
                ofs++;
            }

            return module_id;
        }

        struct EmbeddedPatchEntry {
            uintptr_t offset;
            const void * const data;
            size_t size;
        };

        struct EmbeddedPatch {
            ro::ModuleId module_id;
            size_t num_entries;
            const EmbeddedPatchEntry *entries;
        };

        #include "ldr_embedded_usb_patches.inc"

    }

    /* Apply IPS patches. */
    void LocateAndApplyIpsPatchesToModule(const u8 *build_id, uintptr_t mapped_nso, size_t mapped_size) {
        if (!EnsureSdCardMounted()) {
            return;
        }

        ro::ModuleId module_id;
        std::memcpy(&module_id.build_id, build_id, sizeof(module_id.build_id));
        ams::patcher::LocateAndApplyIpsPatchesToModule(LoaderSdMountName, NsoPatchesDirectory, NsoPatchesProtectedSize, NsoPatchesProtectedOffset, &module_id, reinterpret_cast<u8 *>(mapped_nso), mapped_size);
    }

    /* Apply embedded patches. */
    void ApplyEmbeddedPatchesToModule(const u8 *build_id, uintptr_t mapped_nso, size_t mapped_size) {
        /* Make module id. */
        ro::ModuleId module_id;
        std::memcpy(&module_id.build_id, build_id, sizeof(module_id.build_id));

        if (IsUsb30ForceEnabled()) {
            for (const auto &patch : Usb30ForceEnablePatches) {
                if (std::memcmp(std::addressof(patch.module_id), std::addressof(module_id), sizeof(module_id)) == 0) {
                    for (size_t i = 0; i < patch.num_entries; ++i) {
                        const auto &entry = patch.entries[i];
                        if (entry.offset + entry.size <= mapped_size) {
                            std::memcpy(reinterpret_cast<void *>(mapped_nso + entry.offset), entry.data, entry.size);
                        }
                    }
                }
            }
        }

        if (std::memcmp(PcvModuleId, build_id, sizeof(PcvModuleId)) == 0) {
            ApplyPcvPatch(reinterpret_cast<u8 *>(mapped_nso), mapped_size);
            return;
        }
    }

}