#include <stratosphere.hpp>
#include "ldr_pcv_patch.hpp"

#define EMC_OVERCLOCK 1
#define EMC_OVERVOLT 0

namespace ams::ldr {

    namespace {

        constexpr u32 NewEmcFreq = 1862400;

        namespace Erista {
            /* EMC */
            constexpr u32 NewEmcVoltage = 1200000;
            static_assert(NewEmcVoltage <= 1250000);

        };

        namespace Mariko {
            /* NOTE: Mariko hardware was not supported until firmware 5.0.0 */
            /* ... */
        };

    }

    void ApplyPcvPatch(u8 *mapped_module, size_t mapped_size, u32 target_version) {
        /* Patch EMC clocks and voltage if enabled. note: requires removing minerva or modifiying minerva to enable overclocking */
        if constexpr(EMC_OVERCLOCK) {
            for(u32 i = 0; i < PcvInfo[target_version].EmcFreqOffsets.offset_count; i++) {
                AMS_ABORT_UNLESS(PcvInfo[target_version].EmcFreqOffsets.offsets[i] <= mapped_size);
                std::memcpy(mapped_module + PcvInfo[target_version].EmcFreqOffsets.offsets[i], &NewEmcFreq, sizeof(NewEmcFreq));
            }
        }

        if constexpr(EMC_OVERVOLT) {
            if(spl::GetSocType() == spl::SocType_Erista) {
                for(u32 i = 0; i < 2; i++) {
                    AMS_ABORT_UNLESS(PcvInfo[target_version].EristaEmcVolatageOffsets[i] <= mapped_size);
                    std::memcpy(mapped_module + PcvInfo[target_version].EristaEmcVolatageOffsets[i], &Erista::NewEmcVoltage, sizeof(Erista::NewEmcVoltage));
                }
            } else if(spl::GetSocType() == spl::SocType_Mariko && PcvInfo[target_version].MarikoSupported) {
                /* ... */
            }
        }

        return;
    }

}
