#include <codemorph/codemorph.hpp>

#include <array>
#include <stdexcept>

namespace codemorph {
namespace {

constexpr std::array<std::byte, 256> hex_lookup = {
    /* 00-0F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* 10-1F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* 20-2F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* 30-3F */ std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}, std::byte{5}, std::byte{6},
    std::byte{7},
    std::byte{8}, std::byte{9}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0}, // '0'–'9'
    /* 40-4F */ std::byte{0}, std::byte{10}, std::byte{11}, std::byte{12}, std::byte{13}, std::byte{14},
    std::byte{15}, std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0}, // 'A'–'F'
    /* 50-5F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* 60-6F */ std::byte{0}, std::byte{10}, std::byte{11}, std::byte{12}, std::byte{13}, std::byte{14},
    std::byte{15}, std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0}, // 'a'–'f'
    /* 70-7F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* 80-8F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* 90-9F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* A0-AF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* B0-BF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* C0-CF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* D0-DF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* E0-EF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    /* F0-FF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0},
    std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
    std::byte{0}
};

constexpr std::array<std::byte, 256> ascii_to_ebcdic_table = {
    /*00*/ static_cast<std::byte>(0x00), static_cast<std::byte>(0x01), static_cast<std::byte>(0x02),
    static_cast<std::byte>(0x03), static_cast<std::byte>(0x37), static_cast<std::byte>(0x2d),
    static_cast<std::byte>(0x2e), static_cast<std::byte>(0x2f),
    static_cast<std::byte>(0x16), static_cast<std::byte>(0x05), static_cast<std::byte>(0x15),
    static_cast<std::byte>(0x0b), static_cast<std::byte>(0x0c), static_cast<std::byte>(0x0d),
    static_cast<std::byte>(0x0e), static_cast<std::byte>(0x0f), /*................*/
    /*10*/ static_cast<std::byte>(0x10), static_cast<std::byte>(0x11), static_cast<std::byte>(0x12),
    static_cast<std::byte>(0x13), static_cast<std::byte>(0x3c), static_cast<std::byte>(0x3d),
    static_cast<std::byte>(0x32), static_cast<std::byte>(0x26),
    static_cast<std::byte>(0x18), static_cast<std::byte>(0x19), static_cast<std::byte>(0x3f),
    static_cast<std::byte>(0x27), static_cast<std::byte>(0x1c), static_cast<std::byte>(0x1d),
    static_cast<std::byte>(0x1e), static_cast<std::byte>(0x1f), /*................*/
    /*20*/ static_cast<std::byte>(0x40), static_cast<std::byte>(0x5a), static_cast<std::byte>(0x7f),
    static_cast<std::byte>(0x7b), static_cast<std::byte>(0x5b), static_cast<std::byte>(0x6c),
    static_cast<std::byte>(0x50), static_cast<std::byte>(0x7d),
    static_cast<std::byte>(0x4d), static_cast<std::byte>(0x5d), static_cast<std::byte>(0x5c),
    static_cast<std::byte>(0x4e), static_cast<std::byte>(0x6b), static_cast<std::byte>(0x60),
    static_cast<std::byte>(0x4b), static_cast<std::byte>(0x61), /* !"#$%&'()*+,-./ */
    /*30*/ static_cast<std::byte>(0xf0), static_cast<std::byte>(0xf1), static_cast<std::byte>(0xf2),
    static_cast<std::byte>(0xf3), static_cast<std::byte>(0xf4), static_cast<std::byte>(0xf5),
    static_cast<std::byte>(0xf6), static_cast<std::byte>(0xf7),
    static_cast<std::byte>(0xf8), static_cast<std::byte>(0xf9), static_cast<std::byte>(0x7a),
    static_cast<std::byte>(0x5e), static_cast<std::byte>(0x4c), static_cast<std::byte>(0x7e),
    static_cast<std::byte>(0x6e), static_cast<std::byte>(0x6f), /*0123456789:;<=>?*/
    /*40*/ static_cast<std::byte>(0x7c), static_cast<std::byte>(0xc1), static_cast<std::byte>(0xc2),
    static_cast<std::byte>(0xc3), static_cast<std::byte>(0xc4), static_cast<std::byte>(0xc5),
    static_cast<std::byte>(0xc6), static_cast<std::byte>(0xc7),
    static_cast<std::byte>(0xc8), static_cast<std::byte>(0xc9), static_cast<std::byte>(0xd1),
    static_cast<std::byte>(0xd2), static_cast<std::byte>(0xd3), static_cast<std::byte>(0xd4),
    static_cast<std::byte>(0xd5), static_cast<std::byte>(0xd6), /*@ABCDEFGHIJKLMNO*/
    /*50*/ static_cast<std::byte>(0xd7), static_cast<std::byte>(0xd8), static_cast<std::byte>(0xd9),
    static_cast<std::byte>(0xe2), static_cast<std::byte>(0xe3), static_cast<std::byte>(0xe4),
    static_cast<std::byte>(0xe5), static_cast<std::byte>(0xe6),
    static_cast<std::byte>(0xe7), static_cast<std::byte>(0xe8), static_cast<std::byte>(0xe9),
    static_cast<std::byte>(0xbb), static_cast<std::byte>(0xbc), static_cast<std::byte>(0xbd),
    static_cast<std::byte>(0x6a), static_cast<std::byte>(0x6d), /*PQRSTUVWXYZ[\]^_*/
    /*60*/ static_cast<std::byte>(0x4a), static_cast<std::byte>(0x81), static_cast<std::byte>(0x82),
    static_cast<std::byte>(0x83), static_cast<std::byte>(0x84), static_cast<std::byte>(0x85),
    static_cast<std::byte>(0x86), static_cast<std::byte>(0x87),
    static_cast<std::byte>(0x88), static_cast<std::byte>(0x89), static_cast<std::byte>(0x91),
    static_cast<std::byte>(0x92), static_cast<std::byte>(0x93), static_cast<std::byte>(0x94),
    static_cast<std::byte>(0x95), static_cast<std::byte>(0x96), /*`abcdefghijklmno*/
    /*70*/ static_cast<std::byte>(0x97), static_cast<std::byte>(0x98), static_cast<std::byte>(0x99),
    static_cast<std::byte>(0xa2), static_cast<std::byte>(0xa3), static_cast<std::byte>(0xa4),
    static_cast<std::byte>(0xa5), static_cast<std::byte>(0xa6),
    static_cast<std::byte>(0xa7), static_cast<std::byte>(0xa8), static_cast<std::byte>(0xa9),
    static_cast<std::byte>(0xfb), static_cast<std::byte>(0x4f), static_cast<std::byte>(0xfd),
    static_cast<std::byte>(0xff), static_cast<std::byte>(0x07), /*pqrstuvwxyz{|}~.*/
    /*80*/ static_cast<std::byte>(0x20), static_cast<std::byte>(0x21), static_cast<std::byte>(0x22),
    static_cast<std::byte>(0x23), static_cast<std::byte>(0x24), static_cast<std::byte>(0x04),
    static_cast<std::byte>(0x06), static_cast<std::byte>(0x08),
    static_cast<std::byte>(0x28), static_cast<std::byte>(0x29), static_cast<std::byte>(0x2a),
    static_cast<std::byte>(0x2b), static_cast<std::byte>(0x2c), static_cast<std::byte>(0x09),
    static_cast<std::byte>(0x0a), static_cast<std::byte>(0x14), /*................*/
    /*90*/ static_cast<std::byte>(0x30), static_cast<std::byte>(0x31), static_cast<std::byte>(0x25),
    static_cast<std::byte>(0x33), static_cast<std::byte>(0x34), static_cast<std::byte>(0x35),
    static_cast<std::byte>(0x36), static_cast<std::byte>(0x17),
    static_cast<std::byte>(0x38), static_cast<std::byte>(0x39), static_cast<std::byte>(0x3a),
    static_cast<std::byte>(0x3b), static_cast<std::byte>(0x1a), static_cast<std::byte>(0x1b),
    static_cast<std::byte>(0x3e), static_cast<std::byte>(0x5f), /*................*/
    /*a0*/ static_cast<std::byte>(0x41), static_cast<std::byte>(0xaa), static_cast<std::byte>(0xb0),
    static_cast<std::byte>(0xb1), static_cast<std::byte>(0x9f), static_cast<std::byte>(0xb2),
    static_cast<std::byte>(0xd0), static_cast<std::byte>(0xb5),
    static_cast<std::byte>(0x79), static_cast<std::byte>(0xb4), static_cast<std::byte>(0x9a),
    static_cast<std::byte>(0x8a), static_cast<std::byte>(0xba), static_cast<std::byte>(0xca),
    static_cast<std::byte>(0xaf), static_cast<std::byte>(0xa1), /*................*/
    /*b0*/ static_cast<std::byte>(0x90), static_cast<std::byte>(0x8f), static_cast<std::byte>(0xea),
    static_cast<std::byte>(0xfa), static_cast<std::byte>(0xbe), static_cast<std::byte>(0xa0),
    static_cast<std::byte>(0xb6), static_cast<std::byte>(0xb3),
    static_cast<std::byte>(0x9d), static_cast<std::byte>(0xda), static_cast<std::byte>(0x9b),
    static_cast<std::byte>(0x8b), static_cast<std::byte>(0xb7), static_cast<std::byte>(0xb8),
    static_cast<std::byte>(0xb9), static_cast<std::byte>(0xab), /*................*/
    /*c0*/ static_cast<std::byte>(0x64), static_cast<std::byte>(0x65), static_cast<std::byte>(0x62),
    static_cast<std::byte>(0x66), static_cast<std::byte>(0x63), static_cast<std::byte>(0x67),
    static_cast<std::byte>(0x9e), static_cast<std::byte>(0x68),
    static_cast<std::byte>(0x74), static_cast<std::byte>(0x71), static_cast<std::byte>(0x72),
    static_cast<std::byte>(0x73), static_cast<std::byte>(0x78), static_cast<std::byte>(0x75),
    static_cast<std::byte>(0x76), static_cast<std::byte>(0x77), /*................*/
    /*d0*/ static_cast<std::byte>(0xac), static_cast<std::byte>(0x69), static_cast<std::byte>(0xed),
    static_cast<std::byte>(0xee), static_cast<std::byte>(0xeb), static_cast<std::byte>(0xef),
    static_cast<std::byte>(0xec), static_cast<std::byte>(0xbf),
    static_cast<std::byte>(0x80), static_cast<std::byte>(0xe0), static_cast<std::byte>(0xfe),
    static_cast<std::byte>(0xdd), static_cast<std::byte>(0xfc), static_cast<std::byte>(0xad),
    static_cast<std::byte>(0xae), static_cast<std::byte>(0x59), /*................*/
    /*e0*/ static_cast<std::byte>(0x44), static_cast<std::byte>(0x45), static_cast<std::byte>(0x42),
    static_cast<std::byte>(0x46), static_cast<std::byte>(0x43), static_cast<std::byte>(0x47),
    static_cast<std::byte>(0x9c), static_cast<std::byte>(0x48),
    static_cast<std::byte>(0x54), static_cast<std::byte>(0x51), static_cast<std::byte>(0x52),
    static_cast<std::byte>(0x53), static_cast<std::byte>(0x58), static_cast<std::byte>(0x55),
    static_cast<std::byte>(0x56), static_cast<std::byte>(0x57), /*................*/
    /*f0*/ static_cast<std::byte>(0x8c), static_cast<std::byte>(0x49), static_cast<std::byte>(0xcd),
    static_cast<std::byte>(0xce), static_cast<std::byte>(0xcb), static_cast<std::byte>(0xcf),
    static_cast<std::byte>(0xcc), static_cast<std::byte>(0xe1),
    static_cast<std::byte>(0x70), static_cast<std::byte>(0xc0), static_cast<std::byte>(0xde),
    static_cast<std::byte>(0xdb), static_cast<std::byte>(0xdc), static_cast<std::byte>(0x8d),
    static_cast<std::byte>(0x8e), static_cast<std::byte>(0xdf) /*................*/
};

