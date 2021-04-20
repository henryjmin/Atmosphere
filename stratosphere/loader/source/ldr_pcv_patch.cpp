#include <stratosphere.hpp>

#define EMC_OVERVOLT 0

namespace ams::ldr {

    namespace {

        /* 
        11.0.0:
            0xD7C60,
            0xD7C68,
            0xD7C70,
            0xD7C78,
            0xD7C80,
            0xD7C88,
            0xD7C90,
            0xD7C98,
            0xD7CA0,
            0xD7CA8,
            0xE1800,
            0xEEFA0,
            0xF2478,
            0xFE284,
            0x10A304,
            0x10D7DC,
            0x110A40,
            0x113CA4,
            0x116F08,
            0x11A16C,
            0x11D3D0,
            0x120634,
            0x123898,
            0x126AFC,
            0x129D60,
            0x12CFC4,
            0x130228,
            0x13BFE0,
            0x140D00,
            0x140D50,
        */
        constexpr u32 EmcFreqOffsets[30] = {
            0xE1810,
            0xE6530,
            0xE6580,
            0xE6AB0,
            0xE6AB8,
            0xE6AC0,
            0xE6AC8,
            0xE6AD0,
            0xE6AD8,
            0xE6AE0,
            0xE6AE8,
            0xE6AF0,
            0xE6AF8,
            0xF0650,
            0xFDDF0,
            0x1012C8,
            0x10D0D4,
            0x119154,
            0x11C62C,
            0x11F890,
            0x122AF4,
            0x125D58,
            0x128FBC,
            0x12C220,
            0x12F484,
            0x1326E8,
            0x13594C,
            0x138BB0,
            0x13BE14,
            0x13F078,
        };
        constexpr u32 NewEmcFreq = 1862400;

        namespace Erista {

            /* EMC */
            /* 
            11.0.0: 0x143998, 0x14399C
            */
            constexpr u32 EmcVolatageOffsets[2] = { 0x142878, 0x14287C };
            constexpr u32 NewEmcVoltage = 1200000;
            static_assert(NewEmcVoltage <= 1250000);

        };

        namespace Mariko {

        };

    }

    void ApplyPcvPatch(u8 *mapped_module, size_t mapped_size) {
        /* Patch EMC clocks. note: On Erista, this requires removing or modifiying minerva */
        for(u32 i = 0; i < sizeof(EmcFreqOffsets)/sizeof(u32); i++) {
            AMS_ABORT_UNLESS(EmcFreqOffsets[i] <= mapped_size);
            std::memcpy(mapped_module + EmcFreqOffsets[i], &NewEmcFreq, sizeof(NewEmcFreq));
        }

        /* Patch EMC voltage if enabled */
        if constexpr(EMC_OVERVOLT) {
            if(spl::GetSocType() == spl::SocType_Erista) {
                for(u32 i = 0; i < sizeof(Erista::EmcVolatageOffsets)/sizeof(u32); i++) {
                    AMS_ABORT_UNLESS(Erista::EmcVolatageOffsets[i] <= mapped_size);
                    std::memcpy(mapped_module + Erista::EmcVolatageOffsets[i], &Erista::NewEmcVoltage, sizeof(Erista::NewEmcVoltage));
                }
            } else /* if(spl::GetSocType() == spl::SocType_Mariko) */ {
                /* ... */
            }
        }

        return;
    }

}
