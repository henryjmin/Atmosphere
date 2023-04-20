#include <stratosphere.hpp>
#include "ldr_pcv_patch.hpp"

namespace ams::ldr {
    namespace {
        struct OffsetList {
            u8 offset_count;
            u32 offsets[34];
        };

        struct PcvOffsetEntry {
            bool MarikoSupported;

            /* Common */
            OffsetList EmcFreqOffsets;
            u32 EmcPllFreqOffset[8];

            /* Erista Specific */
            u32 T210EmcVoltOffset[2];
        };

        struct PcvOffset {
            ro::ModuleId module_id;
            PcvOffsetEntry entry;
        };

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

                module_id.data[ofs] = (ParseNybble(str[0]) << 4) | (ParseNybble(str[1]) << 0);

                str += 2;
                ofs++;
            }

            return module_id;
        }

        #include "ldr_embedded_pcv_patch_data.inc"

        constexpr u32 EmcPllFreqLimit = 4266000000; // should be large enough.

        /* Store freqs/voltages/whatever in a volatile struct with magic to
         * allow easy editing of that information without recompiling.
         * If you wish to write a program to make use of this, contact ZachyCatGame#6421. */
        volatile struct {
            char Magic[4] = { 'B', 'R', 'E', 'D' };

            /* Increment on format changes. */
            u16 FormatVersion = 0;

            /* Format Type (Always 1). */
            u16 FormatType = 1;

            /* Flags:
             *  bit0 = EmcOverclockEnabled,
             *  bit1 = EmcOvervoltEnabled, */
            u16 Flags = 0xFF;

            /* Reserved. */
            u8 HeaderReserved[6] = {0};

            /* New Emc Freq. */
            u32 EmcFreq = 1862400;

            /* Emc Voltage for Erista. */
            u32 EmcVoltErista = 1125000;

            /* Reserved. */
            u32 EmcReserved[6] = {0};
        } PcvInfo;

        inline bool EmcOverclockEnabled() {
            return PcvInfo.Flags & 1;
        }

        inline bool EmcOvervoltEnabled() {
            return PcvInfo.Flags >> 1 & 1;
        }
    }

    void ApplyPcvPatch(u8 *mapped_module, const ro::ModuleId* module_id) {
        const PcvOffsetEntry* pcv_offsets = nullptr;

        /* Determine version. */
        bool found = false;
        for (const auto &patch : PcvOffsets) {
            if (!std::memcmp(std::addressof(patch.module_id), module_id, sizeof(patch.module_id))) {
                pcv_offsets = std::addressof(patch.entry);
                found = true;
            }
        }

        /* Return if a patch for this module id wasn't found. */
        if (!found) {
            return;
        }

        /* Determine SoC type. */
        const spl::SocType soc_type = spl::GetSocType();

        if (soc_type == spl::SocType_Mariko) {
            /* Assert that mariko is supported on this firmware. */
            AMS_ABORT_UNLESS(pcv_offsets->MarikoSupported);
        }

        /* Handle EMC/Memory overclock. */
        /* Note: requires removing minerva or modifiying minerva to enable overclocking. */
        if (EmcOverclockEnabled()) {
            /* Patch max emc freq for Erista and Mariko. */
            for (u32 i = 0; i < pcv_offsets->EmcFreqOffsets.offset_count; i++) {
                std::memcpy(mapped_module + pcv_offsets->EmcFreqOffsets.offsets[i], (void*)&PcvInfo.EmcFreq, sizeof(PcvInfo.EmcFreq));
            }
            
            /* Patch Emc pll max freq. */
            /* Only on 12.0+ b/c I'm too lazy to backport to every firmware when they don't seemt to impact anything. */
            if(hos::GetVersion() >= hos::Version_12_0_0) {
                for (u32 i = 0; i < 8; i++) {
                    if(!pcv_offsets->EmcPllFreqOffset[i]) break;
                    std::memcpy(mapped_module + pcv_offsets->EmcPllFreqOffset[i], &EmcPllFreqLimit, 0x4);
                }
            }
        }

        if (EmcOvervoltEnabled()) {
            if (soc_type == spl::SocType_Erista) {
                /* Patch Erista max emc voltage. */
                for (u32 i = 0; i < 2; i++) {
                    std::memcpy(mapped_module + pcv_offsets->T210EmcVoltOffset[i], (void*)&PcvInfo.EmcVoltErista, sizeof(PcvInfo.EmcVoltErista));
                }
            } else /* if(spl::GetSocType() == spl::SocType_Mariko) */ {
                /* ... */
            }
        }

        return;
    }

}