// VISA variant: identical to ascii_to_ebcdic_table except ASCII '^' (0x5E) maps to 0x5F.
constexpr auto ascii_to_ebcdic_visa_table = [] {
    std::array<std::byte, 256> table = ascii_to_ebcdic_table;
    table[0x5E] = static_cast<std::byte>(0x5F);
    return table;
}();

constexpr std::array<std::byte, 256> ebcdic_to_ascii_table = {
    /*00*/ static_cast<std::byte>(0x00), static_cast<std::byte>(0x01), static_cast<std::byte>(0x02),
    static_cast<std::byte>(0x03), static_cast<std::byte>(0x85), static_cast<std::byte>(0x09),
    static_cast<std::byte>(0x86), static_cast<std::byte>(0x7f),
    static_cast<std::byte>(0x87), static_cast<std::byte>(0x8d), static_cast<std::byte>(0x8e),
    static_cast<std::byte>(0x0b), static_cast<std::byte>(0x0c), static_cast<std::byte>(0x0d),
    static_cast<std::byte>(0x0e), static_cast<std::byte>(0x0f), /*................*/
    /*10*/ static_cast<std::byte>(0x10), static_cast<std::byte>(0x11), static_cast<std::byte>(0x12),
    static_cast<std::byte>(0x13), static_cast<std::byte>(0x8f), static_cast<std::byte>(0x0a),
    static_cast<std::byte>(0x08), static_cast<std::byte>(0x97),
    static_cast<std::byte>(0x18), static_cast<std::byte>(0x19), static_cast<std::byte>(0x9c),
    static_cast<std::byte>(0x9d), static_cast<std::byte>(0x1c), static_cast<std::byte>(0x1d),
    static_cast<std::byte>(0x1e), static_cast<std::byte>(0x1f), /*................*/
    /*20*/ static_cast<std::byte>(0x80), static_cast<std::byte>(0x81), static_cast<std::byte>(0x82),
    static_cast<std::byte>(0x83), static_cast<std::byte>(0x84), static_cast<std::byte>(0x92),
    static_cast<std::byte>(0x17), static_cast<std::byte>(0x1b),
    static_cast<std::byte>(0x88), static_cast<std::byte>(0x89), static_cast<std::byte>(0x8a),
    static_cast<std::byte>(0x8b), static_cast<std::byte>(0x8c), static_cast<std::byte>(0x05),
    static_cast<std::byte>(0x06), static_cast<std::byte>(0x07), /*................*/
    /*30*/ static_cast<std::byte>(0x90), static_cast<std::byte>(0x91), static_cast<std::byte>(0x16),
    static_cast<std::byte>(0x93), static_cast<std::byte>(0x94), static_cast<std::byte>(0x95),
    static_cast<std::byte>(0x96), static_cast<std::byte>(0x04),
    static_cast<std::byte>(0x98), static_cast<std::byte>(0x99), static_cast<std::byte>(0x9a),
    static_cast<std::byte>(0x9b), static_cast<std::byte>(0x14), static_cast<std::byte>(0x15),
    static_cast<std::byte>(0x9e), static_cast<std::byte>(0x1a), /*................*/
    /*40*/ static_cast<std::byte>(0x20), static_cast<std::byte>(0xa0), static_cast<std::byte>(0xe2),
    static_cast<std::byte>(0xe4), static_cast<std::byte>(0xe0), static_cast<std::byte>(0xe1),
    static_cast<std::byte>(0xe3), static_cast<std::byte>(0xe5),
    static_cast<std::byte>(0xe7), static_cast<std::byte>(0xf1), static_cast<std::byte>(0x60),
    static_cast<std::byte>(0x2e), static_cast<std::byte>(0x3c), static_cast<std::byte>(0x28),
    static_cast<std::byte>(0x2b), static_cast<std::byte>(0x7c), /* .........`.<(+|*/
    /*50*/ static_cast<std::byte>(0x26), static_cast<std::byte>(0xe9), static_cast<std::byte>(0xea),
    static_cast<std::byte>(0xeb), static_cast<std::byte>(0xe8), static_cast<std::byte>(0xed),
    static_cast<std::byte>(0xee), static_cast<std::byte>(0xef),
    static_cast<std::byte>(0xec), static_cast<std::byte>(0xdf), static_cast<std::byte>(0x21),
    static_cast<std::byte>(0x24), static_cast<std::byte>(0x2a), static_cast<std::byte>(0x29),
    static_cast<std::byte>(0x3b), static_cast<std::byte>(0x9f), /*&.........!$*);.*/
    /*60*/ static_cast<std::byte>(0x2d), static_cast<std::byte>(0x2f), static_cast<std::byte>(0xc2),
    static_cast<std::byte>(0xc4), static_cast<std::byte>(0xc0), static_cast<std::byte>(0xc1),
    static_cast<std::byte>(0xc3), static_cast<std::byte>(0xc5),
    static_cast<std::byte>(0xc7), static_cast<std::byte>(0xd1), static_cast<std::byte>(0x5e),
    static_cast<std::byte>(0x2c), static_cast<std::byte>(0x25), static_cast<std::byte>(0x5f),
    static_cast<std::byte>(0x3e), static_cast<std::byte>(0x3f), /*-/........^,%_>?*/
    /*70*/ static_cast<std::byte>(0xf8), static_cast<std::byte>(0xc9), static_cast<std::byte>(0xca),
    static_cast<std::byte>(0xcb), static_cast<std::byte>(0xc8), static_cast<std::byte>(0xcd),
    static_cast<std::byte>(0xce), static_cast<std::byte>(0xcf),
    static_cast<std::byte>(0xcc), static_cast<std::byte>(0xa8), static_cast<std::byte>(0x3a),
    static_cast<std::byte>(0x23), static_cast<std::byte>(0x40), static_cast<std::byte>(0x27),
    static_cast<std::byte>(0x3d), static_cast<std::byte>(0x22), /*..........:#@'="*/
    /*80*/ static_cast<std::byte>(0xd8), static_cast<std::byte>(0x61), static_cast<std::byte>(0x62),
    static_cast<std::byte>(0x63), static_cast<std::byte>(0x64), static_cast<std::byte>(0x65),
    static_cast<std::byte>(0x66), static_cast<std::byte>(0x67),
    static_cast<std::byte>(0x68), static_cast<std::byte>(0x69), static_cast<std::byte>(0xab),
    static_cast<std::byte>(0xbb), static_cast<std::byte>(0xf0), static_cast<std::byte>(0xfd),
    static_cast<std::byte>(0xfe), static_cast<std::byte>(0xb1), /*.abcdefghi......*/
    /*90*/ static_cast<std::byte>(0xb0), static_cast<std::byte>(0x6a), static_cast<std::byte>(0x6b),
    static_cast<std::byte>(0x6c), static_cast<std::byte>(0x6d), static_cast<std::byte>(0x6e),
    static_cast<std::byte>(0x6f), static_cast<std::byte>(0x70),
    static_cast<std::byte>(0x71), static_cast<std::byte>(0x72), static_cast<std::byte>(0xaa),
    static_cast<std::byte>(0xba), static_cast<std::byte>(0xe6), static_cast<std::byte>(0xb8),
    static_cast<std::byte>(0xc6), static_cast<std::byte>(0xa4), /*.jklmnopqr......*/
    /*a0*/ static_cast<std::byte>(0xb5), static_cast<std::byte>(0xaf), static_cast<std::byte>(0x73),
    static_cast<std::byte>(0x74), static_cast<std::byte>(0x75), static_cast<std::byte>(0x76),
    static_cast<std::byte>(0x77), static_cast<std::byte>(0x78),
    static_cast<std::byte>(0x79), static_cast<std::byte>(0x7a), static_cast<std::byte>(0xa1),
    static_cast<std::byte>(0xbf), static_cast<std::byte>(0xd0), static_cast<std::byte>(0xdd),
    static_cast<std::byte>(0xde), static_cast<std::byte>(0xae), /*..stuvwxyz......*/
    /*b0*/ static_cast<std::byte>(0xa2), static_cast<std::byte>(0xa3), static_cast<std::byte>(0xa5),
    static_cast<std::byte>(0xb7), static_cast<std::byte>(0xa9), static_cast<std::byte>(0xa7),
    static_cast<std::byte>(0xb6), static_cast<std::byte>(0xbc),
    static_cast<std::byte>(0xbd), static_cast<std::byte>(0xbe), static_cast<std::byte>(0xac),
    static_cast<std::byte>(0x5b), static_cast<std::byte>(0x5c), static_cast<std::byte>(0x5d),
    static_cast<std::byte>(0xb4), static_cast<std::byte>(0xd7), /*...........[\]..*/
    /*c0*/ static_cast<std::byte>(0xf9), static_cast<std::byte>(0x41), static_cast<std::byte>(0x42),
    static_cast<std::byte>(0x43), static_cast<std::byte>(0x44), static_cast<std::byte>(0x45),
    static_cast<std::byte>(0x46), static_cast<std::byte>(0x47),
    static_cast<std::byte>(0x48), static_cast<std::byte>(0x49), static_cast<std::byte>(0xad),
    static_cast<std::byte>(0xf4), static_cast<std::byte>(0xf6), static_cast<std::byte>(0xf2),
    static_cast<std::byte>(0xf3), static_cast<std::byte>(0xf5), /*.ABCDEFGHI......*/
    /*d0*/ static_cast<std::byte>(0xa6), static_cast<std::byte>(0x4a), static_cast<std::byte>(0x4b),
    static_cast<std::byte>(0x4c), static_cast<std::byte>(0x4d), static_cast<std::byte>(0x4e),
    static_cast<std::byte>(0x4f), static_cast<std::byte>(0x50),
    static_cast<std::byte>(0x51), static_cast<std::byte>(0x52), static_cast<std::byte>(0xb9),
    static_cast<std::byte>(0xfb), static_cast<std::byte>(0xfc), static_cast<std::byte>(0xdb),
    static_cast<std::byte>(0xfa), static_cast<std::byte>(0xff), /*.JKLMNOPQR......*/
    /*e0*/ static_cast<std::byte>(0xd9), static_cast<std::byte>(0xf7), static_cast<std::byte>(0x53),
    static_cast<std::byte>(0x54), static_cast<std::byte>(0x55), static_cast<std::byte>(0x56),
    static_cast<std::byte>(0x57), static_cast<std::byte>(0x58),
    static_cast<std::byte>(0x59), static_cast<std::byte>(0x5a), static_cast<std::byte>(0xb2),
    static_cast<std::byte>(0xd4), static_cast<std::byte>(0xd6), static_cast<std::byte>(0xd2),
    static_cast<std::byte>(0xd3), static_cast<std::byte>(0xd5), /*..STUVWXYZ......*/
    /*f0*/ static_cast<std::byte>(0x30), static_cast<std::byte>(0x31), static_cast<std::byte>(0x32),
    static_cast<std::byte>(0x33), static_cast<std::byte>(0x34), static_cast<std::byte>(0x35),
    static_cast<std::byte>(0x36), static_cast<std::byte>(0x37),
    static_cast<std::byte>(0x38), static_cast<std::byte>(0x39), static_cast<std::byte>(0xb3),
    static_cast<std::byte>(0x7b), static_cast<std::byte>(0xdc), static_cast<std::byte>(0x7d),
    static_cast<std::byte>(0xda), static_cast<std::byte>(0x7e) /*0123456789.{.}.~*/
};

