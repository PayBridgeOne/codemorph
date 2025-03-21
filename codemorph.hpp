#ifndef CODEMORPH_LIBRARY_H
#define CODEMORPH_LIBRARY_H

#include <array>
#include <string>
#include <span>
#include <vector>

class CodeMorph {
public:
       enum class FieldPadding { LEFT, RIGHT, NONE };
       static std::vector<std::byte> test_hex_to_bytes(const std::string& value);
       static void int_to_bytes(int value, std::span<std::byte> &packedBytes, int &index, int numHexDigits);
       static void int_to_bcd(int value, std::span<std::byte> &packedBytes, int &index, int numBytes);
       static void ascii_to_bcd(const std::string &value, std::span<std::byte> &packedBytes, int &index, FieldPadding padding);
       static void ascii_to_bytes(const std::string &strASCIIString, std::span<std::byte> &packedBytes, size_t &index);
       static void hex_to_bytes(const std::string &value, std::vector<std::byte> &packedBytes, size_t &index);
       static void ascii_to_ebcdic(const std::string &value, std::span<std::byte> &packedBytes, size_t &index);
       static int bytes_to_int(const std::span<std::byte> &packedBytes, int &index, int numHexDigits);
       static int bcd_to_int(std::span<const std::byte> packed_bytes, int& index, int num_hex_digits);
       static std::string bcd_to_ascii(std::span<const std::byte> packedBytes, int& index, FieldPadding padding, int valueLength);
       static std::string bytes_to_ascii(std::span<const std::byte> packedBytes, int& index, int numBytes);
       static std::string bytes_to_hex(std::span<const std::byte> packedBytes, int& index, int numBytes);
       static std::string bytes_to_hex(std::span<const std::byte> bytes, int length);
       static std::string ebcdic_to_ascii(std::span<const std::byte> packedBytes, int& index, int numBytes);
private:
       static constexpr  std::array<std::byte, 144> hex_lookup = {
           /* 00-0F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           /* 10-1F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           /* 20-2F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           /* 30-3F */ std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}, std::byte{5}, std::byte{6}, std::byte{7},
           std::byte{8}, std::byte{9}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},  // '0' - '9'
           /* 40-4F */ std::byte{0}, std::byte{10}, std::byte{11}, std::byte{12}, std::byte{13}, std::byte{14}, std::byte{15}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, // 'A' - 'F'
           /* 50-5F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           /* 60-6F */ std::byte{0}, std::byte{10}, std::byte{11}, std::byte{12}, std::byte{13}, std::byte{14}, std::byte{15}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, // 'a' - 'f'
           /* 70-7F */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           /* 80-FF */ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
           std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}
       };
       static constexpr std::array<std::string, 256> hex_string_lookup = {
              "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F",
              "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1A", "1B", "1C", "1D", "1E", "1F",
              "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2A", "2B", "2C", "2D", "2E", "2F",
              "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3A", "3B", "3C", "3D", "3E", "3F",
              "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4A", "4B", "4C", "4D", "4E", "4F",
              "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5A", "5B", "5C", "5D", "5E", "5F",
              "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6A", "6B", "6C", "6D", "6E", "6F",
              "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7A", "7B", "7C", "7D", "7E", "7F",
              "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8A", "8B", "8C", "8D", "8E", "8F",
              "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9A", "9B", "9C", "9D", "9E", "9F",
              "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "AA", "AB", "AC", "AD", "AE", "AF",
              "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "BA", "BB", "BC", "BD", "BE", "BF",
              "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CA", "CB", "CC", "CD", "CE", "CF",
              "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DA", "DB", "DC", "DD", "DE", "DF",
              "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "EA", "EB", "EC", "ED", "EE", "EF",
              "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "FA", "FB", "FC", "FD", "FE", "FF"
       };
       static constexpr std::array<std::byte, 256> ascii_to_ebcdic_table = {
              /*00*/ static_cast<std::byte>(0x00), static_cast<std::byte>(0x01), static_cast<std::byte>(0x02), static_cast<std::byte>(0x03), static_cast<std::byte>(0x37), static_cast<std::byte>(0x2d), static_cast<std::byte>(0x2e), static_cast<std::byte>(0x2f),
              static_cast<std::byte>(0x16), static_cast<std::byte>(0x05), static_cast<std::byte>(0x15), static_cast<std::byte>(0x0b), static_cast<std::byte>(0x0c), static_cast<std::byte>(0x0d), static_cast<std::byte>(0x0e), static_cast<std::byte>(0x0f),  /*................*/
              /*10*/ static_cast<std::byte>(0x10), static_cast<std::byte>(0x11), static_cast<std::byte>(0x12), static_cast<std::byte>(0x13), static_cast<std::byte>(0x3c), static_cast<std::byte>(0x3d), static_cast<std::byte>(0x32), static_cast<std::byte>(0x26),
              static_cast<std::byte>(0x18), static_cast<std::byte>(0x19), static_cast<std::byte>(0x3f), static_cast<std::byte>(0x27), static_cast<std::byte>(0x1c), static_cast<std::byte>(0x1d), static_cast<std::byte>(0x1e), static_cast<std::byte>(0x1f),  /*................*/
              /*20*/ static_cast<std::byte>(0x40), static_cast<std::byte>(0x5a), static_cast<std::byte>(0x7f), static_cast<std::byte>(0x7b), static_cast<std::byte>(0x5b), static_cast<std::byte>(0x6c), static_cast<std::byte>(0x50), static_cast<std::byte>(0x7d),
              static_cast<std::byte>(0x4d), static_cast<std::byte>(0x5d), static_cast<std::byte>(0x5c), static_cast<std::byte>(0x4e), static_cast<std::byte>(0x6b), static_cast<std::byte>(0x60), static_cast<std::byte>(0x4b), static_cast<std::byte>(0x61),  /* !"#$%&'()*+,-./ */
              /*30*/ static_cast<std::byte>(0xf0), static_cast<std::byte>(0xf1), static_cast<std::byte>(0xf2), static_cast<std::byte>(0xf3), static_cast<std::byte>(0xf4), static_cast<std::byte>(0xf5), static_cast<std::byte>(0xf6), static_cast<std::byte>(0xf7),
              static_cast<std::byte>(0xf8), static_cast<std::byte>(0xf9), static_cast<std::byte>(0x7a), static_cast<std::byte>(0x5e), static_cast<std::byte>(0x4c), static_cast<std::byte>(0x7e), static_cast<std::byte>(0x6e), static_cast<std::byte>(0x6f),  /*0123456789:;<=>?*/
              /*40*/ static_cast<std::byte>(0x7c), static_cast<std::byte>(0xc1), static_cast<std::byte>(0xc2), static_cast<std::byte>(0xc3), static_cast<std::byte>(0xc4), static_cast<std::byte>(0xc5), static_cast<std::byte>(0xc6), static_cast<std::byte>(0xc7),
              static_cast<std::byte>(0xc8), static_cast<std::byte>(0xc9), static_cast<std::byte>(0xd1), static_cast<std::byte>(0xd2), static_cast<std::byte>(0xd3), static_cast<std::byte>(0xd4), static_cast<std::byte>(0xd5), static_cast<std::byte>(0xd6),  /*@ABCDEFGHIJKLMNO*/
              /*50*/ static_cast<std::byte>(0xd7), static_cast<std::byte>(0xd8), static_cast<std::byte>(0xd9), static_cast<std::byte>(0xe2), static_cast<std::byte>(0xe3), static_cast<std::byte>(0xe4), static_cast<std::byte>(0xe5), static_cast<std::byte>(0xe6),
              static_cast<std::byte>(0xe7), static_cast<std::byte>(0xe8), static_cast<std::byte>(0xe9), static_cast<std::byte>(0xbb), static_cast<std::byte>(0xbc), static_cast<std::byte>(0xbd), static_cast<std::byte>(0x6a), static_cast<std::byte>(0x6d),  /*PQRSTUVWXYZ[\]^_*/
              /*60*/ static_cast<std::byte>(0x4a), static_cast<std::byte>(0x81), static_cast<std::byte>(0x82), static_cast<std::byte>(0x83), static_cast<std::byte>(0x84), static_cast<std::byte>(0x85), static_cast<std::byte>(0x86), static_cast<std::byte>(0x87),
              static_cast<std::byte>(0x88), static_cast<std::byte>(0x89), static_cast<std::byte>(0x91), static_cast<std::byte>(0x92), static_cast<std::byte>(0x93), static_cast<std::byte>(0x94), static_cast<std::byte>(0x95), static_cast<std::byte>(0x96),  /*`abcdefghijklmno*/
              /*70*/ static_cast<std::byte>(0x97), static_cast<std::byte>(0x98), static_cast<std::byte>(0x99), static_cast<std::byte>(0xa2), static_cast<std::byte>(0xa3), static_cast<std::byte>(0xa4), static_cast<std::byte>(0xa5), static_cast<std::byte>(0xa6),
              static_cast<std::byte>(0xa7), static_cast<std::byte>(0xa8), static_cast<std::byte>(0xa9), static_cast<std::byte>(0xfb), static_cast<std::byte>(0x4f), static_cast<std::byte>(0xfd), static_cast<std::byte>(0xff), static_cast<std::byte>(0x07),  /*pqrstuvwxyz{|}~.*/
              /*80*/ static_cast<std::byte>(0x20), static_cast<std::byte>(0x21), static_cast<std::byte>(0x22), static_cast<std::byte>(0x23), static_cast<std::byte>(0x24), static_cast<std::byte>(0x04), static_cast<std::byte>(0x06), static_cast<std::byte>(0x08),
              static_cast<std::byte>(0x28), static_cast<std::byte>(0x29), static_cast<std::byte>(0x2a), static_cast<std::byte>(0x2b), static_cast<std::byte>(0x2c), static_cast<std::byte>(0x09), static_cast<std::byte>(0x0a), static_cast<std::byte>(0x14),  /*................*/
              /*90*/ static_cast<std::byte>(0x30), static_cast<std::byte>(0x31), static_cast<std::byte>(0x25), static_cast<std::byte>(0x33), static_cast<std::byte>(0x34), static_cast<std::byte>(0x35), static_cast<std::byte>(0x36), static_cast<std::byte>(0x17),
              static_cast<std::byte>(0x38), static_cast<std::byte>(0x39), static_cast<std::byte>(0x3a), static_cast<std::byte>(0x3b), static_cast<std::byte>(0x1a), static_cast<std::byte>(0x1b), static_cast<std::byte>(0x3e), static_cast<std::byte>(0x5f),  /*................*/
              /*a0*/ static_cast<std::byte>(0x41), static_cast<std::byte>(0xaa), static_cast<std::byte>(0xb0), static_cast<std::byte>(0xb1), static_cast<std::byte>(0x9f), static_cast<std::byte>(0xb2), static_cast<std::byte>(0xd0), static_cast<std::byte>(0xb5),
              static_cast<std::byte>(0x79), static_cast<std::byte>(0xb4), static_cast<std::byte>(0x9a), static_cast<std::byte>(0x8a), static_cast<std::byte>(0xba), static_cast<std::byte>(0xca), static_cast<std::byte>(0xaf), static_cast<std::byte>(0xa1),  /*................*/
              /*b0*/ static_cast<std::byte>(0x90), static_cast<std::byte>(0x8f), static_cast<std::byte>(0xea), static_cast<std::byte>(0xfa), static_cast<std::byte>(0xbe), static_cast<std::byte>(0xa0), static_cast<std::byte>(0xb6), static_cast<std::byte>(0xb3),
              static_cast<std::byte>(0x9d), static_cast<std::byte>(0xda), static_cast<std::byte>(0x9b), static_cast<std::byte>(0x8b), static_cast<std::byte>(0xb7), static_cast<std::byte>(0xb8), static_cast<std::byte>(0xb9), static_cast<std::byte>(0xab),  /*................*/
              /*c0*/ static_cast<std::byte>(0x64), static_cast<std::byte>(0x65), static_cast<std::byte>(0x62), static_cast<std::byte>(0x66), static_cast<std::byte>(0x63), static_cast<std::byte>(0x67), static_cast<std::byte>(0x9e), static_cast<std::byte>(0x68),
              static_cast<std::byte>(0x74), static_cast<std::byte>(0x71), static_cast<std::byte>(0x72), static_cast<std::byte>(0x73), static_cast<std::byte>(0x78), static_cast<std::byte>(0x75), static_cast<std::byte>(0x76), static_cast<std::byte>(0x77),  /*................*/
              /*d0*/ static_cast<std::byte>(0xac), static_cast<std::byte>(0x69), static_cast<std::byte>(0xed), static_cast<std::byte>(0xee), static_cast<std::byte>(0xeb), static_cast<std::byte>(0xef), static_cast<std::byte>(0xec), static_cast<std::byte>(0xbf),
              static_cast<std::byte>(0x80), static_cast<std::byte>(0xe0), static_cast<std::byte>(0xfe), static_cast<std::byte>(0xdd), static_cast<std::byte>(0xfc), static_cast<std::byte>(0xad), static_cast<std::byte>(0xae), static_cast<std::byte>(0x59),  /*................*/
              /*e0*/ static_cast<std::byte>(0x44), static_cast<std::byte>(0x45), static_cast<std::byte>(0x42), static_cast<std::byte>(0x46), static_cast<std::byte>(0x43), static_cast<std::byte>(0x47), static_cast<std::byte>(0x9c), static_cast<std::byte>(0x48),
              static_cast<std::byte>(0x54), static_cast<std::byte>(0x51), static_cast<std::byte>(0x52), static_cast<std::byte>(0x53), static_cast<std::byte>(0x58), static_cast<std::byte>(0x55), static_cast<std::byte>(0x56), static_cast<std::byte>(0x57),  /*................*/
              /*f0*/ static_cast<std::byte>(0x8c), static_cast<std::byte>(0x49), static_cast<std::byte>(0xcd), static_cast<std::byte>(0xce), static_cast<std::byte>(0xcb), static_cast<std::byte>(0xcf), static_cast<std::byte>(0xcc), static_cast<std::byte>(0xe1),
              static_cast<std::byte>(0x70), static_cast<std::byte>(0xc0), static_cast<std::byte>(0xde), static_cast<std::byte>(0xdb), static_cast<std::byte>(0xdc), static_cast<std::byte>(0x8d), static_cast<std::byte>(0x8e), static_cast<std::byte>(0xdf)   /*................*/
       };
       static constexpr std::array<std::byte, 256> ebcdic_to_ascii_table  = {
              /*00*/ static_cast<std::byte>(0x00), static_cast<std::byte>(0x01), static_cast<std::byte>(0x02), static_cast<std::byte>(0x03), static_cast<std::byte>(0x85), static_cast<std::byte>(0x09), static_cast<std::byte>(0x86), static_cast<std::byte>(0x7f),
              static_cast<std::byte>(0x87), static_cast<std::byte>(0x8d), static_cast<std::byte>(0x8e), static_cast<std::byte>(0x0b), static_cast<std::byte>(0x0c), static_cast<std::byte>(0x0d), static_cast<std::byte>(0x0e), static_cast<std::byte>(0x0f), /*................*/
              /*10*/ static_cast<std::byte>(0x10), static_cast<std::byte>(0x11), static_cast<std::byte>(0x12), static_cast<std::byte>(0x13), static_cast<std::byte>(0x8f), static_cast<std::byte>(0x0a), static_cast<std::byte>(0x08), static_cast<std::byte>(0x97),
              static_cast<std::byte>(0x18), static_cast<std::byte>(0x19), static_cast<std::byte>(0x9c), static_cast<std::byte>(0x9d), static_cast<std::byte>(0x1c), static_cast<std::byte>(0x1d), static_cast<std::byte>(0x1e), static_cast<std::byte>(0x1f), /*................*/
              /*20*/ static_cast<std::byte>(0x80), static_cast<std::byte>(0x81), static_cast<std::byte>(0x82), static_cast<std::byte>(0x83), static_cast<std::byte>(0x84), static_cast<std::byte>(0x92), static_cast<std::byte>(0x17), static_cast<std::byte>(0x1b),
              static_cast<std::byte>(0x88), static_cast<std::byte>(0x89), static_cast<std::byte>(0x8a), static_cast<std::byte>(0x8b), static_cast<std::byte>(0x8c), static_cast<std::byte>(0x05), static_cast<std::byte>(0x06), static_cast<std::byte>(0x07), /*................*/
              /*30*/ static_cast<std::byte>(0x90), static_cast<std::byte>(0x91), static_cast<std::byte>(0x16), static_cast<std::byte>(0x93), static_cast<std::byte>(0x94), static_cast<std::byte>(0x95), static_cast<std::byte>(0x96), static_cast<std::byte>(0x04),
              static_cast<std::byte>(0x98), static_cast<std::byte>(0x99), static_cast<std::byte>(0x9a), static_cast<std::byte>(0x9b), static_cast<std::byte>(0x14), static_cast<std::byte>(0x15), static_cast<std::byte>(0x9e), static_cast<std::byte>(0x1a), /*................*/
              /*40*/ static_cast<std::byte>(0x20), static_cast<std::byte>(0xa0), static_cast<std::byte>(0xe2), static_cast<std::byte>(0xe4), static_cast<std::byte>(0xe0), static_cast<std::byte>(0xe1), static_cast<std::byte>(0xe3), static_cast<std::byte>(0xe5),
              static_cast<std::byte>(0xe7), static_cast<std::byte>(0xf1), static_cast<std::byte>(0x60), static_cast<std::byte>(0x2e), static_cast<std::byte>(0x3c), static_cast<std::byte>(0x28), static_cast<std::byte>(0x2b), static_cast<std::byte>(0x7c), /* .........`.<(+|*/
              /*50*/ static_cast<std::byte>(0x26), static_cast<std::byte>(0xe9), static_cast<std::byte>(0xea), static_cast<std::byte>(0xeb), static_cast<std::byte>(0xe8), static_cast<std::byte>(0xed), static_cast<std::byte>(0xee), static_cast<std::byte>(0xef),
              static_cast<std::byte>(0xec), static_cast<std::byte>(0xdf), static_cast<std::byte>(0x21), static_cast<std::byte>(0x24), static_cast<std::byte>(0x2a), static_cast<std::byte>(0x29), static_cast<std::byte>(0x3b), static_cast<std::byte>(0x9f), /*&.........!$*);.*/
              /*60*/ static_cast<std::byte>(0x2d), static_cast<std::byte>(0x2f), static_cast<std::byte>(0xc2), static_cast<std::byte>(0xc4), static_cast<std::byte>(0xc0), static_cast<std::byte>(0xc1), static_cast<std::byte>(0xc3), static_cast<std::byte>(0xc5),
              static_cast<std::byte>(0xc7), static_cast<std::byte>(0xd1), static_cast<std::byte>(0x5e), static_cast<std::byte>(0x2c), static_cast<std::byte>(0x25), static_cast<std::byte>(0x5f), static_cast<std::byte>(0x3e), static_cast<std::byte>(0x3f), /*-/........^,%_>?*/
              /*70*/ static_cast<std::byte>(0xf8), static_cast<std::byte>(0xc9), static_cast<std::byte>(0xca), static_cast<std::byte>(0xcb), static_cast<std::byte>(0xc8), static_cast<std::byte>(0xcd), static_cast<std::byte>(0xce), static_cast<std::byte>(0xcf),
              static_cast<std::byte>(0xcc), static_cast<std::byte>(0xa8), static_cast<std::byte>(0x3a), static_cast<std::byte>(0x23), static_cast<std::byte>(0x40), static_cast<std::byte>(0x27), static_cast<std::byte>(0x3d), static_cast<std::byte>(0x22), /*..........:#@'="*/
              /*80*/ static_cast<std::byte>(0xd8), static_cast<std::byte>(0x61), static_cast<std::byte>(0x62), static_cast<std::byte>(0x63), static_cast<std::byte>(0x64), static_cast<std::byte>(0x65), static_cast<std::byte>(0x66), static_cast<std::byte>(0x67),
              static_cast<std::byte>(0x68), static_cast<std::byte>(0x69), static_cast<std::byte>(0xab), static_cast<std::byte>(0xbb), static_cast<std::byte>(0xf0), static_cast<std::byte>(0xfd), static_cast<std::byte>(0xfe), static_cast<std::byte>(0xb1), /*.abcdefghi......*/
              /*90*/ static_cast<std::byte>(0xb0), static_cast<std::byte>(0x6a), static_cast<std::byte>(0x6b), static_cast<std::byte>(0x6c), static_cast<std::byte>(0x6d), static_cast<std::byte>(0x6e), static_cast<std::byte>(0x6f), static_cast<std::byte>(0x70),
              static_cast<std::byte>(0x71), static_cast<std::byte>(0x72), static_cast<std::byte>(0xaa), static_cast<std::byte>(0xba), static_cast<std::byte>(0xe6), static_cast<std::byte>(0xb8), static_cast<std::byte>(0xc6), static_cast<std::byte>(0xa4), /*.jklmnopqr......*/
              /*a0*/ static_cast<std::byte>(0xb5), static_cast<std::byte>(0xaf), static_cast<std::byte>(0x73), static_cast<std::byte>(0x74), static_cast<std::byte>(0x75), static_cast<std::byte>(0x76), static_cast<std::byte>(0x77), static_cast<std::byte>(0x78),
              static_cast<std::byte>(0x79), static_cast<std::byte>(0x7a), static_cast<std::byte>(0xa1), static_cast<std::byte>(0xbf), static_cast<std::byte>(0xd0), static_cast<std::byte>(0xdd), static_cast<std::byte>(0xde), static_cast<std::byte>(0xae), /*..stuvwxyz......*/
              /*b0*/ static_cast<std::byte>(0xa2), static_cast<std::byte>(0xa3), static_cast<std::byte>(0xa5), static_cast<std::byte>(0xb7), static_cast<std::byte>(0xa9), static_cast<std::byte>(0xa7), static_cast<std::byte>(0xb6), static_cast<std::byte>(0xbc),
              static_cast<std::byte>(0xbd), static_cast<std::byte>(0xbe), static_cast<std::byte>(0xac), static_cast<std::byte>(0x5b), static_cast<std::byte>(0x5c), static_cast<std::byte>(0x5d), static_cast<std::byte>(0xb4), static_cast<std::byte>(0xd7), /*...........[\]..*/
              /*c0*/ static_cast<std::byte>(0xf9), static_cast<std::byte>(0x41), static_cast<std::byte>(0x42), static_cast<std::byte>(0x43), static_cast<std::byte>(0x44), static_cast<std::byte>(0x45), static_cast<std::byte>(0x46), static_cast<std::byte>(0x47),
              static_cast<std::byte>(0x48), static_cast<std::byte>(0x49), static_cast<std::byte>(0xad), static_cast<std::byte>(0xf4), static_cast<std::byte>(0xf6), static_cast<std::byte>(0xf2), static_cast<std::byte>(0xf3), static_cast<std::byte>(0xf5), /*.ABCDEFGHI......*/
              /*d0*/ static_cast<std::byte>(0xa6), static_cast<std::byte>(0x4a), static_cast<std::byte>(0x4b), static_cast<std::byte>(0x4c), static_cast<std::byte>(0x4d), static_cast<std::byte>(0x4e), static_cast<std::byte>(0x4f), static_cast<std::byte>(0x50),
              static_cast<std::byte>(0x51), static_cast<std::byte>(0x52), static_cast<std::byte>(0xb9), static_cast<std::byte>(0xfb), static_cast<std::byte>(0xfc), static_cast<std::byte>(0xdb), static_cast<std::byte>(0xfa), static_cast<std::byte>(0xff), /*.JKLMNOPQR......*/
              /*e0*/ static_cast<std::byte>(0xd9), static_cast<std::byte>(0xf7), static_cast<std::byte>(0x53), static_cast<std::byte>(0x54), static_cast<std::byte>(0x55), static_cast<std::byte>(0x56), static_cast<std::byte>(0x57), static_cast<std::byte>(0x58),
              static_cast<std::byte>(0x59), static_cast<std::byte>(0x5a), static_cast<std::byte>(0xb2), static_cast<std::byte>(0xd4), static_cast<std::byte>(0xd6), static_cast<std::byte>(0xd2), static_cast<std::byte>(0xd3), static_cast<std::byte>(0xd5), /*..STUVWXYZ......*/
              /*f0*/ static_cast<std::byte>(0x30), static_cast<std::byte>(0x31), static_cast<std::byte>(0x32), static_cast<std::byte>(0x33), static_cast<std::byte>(0x34), static_cast<std::byte>(0x35), static_cast<std::byte>(0x36), static_cast<std::byte>(0x37),
              static_cast<std::byte>(0x38), static_cast<std::byte>(0x39), static_cast<std::byte>(0xb3), static_cast<std::byte>(0x7b), static_cast<std::byte>(0xdc), static_cast<std::byte>(0x7d), static_cast<std::byte>(0xda), static_cast<std::byte>(0x7e)  /*0123456789.{.}.~*/
       };
};

#endif //CODEMORPH_LIBRARY_H