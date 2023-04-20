constexpr inline const PcvOffsetEntry PcvOffsets_1_0_0 = {
    .MarikoSupported = false,

    .EmcFreqOffsets = { 5, { 0xE211C, 0xFA38C, 0x10640C, 0x11248C, 0x11E50C } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xD4B48, 0xD4B4C }
};

constexpr inline const PcvOffsetEntry PcvOffsets_2_0_0 = {
    .MarikoSupported = false,

    .EmcFreqOffsets = { 6, { 0xBE4E0, 0xD6DDC, 0xE2E5C, 0xEEEDC, 0xFAF5C, 0x106FDC } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xB0CD8, 0xB0CDC }
};

constexpr inline const PcvOffsetEntry PcvOffsets_3_0_0 = {
    .MarikoSupported = false,

    .EmcFreqOffsets = { 8, { 0xCC2F0, 0xE4D7C, 0xF0DFC, 0xFCE7C, 0x108EFC, 0x114F7C, 0x120FFC, 0x12D07C } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x12F5B0, 0x12F5B4 }
};

constexpr inline const PcvOffsetEntry PcvOffsets_4_0_0 = {
    .MarikoSupported = false,

    .EmcFreqOffsets = { 8, { 0xCD830, 0xE62CC,  0xF234C, 0xFE3CC, 0x10A44C, 0x1164C4, 0x12254C, 0x12E5CC } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x130B90, 0x130B94 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_5_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 24, { 0xBE4A8, 0x105CB8, 0x10A8D8, 0x10A928, 0x10AE48, 0x10AE50, 0x10AE58, 0x10AE60, 0x10AE68, 0x10AE70, 0x10AE78, 0x10AE80, 0x10AE88, 0x10AE90, 0x121E70, 0x12DEF0, 0x1313C8, 0x13D1D4, 0x149254, 0x1552D4, 0x161354, 0x16D3D4, 0x1708AC, 0x173B10 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x1762C0, 0x1762C4 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_5_1_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 24, { 0xBE538, 0x105CF8, 0x10A918, 0x10A968, 0x10AE88, 0x10AE90, 0x10AE98, 0x10AEA0, 0x10AEA8, 0x10AEB0, 0x10AEB8, 0x10AEC0, 0x10AEC8, 0x10AED0, 0x121EB0, 0x12DF30, 0x131408, 0x13D214, 0x149294, 0x155314, 0x161394, 0x16D414, 0x1708EC, 0x173B50 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x176300, 0x176304 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_6_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 25, { 0xFE170, 0xFE178, 0xFE180, 0xFE188, 0xFE190, 0xFE198, 0xFE1A0, 0xFE1A8, 0xFE1B0, 0xFE1B8, 0x107CE0, 0x1154A0, 0x121520, 0x1249FC, 0x130804, 0x13C884, 0x148904, 0x154984, 0x160A04, 0x163EDC, 0x167140, 0x16A3A4, 0x176158, 0x17AE78, 0x17AEC8 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xE92E0, 0xE92E4 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_7_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 26, { 0x1001D0, 0x1001D8, 0x1001E0, 0x1001E8, 0x1001F0, 0x1001F8, 0x100200, 0x100208, 0x100210, 0x100218, 0x109D70, 0x1174F0, 0x123570, 0x125A4C, 0x132854, 0x13E8D4, 0x14A954, 0x1569D4, 0x162A54, 0x165F2C, 0x169190, 0x16C3F4, 0x16F654, 0x17B410, 0x180130, 0x180180 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xEB340, 0xEB344 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_8_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 27, { 0x11C9E0, 0x11C9E8, 0x11C9F0, 0x11C9F8, 0x11CA00, 0x11CA08, 0x11CA10, 0x11CA18, 0x11CA20, 0x11CA28, 0x126580, 0x133D20, 0x13FDA0, 0x143278, 0x14F084, 0x15B104, 0x167184, 0x173204, 0x17F284, 0x18275C, 0x1859C0, 0x188C24, 0x18BE88, 0x18F0EC, 0x19AEA0, 0x19FBC0, 0x19FC10 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x107978, 0x10797C },
};

constexpr inline const PcvOffsetEntry PcvOffsets_9_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 28, { 0xD9A28, 0xD9A30, 0xD9A38, 0xD9A40, 0xD9A48, 0xD9A50, 0xD9A58, 0xD9A60, 0xD9A68, 0xD9A70, 0xE35C8, 0xF0D68, 0xF4240, 0x10004C, 0x10C0CC, 0x10F5A4, 0x112808, 0x115A6C, 0x118CD0, 0x11BF34, 0x11F198, 0x1223FC, 0x125660, 0x1288C4, 0x12BB28, 0x1378E0, 0x13C600, 0x13C650 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x13F1B0, 0x13F1B4 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_10_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 28, { 0xD78D8, 0xD78E0, 0xD78E8, 0xD78F0, 0xD78F8, 0xD7900, 0xD7908, 0xD7910, 0xD7918, 0xD7920, 0xE1478, 0xEEC18, 0xF20F0, 0xFDEFC, 0x109F7C, 0x10D454, 0x1106B8, 0x11391C, 0x116B80, 0x119DE4, 0x11D048, 0x1202AC, 0x123510, 0x126774, 0x1299D8, 0x135790, 0x13A4B0, 0x13A500 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x13D128, 0x13D12C },
};

constexpr inline const PcvOffsetEntry PcvOffsets_11_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 30, { 0xD7C60, 0xD7C68, 0xD7C70, 0xD7C78, 0xD7C80, 0xD7C88, 0xD7C90, 0xD7C98, 0xD7CA0, 0xD7CA8, 0xE1800, 0xEEFA0, 0xF2478, 0xFE284, 0x10A304, 0x10D7DC, 0x110A40, 0x113CA4, 0x116F08, 0x11A16C, 0x11D3D0, 0x120634, 0x123898, 0x126AFC, 0x129D60, 0x12CFC4, 0x130228, 0x13BFE0, 0x140D00, 0x140D50 } },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x143998, 0x14399C },
};

constexpr inline const PcvOffsetEntry PcvOffsets_12_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 30, { 0xE1810, 0xE6530, 0xE6580, 0xE6AB0, 0xE6AB8, 0xE6AC0, 0xE6AC8, 0xE6AD0, 0xE6AD8, 0xE6AE0, 0xE6AE8, 0xE6AF0, 0xE6AF8, 0xF0650, 0xFDDF0, 0x1012C8, 0x10D0D4, 0x119154, 0x11C62C, 0x11F890, 0x122AF4, 0x125D58, 0x128FBC, 0x12C220, 0x12F484, 0x1326E8, 0x13594C, 0x138BB0, 0x13BE14, 0x13F078 } },
    .EmcPllFreqOffset = { 0xDA758, 0xDA770, 0xDA7E8, 0xDA800, 0xDA7A0, 0xDA7B8, 0xDA830, 0xDA848 },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x142878, 0x14287C },
};