// EBCDIC to ASCII table for VISA payment systems.
// Key difference from standard IBM-037: 0x5F maps to '^' (0x5E) instead of control char.
// This is required for Track 1 data where '^' is the field separator.
constexpr std::array<std::byte, 256> ebcdic_to_ascii_visa_table = {
    /*00*/ static_cast<std::byte>(0x00), static_cast<std::byte>(0x01), static_cast<std::byte>(0x02),
    static_cast<std::byte>(0x03), static_cast<std::byte>(0x85), static_cast<std::byte>(0x09),
    static_cast<std::byte>(0x86), static_cast<std::byte>(0x7f),
    static_cast<std::byte>(0x87), static_cast<std::byte>(0x8d), static_cast<std::byte>(0x8e),
    static_cast<std::byte>(0x0b), static_cast<std::byte>(0x0c), static_cast<std::byte>(0x0d),
    static_cast<std::byte>(0x0e), static_cast<std::byte>(0x0f), /*................*/
    /*10*/ static_cast<std::byte>(0x10), static_cast<std::byte>(0x11), static_cast<std::byte>(0x12),
    static_cast<std::byte>(0x13), static_cast<std::byte>(0x8f), static_cast<std::byte>(0x0a),
    static_cast<std::byte>(0x08), static_cast<std::byte>(0x97),
    static_cast<std::byte>(0x18), static_cast<std::byte>(0x19), static_cast<std::byte>(0x9c),
    static_cast<std::byte>(0x9d), static_cast<std::byte>(0x1c), static_cast<std::byte>(0x1d),
    static_cast<std::byte>(0x1e), static_cast<std::byte>(0x1f), /*................*/
    /*20*/ static_cast<std::byte>(0x80), static_cast<std::byte>(0x81), static_cast<std::byte>(0x82),
    static_cast<std::byte>(0x83), static_cast<std::byte>(0x84), static_cast<std::byte>(0x92),
    static_cast<std::byte>(0x17), static_cast<std::byte>(0x1b),
    static_cast<std::byte>(0x88), static_cast<std::byte>(0x89), static_cast<std::byte>(0x8a),
    static_cast<std::byte>(0x8b), static_cast<std::byte>(0x8c), static_cast<std::byte>(0x05),
    static_cast<std::byte>(0x06), static_cast<std::byte>(0x07), /*................*/
    /*30*/ static_cast<std::byte>(0x90), static_cast<std::byte>(0x91), static_cast<std::byte>(0x16),
    static_cast<std::byte>(0x93), static_cast<std::byte>(0x94), static_cast<std::byte>(0x95),
    static_cast<std::byte>(0x96), static_cast<std::byte>(0x04),
    static_cast<std::byte>(0x98), static_cast<std::byte>(0x99), static_cast<std::byte>(0x9a),
    static_cast<std::byte>(0x9b), static_cast<std::byte>(0x14), static_cast<std::byte>(0x15),
    static_cast<std::byte>(0x9e), static_cast<std::byte>(0x1a), /*................*/
    /*40*/ static_cast<std::byte>(0x20), static_cast<std::byte>(0xa0), static_cast<std::byte>(0xe2),
    static_cast<std::byte>(0xe4), static_cast<std::byte>(0xe0), static_cast<std::byte>(0xe1),
    static_cast<std::byte>(0xe3), static_cast<std::byte>(0xe5),
    static_cast<std::byte>(0xe7), static_cast<std::byte>(0xf1), static_cast<std::byte>(0x60),
    static_cast<std::byte>(0x2e), static_cast<std::byte>(0x3c), static_cast<std::byte>(0x28),
    static_cast<std::byte>(0x2b), static_cast<std::byte>(0x7c), /* .........`.<(+|*/
    /*50*/ static_cast<std::byte>(0x26), static_cast<std::byte>(0xe9), static_cast<std::byte>(0xea),
    static_cast<std::byte>(0xeb), static_cast<std::byte>(0xe8), static_cast<std::byte>(0xed),
    static_cast<std::byte>(0xee), static_cast<std::byte>(0xef),
    static_cast<std::byte>(0xec), static_cast<std::byte>(0xdf), static_cast<std::byte>(0x21),
    static_cast<std::byte>(0x24), static_cast<std::byte>(0x2a), static_cast<std::byte>(0x29),
    static_cast<std::byte>(0x3b), static_cast<std::byte>(0x5e), /*&.........!$*);^ (VISA: 0x5F->'^')*/
    /*60*/ static_cast<std::byte>(0x2d), static_cast<std::byte>(0x2f), static_cast<std::byte>(0xc2),
    static_cast<std::byte>(0xc4), static_cast<std::byte>(0xc0), static_cast<std::byte>(0xc1),
    static_cast<std::byte>(0xc3), static_cast<std::byte>(0xc5),
    static_cast<std::byte>(0xc7), static_cast<std::byte>(0xd1), static_cast<std::byte>(0x5e),
    static_cast<std::byte>(0x2c), static_cast<std::byte>(0x25), static_cast<std::byte>(0x5f),
    static_cast<std::byte>(0x3e), static_cast<std::byte>(0x3f), /*-/........^,%_>?*/
    /*70*/ static_cast<std::byte>(0xf8), static_cast<std::byte>(0xc9), static_cast<std::byte>(0xca),
    static_cast<std::byte>(0xcb), static_cast<std::byte>(0xc8), static_cast<std::byte>(0xcd),
    static_cast<std::byte>(0xce), static_cast<std::byte>(0xcf),
    static_cast<std::byte>(0xcc), static_cast<std::byte>(0xa8), static_cast<std::byte>(0x3a),
    static_cast<std::byte>(0x23), static_cast<std::byte>(0x40), static_cast<std::byte>(0x27),
    static_cast<std::byte>(0x3d), static_cast<std::byte>(0x22), /*..........:#@'="*/
    /*80*/ static_cast<std::byte>(0xd8), static_cast<std::byte>(0x61), static_cast<std::byte>(0x62),
    static_cast<std::byte>(0x63), static_cast<std::byte>(0x64), static_cast<std::byte>(0x65),
    static_cast<std::byte>(0x66), static_cast<std::byte>(0x67),
    static_cast<std::byte>(0x68), static_cast<std::byte>(0x69), static_cast<std::byte>(0xab),
    static_cast<std::byte>(0xbb), static_cast<std::byte>(0xf0), static_cast<std::byte>(0xfd),
    static_cast<std::byte>(0xfe), static_cast<std::byte>(0xb1), /*.abcdefghi......*/
    /*90*/ static_cast<std::byte>(0xb0), static_cast<std::byte>(0x6a), static_cast<std::byte>(0x6b),
    static_cast<std::byte>(0x6c), static_cast<std::byte>(0x6d), static_cast<std::byte>(0x6e),
    static_cast<std::byte>(0x6f), static_cast<std::byte>(0x70),
    static_cast<std::byte>(0x71), static_cast<std::byte>(0x72), static_cast<std::byte>(0xaa),
    static_cast<std::byte>(0xba), static_cast<std::byte>(0xe6), static_cast<std::byte>(0xb8),
    static_cast<std::byte>(0xc6), static_cast<std::byte>(0xa4), /*.jklmnopqr......*/
    /*a0*/ static_cast<std::byte>(0xb5), static_cast<std::byte>(0xaf), static_cast<std::byte>(0x73),
    static_cast<std::byte>(0x74), static_cast<std::byte>(0x75), static_cast<std::byte>(0x76),
    static_cast<std::byte>(0x77), static_cast<std::byte>(0x78),
    static_cast<std::byte>(0x79), static_cast<std::byte>(0x7a), static_cast<std::byte>(0xa1),
    static_cast<std::byte>(0xbf), static_cast<std::byte>(0xd0), static_cast<std::byte>(0xdd),
    static_cast<std::byte>(0xde), static_cast<std::byte>(0xae), /*..stuvwxyz......*/
    /*b0*/ static_cast<std::byte>(0xa2), static_cast<std::byte>(0xa3), static_cast<std::byte>(0xa5),
    static_cast<std::byte>(0xb7), static_cast<std::byte>(0xa9), static_cast<std::byte>(0xa7),
    static_cast<std::byte>(0xb6), static_cast<std::byte>(0xbc),
    static_cast<std::byte>(0xbd), static_cast<std::byte>(0xbe), static_cast<std::byte>(0xac),
    static_cast<std::byte>(0x5b), static_cast<std::byte>(0x5c), static_cast<std::byte>(0x5d),
    static_cast<std::byte>(0xb4), static_cast<std::byte>(0xd7), /*...........[\]..*/
    /*c0*/ static_cast<std::byte>(0xf9), static_cast<std::byte>(0x41), static_cast<std::byte>(0x42),
    static_cast<std::byte>(0x43), static_cast<std::byte>(0x44), static_cast<std::byte>(0x45),
    static_cast<std::byte>(0x46), static_cast<std::byte>(0x47),
    static_cast<std::byte>(0x48), static_cast<std::byte>(0x49), static_cast<std::byte>(0xad),
    static_cast<std::byte>(0xf4), static_cast<std::byte>(0xf6), static_cast<std::byte>(0xf2),
    static_cast<std::byte>(0xf3), static_cast<std::byte>(0xf5), /*.ABCDEFGHI......*/
    /*d0*/ static_cast<std::byte>(0xa6), static_cast<std::byte>(0x4a), static_cast<std::byte>(0x4b),
    static_cast<std::byte>(0x4c), static_cast<std::byte>(0x4d), static_cast<std::byte>(0x4e),
    static_cast<std::byte>(0x4f), static_cast<std::byte>(0x50),
    static_cast<std::byte>(0x51), static_cast<std::byte>(0x52), static_cast<std::byte>(0xb9),
    static_cast<std::byte>(0xfb), static_cast<std::byte>(0xfc), static_cast<std::byte>(0xdb),
    static_cast<std::byte>(0xfa), static_cast<std::byte>(0xff), /*.JKLMNOPQR......*/
    /*e0*/ static_cast<std::byte>(0xd9), static_cast<std::byte>(0xf7), static_cast<std::byte>(0x53),
    static_cast<std::byte>(0x54), static_cast<std::byte>(0x55), static_cast<std::byte>(0x56),
    static_cast<std::byte>(0x57), static_cast<std::byte>(0x58),
    static_cast<std::byte>(0x59), static_cast<std::byte>(0x5a), static_cast<std::byte>(0xb2),
    static_cast<std::byte>(0xd4), static_cast<std::byte>(0xd6), static_cast<std::byte>(0xd2),
    static_cast<std::byte>(0xd3), static_cast<std::byte>(0xd5), /*..STUVWXYZ......*/
    /*f0*/ static_cast<std::byte>(0x30), static_cast<std::byte>(0x31), static_cast<std::byte>(0x32),
    static_cast<std::byte>(0x33), static_cast<std::byte>(0x34), static_cast<std::byte>(0x35),
    static_cast<std::byte>(0x36), static_cast<std::byte>(0x37),
    static_cast<std::byte>(0x38), static_cast<std::byte>(0x39), static_cast<std::byte>(0xb3),
    static_cast<std::byte>(0x7b), static_cast<std::byte>(0xdc), static_cast<std::byte>(0x7d),
    static_cast<std::byte>(0xda), static_cast<std::byte>(0x7e) /*0123456789.{.}.~*/
};

} // namespace

