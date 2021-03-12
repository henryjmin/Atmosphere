#include <stratosphere.hpp>

#define EMC_OVERCLOCK 1
#define EMC_OVERVOLT 0

namespace ams::ldr {

    namespace {

        typedef struct {
            u32 hz = 0;
            u32 volt = 0;
            u32 unk[6] = {0};
            s32 coeffs[6] = {0};
        } gpu_clock_table_t;

        constexpr u32 EmcFreqOffsets[30] = {
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
        };
        constexpr u32 NewEmcFreq = 1862400;

        namespace Erista {

            typedef struct {
                u32 hz = 0;
                u32 unk = 0;
                u32 volt = 0;
                u32 unk2[5] = {0};
                s32 coeffs[6] = {0};
            } cpu_clock_table_t;

            /* CPU */
            constexpr u32 CpuTablesFreeSpace = 0xE3B78;
            constexpr cpu_clock_table_t NewCpuTables[] = { 

            };
            static_assert(sizeof(NewCpuTables) <= sizeof(cpu_clock_table_t)*16);

            constexpr u32 CpuVoltageLimitOffsets[] = { 0xE1AC8, 0xE1AD4, 0xE37E4 };
            constexpr u32 NewCpuVoltageLimit = 1400;
            static_assert(NewCpuVoltageLimit <= 1400);

            /* GPU */
            constexpr u32 GpuTablesFreeSpace = 0xE2B58;
            constexpr gpu_clock_table_t NewGpuTables[] = {

            };
            static_assert(sizeof(NewGpuTables) <= sizeof(gpu_clock_table_t)*20);


            /* EMC */
            constexpr u32 EmcVolatageOffsets[2] = { 0x143998, 0x14399C };
            constexpr u32 NewEmcVoltage = 1200000;
            static_assert(NewEmcVoltage <= 1250000); // prevent me from being a galaxy brain

        };

        namespace Mariko {

            typedef struct {
                u32 hz = 0;
                u32 unk1 = 0;
                s32 coeffs[6] = {0};
                u32 volt = 0;
                u32 unk3[5] = {0};
            } cpu_clock_table_t;

            /* CPU */
            constexpr u32 CpuTablesFreeSpace = 0xE2350;
            constexpr cpu_clock_table_t NewCpuTables[] = {0};
            static_assert(sizeof(NewCpuTables) <= sizeof(cpu_clock_table_t)*14);

            constexpr u32 MaxCpuClockOffset = 0xE2740;
            constexpr u32 NewMaxCpuClock = 1963500;

            /* GPU */
            constexpr u32 GpuTablesFreeSpace = 0xE3410;
            constexpr gpu_clock_table_t NewGpuTables[] = {0};
            static_assert(sizeof(NewGpuTables) <= sizeof(gpu_clock_table_t)*15);

            constexpr u32 Reg1MaxGpuOffset = 0x2E0AC;
            constexpr u8 Reg1NewMaxGpuClock[0xC] = {
                /* 1267MHz */
                /*
                MOV   W13,#0x5600
                MOVK  W13,#0x13,LSL #16
                NOP
                */
                0x0D, 0xC0, 0x8A, 0x52, 0x6D, 0x02, 0xA0, 0x72, 0x1F, 0x20, 0x03, 0xD5
            };

            constexpr u32 Reg2MaxGpuOffset = 0x2E110;
            constexpr u8 Reg2NewMaxGpuClock[0x8] = {
                /* 1267MHz */
                /*
                MOV   W13,#0x5600
                MOVK  W13,#0x13,LSL #16
                */
                0x0D, 0xC0, 0x8A, 0x52, 0x6D, 0x02, 0xA0, 0x72
            };

        };

    }

    void ApplyPcvPatch(u8 *mapped_module, size_t mapped_size) {
        /* Add new CPU and GPU clock tables for Erista */
        AMS_ABORT_UNLESS(Erista::CpuTablesFreeSpace <= mapped_size && Erista::GpuTablesFreeSpace <= mapped_size);
        std::memcpy(mapped_module + Erista::CpuTablesFreeSpace, Erista::NewCpuTables, sizeof(Erista::NewCpuTables));
        std::memcpy(mapped_module + Erista::GpuTablesFreeSpace, Erista::NewGpuTables, sizeof(Erista::NewGpuTables));

        /* Patch max CPU voltage on Erista */
        for(int i = 0; i < 3; i++) {
            std::memcpy(mapped_module + Erista::CpuVoltageLimitOffsets[i], &Erista::NewCpuVoltageLimit, sizeof(Erista::NewCpuVoltageLimit));
        }

        /* Add new CPU and GPU clock tables for Mariko */
        AMS_ABORT_UNLESS(Mariko::CpuTablesFreeSpace <= mapped_size && Mariko::GpuTablesFreeSpace <= mapped_size);
        std::memcpy(mapped_module + Mariko::CpuTablesFreeSpace, Mariko::NewCpuTables, sizeof(Mariko::NewCpuTables));
        std::memcpy(mapped_module + Mariko::GpuTablesFreeSpace, Mariko::NewGpuTables, sizeof(Mariko::NewGpuTables));

        /* Patch Mariko max CPU and GPU clockrates */
        AMS_ABORT_UNLESS(Mariko::MaxCpuClockOffset <= mapped_size && Mariko::Reg1MaxGpuOffset <= mapped_size && Mariko::Reg2MaxGpuOffset <= mapped_size);
        std::memcpy(mapped_module + Mariko::MaxCpuClockOffset, &Mariko::NewMaxCpuClock, sizeof(Mariko::NewMaxCpuClock));
        std::memcpy(mapped_module + Mariko::Reg1MaxGpuOffset, Mariko::Reg1NewMaxGpuClock, sizeof(Mariko::Reg1NewMaxGpuClock));
        std::memcpy(mapped_module + Mariko::Reg2MaxGpuOffset, Mariko::Reg2NewMaxGpuClock, sizeof(Mariko::Reg2NewMaxGpuClock));

        /* Patch EMC clocks and voltage if enabled. note: requires removing minerva or modifiying minerva to enable overclocking */
        if constexpr(EMC_OVERCLOCK) {
            for(u32 i = 0; i < sizeof(EmcFreqOffsets)/sizeof(u32); i++) {
                AMS_ABORT_UNLESS(EmcFreqOffsets[i] <= mapped_size);
                std::memcpy(mapped_module + EmcFreqOffsets[i], &NewEmcFreq, sizeof(NewEmcFreq));
            }
        }

        if constexpr(EMC_OVERVOLT) {
            if(spl::GetSocType() == spl::SocType_Erista) {
                for(u32 i = 0; i < sizeof(Erista::EmcVolatageOffsets)/sizeof(u32); i++) {
                    AMS_ABORT_UNLESS(Erista::EmcVolatageOffsets[i] <= mapped_size);
                    std::memcpy(mapped_module + Erista::EmcVolatageOffsets[i], &Erista::NewEmcVoltage, sizeof(Erista::NewEmcVoltage));
                }
            } else /* if(spl::GetSocType() == spl::SocType_Mariko) */ {

            }
        }

        return;
    }

}