constexpr inline const PcvOffsetEntry PcvOffsets_13_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 30, { 0xE1860, 0xE6580, 0xE65D0, 0xE6B00, 0xE6B08, 0xE6B10, 0xE6B18, 0xE6B20, 0xE6B28, 0xE6B30, 0xE6B38, 0xE6B40, 0xE6B48, 0xF06A0, 0xFDE40, 0x101318, 0x10D124, 0x1191A4, 0x11C67C, 0x11F8E0, 0x122B44, 0x125DA8, 0x12900C, 0x12C270, 0x12F4D4, 0x132738, 0x13599C, 0x138C00, 0x13BE64, 0x13F0C8 } },
    .EmcPllFreqOffset = { 0xDA7A8, 0xDA7C0, 0xDA838, 0xDA850, 0xDA7F0, 0xDA808, 0xDA880, 0xDA898 },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0x1428B8, 0x1428BC },
};

constexpr inline const PcvOffsetEntry PcvOffsets_14_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 32, { 0xE56C0, 0xEA3E0, 0xEA430, 0xEA960, 0xEA968, 0xEA970, 0xEA978, 0xEA980, 0xEA988, 0xEA990, 0xEA998, 0xEA9A0, 0xEA9A8, 0xF4500, 0x101CA0, 0x105178, 0x110F84, 0x11D004, 0x1204DC, 0x123740, 0x1269A4, 0x129C08, 0x12CE6C, 0x1300D0, 0x133334, 0x136598, 0x1397FC, 0x13CA60, 0x13FCC4, 0x142F28, 0x14618C, 0x1493F0 } },
    .EmcPllFreqOffset = { 0xDE608, 0xDE620, 0xDE698, 0xDE6B0, 0xDE650, 0xDE668, 0xDE6E0, 0xDE6F8 },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xC18A8, 0xC18AC },
};

constexpr inline const PcvOffsetEntry PcvOffsets_15_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 32, { 0xE0518, 0xE5238, 0xE5288, 0xE59B8, 0xE59C0, 0xE59C8, 0xE59D0, 0xE59D8, 0xE59E0, 0xE59E8, 0xE59F0, 0xE59F8, 0xE5A00, 0xEF558, 0xFCCF8, 0x1001D0, 0x10BFDC, 0x11805C, 0x11B534, 0x11E798, 0x1219FC, 0x124C60, 0x127EC4, 0x12B128, 0x12E38C, 0x1315F0, 0x134854, 0x137AB8, 0x13AD1C, 0x13DF80, 0x1411E4, 0x144448 } },
    .EmcPllFreqOffset = { 0xD9460, 0xD9478, 0xD94F0, 0xD9508, 0xD94A8, 0xD94C0, 0xD9538, 0xD9550 },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xBC6A0, 0xBC6A8 },
};