auto hex_to_bytes(const std::string_view value) -> std::vector<std::byte> {
    const std::size_t bin_length = value.length() / 2;
    std::vector<std::byte> packed_bytes(bin_length);

    for (std::size_t i = 0, j = 0; i < bin_length; i++, j++) {
        packed_bytes[j] =
            static_cast<std::byte>(std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
                                   std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])]));
    }

    return packed_bytes;
}

void hex_to_bytes(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index) {
    const std::size_t bin_length = value.length() / 2;

    for (std::size_t i = 0, j = index; i < bin_length; i++, j++) {
        packed_bytes[j] =
            static_cast<std::byte>(std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
                                   std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])]));
    }

    index += bin_length;
}

auto bytes_to_hex(const std::span<const std::byte> bytes) -> std::string {
    static constexpr std::array HEX_DIGITS{'0', '1', '2', '3', '4', '5', '6', '7',
                                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    const std::size_t n = bytes.size();
    std::string out(n * 2, '0');
    char* dst = out.data();

    std::size_t i = 0;
    std::size_t o = 0;

    // Process 4 bytes per iteration (unrolled loop for throughput / ILP).
    for (const std::size_t n4 = n & ~static_cast<std::size_t>(3); i < n4; i += 4) {
        const auto v0 = std::to_integer<unsigned>(bytes[i]);
        dst[o++] = HEX_DIGITS[v0 >> 4 & 0x0F];
        dst[o++] = HEX_DIGITS[v0 & 0x0F];

        const auto v1 = std::to_integer<unsigned>(bytes[i + 1]);
        dst[o++] = HEX_DIGITS[v1 >> 4 & 0x0F];
        dst[o++] = HEX_DIGITS[v1 & 0x0F];

        const auto v2 = std::to_integer<unsigned>(bytes[i + 2]);
        dst[o++] = HEX_DIGITS[v2 >> 4 & 0x0F];
        dst[o++] = HEX_DIGITS[v2 & 0x0F];

        const auto v3 = std::to_integer<unsigned>(bytes[i + 3]);
        dst[o++] = HEX_DIGITS[v3 >> 4 & 0x0F];
        dst[o++] = HEX_DIGITS[v3 & 0x0F];
    }

    // Tail for remaining 0..3 bytes.
    for (; i < n; ++i) {
        const auto v = std::to_integer<unsigned>(bytes[i]);
        dst[o++] = HEX_DIGITS[v >> 4 & 0x0F];
        dst[o++] = HEX_DIGITS[v & 0x0F];
    }

    return out;
}

auto bytes_to_hex(const std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t num_bytes)
    -> std::string {
    static constexpr std::array HEX_DIGITS = {'0', '1', '2', '3', '4', '5', '6', '7',
                                              '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    std::string result(num_bytes * 2, '0');
    char* dst = result.data();
    std::size_t out_pos = 0;

    for (std::size_t i = 0; i < num_bytes; ++i) {
        const auto v = std::to_integer<unsigned>(packed_bytes[index + i]);
        dst[out_pos++] = HEX_DIGITS[v >> 4 & 0x0F];
        dst[out_pos++] = HEX_DIGITS[v & 0x0F];
    }

    index += num_bytes;
    return result;
}

void int_to_bytes(const int32_t value, std::span<std::byte> packed_bytes, std::size_t& index,
                  const std::size_t byte_width) {
    for (std::size_t i = 0; i < byte_width; i++) {
        packed_bytes[index + i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
    }
    index += byte_width;
}

auto int_to_bytes(const int32_t value, const std::size_t byte_width) -> std::vector<std::byte> {
    std::vector<std::byte> result(byte_width);

    for (std::size_t i = 0; i < byte_width; i++) {
        result[i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
    }

    return result;
}

void int_to_bcd(int32_t value, std::span<std::byte> packed_bytes, std::size_t& index, const std::size_t digit_count) {
    if ((digit_count & 1u) != 0u) {
        throw std::invalid_argument("int_to_bcd: num_digits must be even");
    }

    const std::size_t len = digit_count / 2;

    if (index + len > packed_bytes.size()) {
        throw std::out_of_range("int_to_bcd: destination span too small");
    }

    for (std::size_t offset = 0; offset < len; ++offset) {
        const int32_t digit_pair = value % 100;
        value /= 100;

        const int32_t bcd = (digit_pair / 10) << 4 | digit_pair % 10;

        const std::size_t target = index + (len - 1 - offset);
        packed_bytes[target] = static_cast<std::byte>(bcd & 0xFF);
    }

    index += len;
}

auto int_to_bcd(int32_t value, const std::size_t digit_count) -> std::vector<std::byte> {
    if ((digit_count & 1u) != 0u)
        throw std::invalid_argument("int_to_bcd: num_digits must be even");

    const std::size_t len = digit_count / 2;
    std::vector<std::byte> result(len);

    for (std::size_t offset = 0; offset < len; ++offset) {
        const int32_t digit = value % 100;
        value /= 100;

        const int32_t bcd = (digit / 10) << 4 | digit % 10;
        const std::size_t pos = len - 1 - offset;

        result[pos] = static_cast<std::byte>(bcd);
    }

    return result;
}

auto int_to_bcd(uint64_t value, const std::size_t digit_count) -> std::vector<std::byte> {
    if ((digit_count & 1u) != 0u)
        throw std::invalid_argument("int_to_bcd: num_digits must be even");

    const std::size_t len = digit_count / 2;
    std::vector<std::byte> result(len);

    for (std::size_t offset = 0; offset < len; ++offset) {
        const uint64_t digit = value % 100;
        value /= 100;

        const auto bcd = static_cast<uint8_t>((digit / 10) << 4 | digit % 10);
        const std::size_t pos = len - 1 - offset;

        result[pos] = static_cast<std::byte>(bcd);
    }

    return result;
}

auto bcd_to_uint64(std::span<const std::byte> packed_bytes, const std::size_t digit_count) -> uint64_t {
    uint64_t result = 0;
    const std::size_t len = digit_count / 2;

    for (std::size_t i = 0; i < len; ++i) {
        const auto byte_val = static_cast<uint8_t>(packed_bytes[i]);
        const uint64_t high = byte_val >> 4 & 0xF;
        const uint64_t low = byte_val & 0xF;
        result = result * 100 + high * 10 + low;
    }

    return result;
}

void ascii_to_bcd(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index,
                  const FieldPadding padding) {
    auto value_length = value.length();
    std::size_t start_index = 0;
    const bool need_padding = value_length % 2 != 0;

    if (need_padding && padding == FieldPadding::LEFT) {
        packed_bytes[index++] = static_cast<std::byte>(value[0] - 0x30);
        start_index++;
    } else if (need_padding && padding == FieldPadding::RIGHT) {
        value_length--;
    }

    for (std::size_t i = start_index; i < value_length; i += 2) {
        packed_bytes[index++] = static_cast<std::byte>((value[i] - 0x30) * 0x10 + value[i + 1] - 0x30);
    }

    if (need_padding && padding == FieldPadding::RIGHT) {
        packed_bytes[index++] = static_cast<std::byte>((value[value_length] - 0x30) * 0x10);
    }
}

auto ascii_to_bcd(const std::string_view value, const FieldPadding padding) -> std::vector<std::byte> {
    const std::size_t digit_count = value.size();
    const bool odd = (digit_count & 1u) != 0u;

    for (unsigned char c : value) {
        if (c < '0' || c > '9') {
            throw std::invalid_argument("ascii_to_bcd: non-decimal character in input");
        }
    }

    const std::size_t bcd_len = (digit_count + 1) / 2;
    std::vector<std::byte> result(bcd_len);

    std::size_t src_i = 0;
    std::size_t dst_i = 0;

    if (odd && padding == FieldPadding::LEFT) {
        const auto d = static_cast<unsigned>(value[0] - '0');
        result[dst_i++] = static_cast<std::byte>(d);
        src_i = 1;
    }

    while (src_i + 1 < digit_count) {
        const auto d1 = static_cast<unsigned>(value[src_i] - '0');
        const auto d2 = static_cast<unsigned>(value[src_i + 1] - '0');
        result[dst_i++] = static_cast<std::byte>((d1 << 4) | d2);
        src_i += 2;
    }

    if (odd && padding == FieldPadding::RIGHT) {
        const auto d = static_cast<unsigned>(value[src_i] - '0');
        result[dst_i++] = static_cast<std::byte>(d << 4);
    }

    return result;
}

void ascii_to_bytes(std::string_view str_ascii_string, std::span<std::byte> packed_bytes, std::size_t& index) {
    const auto len = str_ascii_string.length();

    for (std::size_t i = 0; i < len; i++)
        packed_bytes[index + i] = static_cast<std::byte>(str_ascii_string[i]);

    index += len;
}

auto ascii_to_bytes(std::string_view str_ascii_string) -> std::vector<std::byte> {
    const std::size_t len = str_ascii_string.length();
    std::vector<std::byte> result(len);

    for (std::size_t i = 0; i < len; ++i) {
        result[i] = static_cast<std::byte>(str_ascii_string[i]);
    }

    return result;
}

void ascii_to_ebcdic(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index) {
    const auto src_length = value.length();

    for (std::size_t i = 0; i < src_length; i++) {
        packed_bytes[index + i] = ascii_to_ebcdic_table[static_cast<unsigned char>(value[i])];
    }

    index += src_length;
}

auto ascii_to_ebcdic(const std::string_view value) -> std::vector<std::byte> {
    const auto src_length = value.length();
    std::vector<std::byte> result(src_length);

    for (std::size_t i = 0; i < src_length; i++) {
        result[i] = ascii_to_ebcdic_table[static_cast<unsigned char>(value[i])];
    }

    return result;
}

void ascii_to_ebcdic_visa(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index) {
    const auto src_length = value.length();

    for (std::size_t i = 0; i < src_length; i++) {
        packed_bytes[index + i] = ascii_to_ebcdic_visa_table[static_cast<unsigned char>(value[i])];
    }

    index += src_length;
}

auto ascii_to_ebcdic_visa(const std::string_view value) -> std::vector<std::byte> {
    const auto src_length = value.length();
    std::vector<std::byte> result(src_length);

    for (std::size_t i = 0; i < src_length; i++) {
        result[i] = ascii_to_ebcdic_visa_table[static_cast<unsigned char>(value[i])];
    }

    return result;
}

auto bytes_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t byte_width)
    -> int32_t {
    int32_t result = 0;
    std::size_t pos = (byte_width / 2 - 1) * 8;

    for (std::size_t i = 0; i < byte_width / 2; i++) {
        result |= static_cast<int32_t>(packed_bytes[index + i]) << pos;
        pos -= 8;
    }

    index += byte_width / 2;
    return result;
}

auto bytes_to_int(std::span<const std::byte> packed_bytes, const std::size_t byte_width) -> int32_t {
    int32_t result = 0;
    std::size_t pos = (byte_width / 2 - 1) * 8;

    for (std::size_t i = 0; i < byte_width / 2; i++) {
        result |= static_cast<int32_t>(packed_bytes[i]) << pos;
        pos -= 8;
    }

    return result;
}

auto bcd_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t digit_count) -> int32_t {
    int32_t result = 0;
    const std::size_t len = digit_count / 2;

    for (std::size_t i = 0; i < len; ++i) {
        const auto byte_val = static_cast<int32_t>(packed_bytes[index + i]);
        const int32_t high = byte_val >> 4 & 0xF;
        const int32_t low = byte_val & 0xF;
        result = result * 100 + high * 10 + low;
    }

    index += len;
    return result;
}

auto bcd_to_int(std::span<const std::byte> packed_bytes, const std::size_t digit_count) -> int32_t {
    int32_t result = 0;
    const std::size_t len = digit_count / 2;

    for (std::size_t i = 0; i < len; ++i) {
        const auto byte_val = static_cast<int32_t>(packed_bytes[i]);
        const int32_t high = byte_val >> 4 & 0xF;
        const int32_t low = byte_val & 0xF;
        result = result * 100 + high * 10 + low;
    }

    return result;
}

auto bcd_to_ascii(const std::span<const std::byte> packed_bytes, std::size_t& index, const FieldPadding padding,
                  const std::size_t digit_count) -> std::string {
    std::string value(digit_count, '0');

    if (digit_count % 2 != 0) {
        if (padding == FieldPadding::LEFT) {
            auto byte_val = std::to_integer<unsigned>(packed_bytes[index]);
            value[0] = static_cast<char>((byte_val & 0x0F) + '0');
            index++;

            for (std::size_t i = 1; i < digit_count; i += 2) {
                byte_val = std::to_integer<unsigned>(packed_bytes[index]);
                value[i] = static_cast<char>((byte_val >> 4) + '0');
                value[i + 1] = static_cast<char>((byte_val & 0x0F) + '0');
                index++;
            }
        } else {
            std::size_t i;
            for (i = 0; i < digit_count - 1; i += 2) {
                const auto byte_val = std::to_integer<unsigned>(packed_bytes[index]);
                value[i] = static_cast<char>((byte_val >> 4) + '0');
                value[i + 1] = static_cast<char>((byte_val & 0x0F) + '0');
                index++;
            }
            const auto byte_val = std::to_integer<unsigned>(packed_bytes[index]);
            value[i] = static_cast<char>((byte_val >> 4) + '0');
            index++;
        }
    } else {
        for (std::size_t i = 0; i < digit_count; i += 2) {
            const auto byte_val = std::to_integer<unsigned>(packed_bytes[index]);
            value[i] = static_cast<char>((byte_val >> 4) + '0');
            value[i + 1] = static_cast<char>((byte_val & 0x0F) + '0');
            index++;
        }
    }
    return value;
}

auto bcd_to_ascii(const std::span<const std::byte> packed_bytes, const FieldPadding padding,
                  const std::size_t digit_count) -> std::string {
    std::size_t index = 0;
    return bcd_to_ascii(packed_bytes, index, padding, digit_count);
}

auto bytes_to_ascii(std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t byte_count)
    -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++)
        result[i] = static_cast<char>(packed_bytes[index + i]);

    index += byte_count;
    return result;
}