constexpr inline const PcvOffsetEntry PcvOffsets_16_0_0 = {
    .MarikoSupported = true,

    .EmcFreqOffsets = { 34, { 0xDC428, 0xE1148, 0xE1198, 0xE18C8, 0xE18D0, 0xE18D8, 0xE18E0, 0xE18E8, 0xE18F0, 0xE18F8, 0xE1900, 0xE1908, 0xE1910, 0xEB468, 0xF8C08, 0xFC0E0, 0x107EEC, 0x113F6C, 0x117444, 0x11A6A8, 0x11D90C, 0x120B70, 0x123DD4, 0x127038, 0x12A29C, 0x12D500, 0x130764, 0x1339C8, 0x136C2C, 0x139E90, 0x13D0F4, 0x140358, 0x1435BC, 0x146820 } },
    .EmcPllFreqOffset = { 0xD5370, 0xD5388, 0xD5400, 0xD5418, 0xD53B8, 0xD53D0, 0xD5448, 0xD5460 },

    /* Erista Specific */
    .T210EmcVoltOffset = { 0xB8660, 0xB8668 },
};

constexpr inline const PcvOffset PcvOffsets[] = {
    { ParseModuleId("13B63ACC845C6BB9CF6EDE4250A3C725604EFFB8"), PcvOffsets_1_0_0 }, // 0.8.15-0
    { ParseModuleId("B5925604D55DD4BA0A4F53EF2D547652EC10884F"), PcvOffsets_1_0_0 }, // 1.0.0-7
    { ParseModuleId("798E17E082FDAD6713AC807181040277C80496BB"), PcvOffsets_1_0_0 }, // 1.0.0-15
    { ParseModuleId("98E4C0FE3A8587942C4F3E39A936DED1FC85F40A"), PcvOffsets_2_0_0 }, // 2.0.0-13 to 2.3.0
    { ParseModuleId("208BB4D2827231C260A8901EF305054D4B99497D"), PcvOffsets_3_0_0 }, // 3.0.0
    { ParseModuleId("7B00B6BF89ABBF0ACC43CC2C66E2B1C85719FF96"), PcvOffsets_3_0_0 }, // 3.0.1 to 3.0.2
    { ParseModuleId("711183E5613A02C6B40CE9BA62A437D5AE7B3ACB"), PcvOffsets_4_0_0 }, // 4.0.0 to 4.1.0
    { ParseModuleId("025AFEC8234F9D29A2B4E59DB8C2428F65E1AA96"), PcvOffsets_5_0_0 }, // 5.0.0 to 5.0.2
    { ParseModuleId("0FBC5CF9E0C33CFBA6A794B3AC4A2C6B51E7592C"), PcvOffsets_5_1_0 }, // 5.1.0
    { ParseModuleId("FE9F2972D062FE7B4284C5756F8D1FEAA7CBB423"), PcvOffsets_6_0_0 }, // 6.0.0-4
    { ParseModuleId("AB67DC8A73273A114B3525F4A8DD7BC9CADC56C4"), PcvOffsets_6_0_0 }, // 6.0.0-5 to 6.2.0
    { ParseModuleId("2A321569A7214D8A49477F8D70FCCCC0CFC064BF"), PcvOffsets_7_0_0 }, // 7.0.0 to 7.0.0-5
    { ParseModuleId("00B8943546391A1F4E80AEB210049E37EB33BAF0"), PcvOffsets_8_0_0 }, // 8.0.0 to 8.1.1
    { ParseModuleId("EE33AE06452B4456578DFD1E9C45A7F90CEF11A7"), PcvOffsets_9_0_0 }, // 9.0.0 to 9.2.0
    { ParseModuleId("2F17B50433CFB4F57B47A909EFE5D7DD10394DC4"), PcvOffsets_10_0_0 }, // 10.0.0 to 10.2.0
    { ParseModuleId("91D61D59D7002378E35584FC0B38C7693A3ABAB5"), PcvOffsets_11_0_0 }, // 11.0.0 to 11.0.1
    { ParseModuleId("C503E96550F302E121873136B814A529863D949B"), PcvOffsets_12_0_0 }, // 12.0.0 to 12.1.0
    { ParseModuleId("2058C97C551571506656AA04EC85E2B1B01B155C"), PcvOffsets_13_0_0 }, // 13.0.0 to 13.2.1
    { ParseModuleId("DE2C8A80A1970109241029194A22D0004D6E241C"), PcvOffsets_14_0_0 }, // 14.0.0 to 14.1.2
    { ParseModuleId("961A1D4EAF69396B5F61A6A70B8873F7BEB34332"), PcvOffsets_15_0_0 }, // 15.0.0 to 15.0.1
    { ParseModuleId("424BFC8D5108B9AE6E0D684143706EF024759EB6"), PcvOffsets_16_0_0 }, // 16.0.0+
};