auto bytes_to_ascii(std::span<const std::byte> packed_bytes, const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++)
        result[i] = static_cast<char>(packed_bytes[i]);

    return result;
}

auto ebcdic_to_ascii(const std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t byte_count)
    -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++) {
        const auto ebcdic_byte = std::to_integer<unsigned>(packed_bytes[index + i]);
        result[i] = static_cast<char>(ebcdic_to_ascii_table[ebcdic_byte]);
    }

    index += byte_count;
    return result;
}

auto ebcdic_to_ascii(const std::span<const std::byte> packed_bytes, const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++) {
        const auto ebcdic_byte = std::to_integer<unsigned>(packed_bytes[i]);
        result[i] = static_cast<char>(ebcdic_to_ascii_table[ebcdic_byte]);
    }

    return result;
}

// ============================================================================
// EBCDIC VISA Variant Conversions
// ============================================================================

auto ebcdic_to_ascii_visa(const std::span<const std::byte> packed_bytes, std::size_t& index,
                          const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++) {
        const auto ebcdic_byte = std::to_integer<unsigned>(packed_bytes[index + i]);
        result[i] = static_cast<char>(ebcdic_to_ascii_visa_table[ebcdic_byte]);
    }

    index += byte_count;
    return result;
}

auto ebcdic_to_ascii_visa(const std::span<const std::byte> packed_bytes, const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++) {
        const auto ebcdic_byte = std::to_integer<unsigned>(packed_bytes[i]);
        result[i] = static_cast<char>(ebcdic_to_ascii_visa_table[ebcdic_byte]);
    }

    return result;
}

// ============================================================================
// EBCDIC Numeric Conversions
// ============================================================================

void int_to_ebcdic(const int64_t value, std::span<std::byte> packed_bytes, std::size_t& index,
                   const std::size_t digit_count) {
    // EBCDIC digits: '0' = 0xF0, '1' = 0xF1, ..., '9' = 0xF9
    constexpr std::byte EBCDIC_ZERO{0xF0};

    // Convert to positive value for digit extraction
    auto abs_value = static_cast<uint64_t>(value < 0 ? -value : value);

    // Extract digits in reverse order, then write left-to-right
    std::array<std::byte, 20> digits{}; // Max 20 digits for int64
    std::size_t digit_pos = digit_count;

    while (digit_pos > 0 && abs_value > 0) {
        --digit_pos;
        digits[digit_pos] =
            static_cast<std::byte>(std::to_integer<uint8_t>(EBCDIC_ZERO) + static_cast<uint8_t>(abs_value % 10));
        abs_value /= 10;
    }

    // Fill remaining positions with EBCDIC '0'
    while (digit_pos > 0) {
        --digit_pos;
        digits[digit_pos] = EBCDIC_ZERO;
    }

    // Copy to output buffer
    for (std::size_t i = 0; i < digit_count; ++i) {
        packed_bytes[index + i] = digits[i];
    }

    index += digit_count;
}

auto int_to_ebcdic(const int64_t value, const std::size_t digit_count) -> std::vector<std::byte> {
    std::vector<std::byte> result(digit_count);
    std::size_t index = 0;
    int_to_ebcdic(value, result, index, digit_count);
    return result;
}

auto ebcdic_to_int(const std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t digit_count)
    -> int64_t {
    // EBCDIC digits: '0' = 0xF0, '1' = 0xF1, ..., '9' = 0xF9
    constexpr uint8_t EBCDIC_ZERO = 0xF0;
    constexpr uint8_t EBCDIC_NINE = 0xF9;

    int64_t result = 0;

    for (std::size_t i = 0; i < digit_count; ++i) {
        const auto byte_val = std::to_integer<uint8_t>(packed_bytes[index + i]);

        // Validate it's an EBCDIC digit
        if (byte_val >= EBCDIC_ZERO && byte_val <= EBCDIC_NINE) {
            result = result * 10 + static_cast<int64_t>(byte_val - EBCDIC_ZERO);
        } else {
            // Not a valid EBCDIC digit - treat as 0 or throw?
            // For robustness, treat invalid bytes as 0
            result = result * 10;
        }
    }

    index += digit_count;
    return result;
}

auto ebcdic_to_int(const std::span<const std::byte> packed_bytes, const std::size_t digit_count) -> int64_t {
    std::size_t index = 0;
    return ebcdic_to_int(packed_bytes, index, digit_count);
}

} // namespace codemorph
