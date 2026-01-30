#ifndef CODEMORPH_LIBRARY_H
#define CODEMORPH_LIBRARY_H

#include <array>
#include <cstdint>
#include <string>
#include <span>
#include <vector>

/**
 * The CodeMorph class provides utility methods for converting between
 * various data formats such as hexadecimal, bytes, ASCII, BCD, and EBCDIC.
 * It includes methods for encoding, decoding, and transforming data
 * with support for padding and indexing.
 */
class CodeMorph {
public:
    /**
     * Represents the type of padding to apply to fields.
     * LEFT: Pads on the left side.
     * RIGHT: Pads on the right side.
     * NONE: No padding is applied.
     */
    enum class FieldPadding { LEFT, RIGHT, NONE };

    /**
     * Converts a hexadecimal string to a vector of bytes.
     * @param value The hexadecimal string to convert.
     * @return A vector of bytes representing the hexadecimal string.
     */
    [[nodiscard]] static auto hex_to_bytes(std::string_view value) -> std::vector<std::byte>;

    /**
     * Converts a hexadecimal string to bytes and writes them into a destination buffer.
     * @param value The hexadecimal string to convert.
     * @param packed_bytes The destination span to store the resulting bytes.
     * @param index The current write offset in the destination span. It will be advanced.
     */
    static void hex_to_bytes(std::string_view value,
                             std::span<std::byte> packed_bytes,
                             std::size_t& index);

    /**
     * Converts a span of bytes to a hexadecimal string.
     * @param bytes The span of bytes to convert.
     * @return A string representing the bytes in hexadecimal format.
     */
    [[nodiscard]] static auto bytes_to_hex(std::span<const std::byte> bytes) -> std::string;

    /**
     * Converts a section of a span of bytes to a hexadecimal string.
     * @param packed_bytes The source span of bytes to convert.
     * @param index The current read offset in the span. It will be advanced.
     * @param num_bytes The number of bytes to convert.
     * @return A string representing the bytes in hexadecimal format.
     */
    [[nodiscard]] static auto bytes_to_hex(std::span<const std::byte> packed_bytes,
                             std::size_t& index,
                             std::size_t num_bytes) -> std::string;

    /**
     * Converts an integer to bytes (binary/hex digit packing) and stores them in a destination buffer.
     * @param value The integer to convert.
     * @param packed_bytes The destination span to store the resulting bytes.
     * @param index The current write offset in the destination span. It will be advanced.
     * @param byte_width The number of hexadecimal digits of `value` to encode.
     */
    static void int_to_bytes(int32_t value,
                             std::span<std::byte> packed_bytes,
                             std::size_t& index,
                             std::size_t byte_width);

    /**
     * Converts an integer to a vector of bytes.
     * @param value The integer to convert.
     * @param byte_width The number of hexadecimal digits of `value` to encode.
     * @return A vector of bytes representing the integer.
     */
    [[nodiscard]] static auto int_to_bytes(int32_t value,
                             std::size_t byte_width) -> std::vector<std::byte>;

    /**
     * Converts an integer to Binary-Coded Decimal (BCD) and stores it in a destination buffer.
     * @param value The integer to convert.
     * @param packed_bytes The destination span to store the resulting BCD.
     * @param index The current write offset in the destination span. It will be advanced.
     * @param digit_count The number of decimal digits to encode as BCD.
     */
    static void int_to_bcd(int32_t value,
                           std::span<std::byte> packed_bytes,
                           std::size_t& index,
                           std::size_t digit_count);

    /**
     * Converts an integer to a vector of Binary-Coded Decimal (BCD).
     * @param value The integer to convert.
     * @param digit_count The number of decimal digits to encode as BCD.
     * @return A vector of bytes representing the BCD.
     */
    [[nodiscard]] static auto int_to_bcd(int32_t value,
                           std::size_t digit_count) -> std::vector<std::byte>;

    /**
     * Converts a 64-bit unsigned integer to a vector of Binary-Coded Decimal (BCD).
     * Supports values up to 19 digits (max uint64_t).
     * @param value The 64-bit integer to convert.
     * @param digit_count The number of decimal digits to encode as BCD.
     * @return A vector of bytes representing the BCD.
     */
    [[nodiscard]] static auto int_to_bcd(uint64_t value,
                           std::size_t digit_count) -> std::vector<std::byte>;

    /**
     * Converts BCD bytes to a 64-bit unsigned integer.
     * @param packed_bytes The source span of BCD bytes to read.
     * @param digit_count The number of decimal digits encoded in BCD to read.
     * @return The decoded 64-bit unsigned integer value.
     */
    [[nodiscard]] static auto bcd_to_uint64(std::span<const std::byte> packed_bytes,
                           std::size_t digit_count) -> uint64_t;

    /**
     * Converts an ASCII string of decimal digits to Binary-Coded Decimal (BCD)
     * and writes it into a destination buffer.
     * @param value The ASCII string to convert.
     * @param packed_bytes The destination span to store the resulting BCD.
     * @param index The current write offset in the destination span. It will be advanced.
     * @param padding The padding to apply (LEFT, RIGHT, or NONE) when the length is odd.
     */
    static void ascii_to_bcd(std::string_view value,
                             std::span<std::byte> packed_bytes,
                             std::size_t& index,
                             FieldPadding padding);

    /**
     * Converts an ASCII string of decimal digits to Binary-Coded Decimal (BCD).
     * @param value The ASCII string to convert.
     * @param padding The padding to apply (LEFT, RIGHT, or NONE) when the length is odd.
     * @return A vector of bytes representing the BCD.
     */
    [[nodiscard]] static auto ascii_to_bcd(std::string_view value,
                             FieldPadding padding) -> std::vector<std::byte>;

    /**
     * Converts an ASCII string to raw bytes and writes them into a destination buffer.
     * @param str_ascii_string The ASCII string to convert.
     * @param packed_bytes The destination span to store the resulting bytes.
     * @param index The current write offset in the destination span. It will be advanced.
     */
    static void ascii_to_bytes(std::string_view str_ascii_string,
                               std::span<std::byte> packed_bytes,
                               std::size_t& index);

    /**
     * Converts an ASCII string to a vector of raw bytes.
     * @param str_ascii_string The ASCII string to convert.
     * @return A vector of bytes representing the ASCII string.
     */
    [[nodiscard]] static auto ascii_to_bytes(std::string_view str_ascii_string) -> std::vector<std::byte>;

    /**
     * Converts an ASCII string to EBCDIC bytes and writes them into a destination buffer.
     * @param value The ASCII string to convert.
     * @param packed_bytes The destination span to store the resulting EBCDIC bytes.
     * @param index The current write offset in the destination span. It will be advanced.
     */
    static void ascii_to_ebcdic(std::string_view value,
                                std::span<std::byte> packed_bytes,
                                std::size_t& index);

    /**
     * Converts an ASCII string to a vector of EBCDIC bytes.
     * @param value The ASCII string to convert.
     * @return A vector of bytes representing the EBCDIC encoding.
     */
    [[nodiscard]] static auto ascii_to_ebcdic(std::string_view value) -> std::vector<std::byte>;

    /**
     * Converts bytes to an integer starting from a specific offset.
     * @param packed_bytes The source span of bytes to read.
     * @param index The current read offset in the span. It will be advanced.
     * @param byte_width The number of hexadecimal digits to read/interpret.
     * @return The integer represented by the bytes.
     */
    [[nodiscard]] static auto bytes_to_int(std::span<const std::byte> packed_bytes,
                             std::size_t& index,
                             std::size_t byte_width) -> int32_t;

    /**
     * Converts bytes to an integer.
     * @param packed_bytes The source span of bytes to read.
     * @param byte_width The number of hexadecimal digits to read/interpret.
     * @return The integer represented by the bytes.
     */
    [[nodiscard]] static auto bytes_to_int(std::span<const std::byte> packed_bytes,
                             std::size_t byte_width) -> int32_t;

    /**
     * Converts BCD bytes to an integer starting from a specific offset.
     * @param packed_bytes The source span of BCD bytes to read.
     * @param index The current read offset in the span. It will be advanced.
     * @param digit_count The number of decimal digits encoded in BCD to read.
     * @return The decoded integer value.
     */
    [[nodiscard]] static auto bcd_to_int(std::span<const std::byte> packed_bytes,
                           std::size_t& index,
                           std::size_t digit_count) -> int32_t;

    /**
     * Converts BCD bytes to an integer.
     * @param packed_bytes The source span of BCD bytes to read.
     * @param digit_count The number of decimal digits encoded in BCD to read.
     * @return The decoded integer value.
     */
    [[nodiscard]] static auto bcd_to_int(std::span<const std::byte> packed_bytes,
                           std::size_t digit_count) -> int32_t;

    /**
     * Converts BCD bytes to an ASCII string starting from a specific offset.
     * @param packed_bytes The source span of BCD bytes to read.
     * @param index The current read offset in the span. It will be advanced.
     * @param padding The padding that was originally applied (LEFT, RIGHT, or NONE).
     * @param digit_count The number of ASCII characters expected in the output.
     * @return The ASCII string represented by the BCD.
     */
    [[nodiscard]] static auto bcd_to_ascii(std::span<const std::byte> packed_bytes,
                             std::size_t& index,
                             FieldPadding padding,
                             std::size_t digit_count) -> std::string;

    /**
     * Converts BCD bytes to an ASCII string.
     * @param packed_bytes The source span of BCD bytes to read.
     * @param padding The padding that was originally applied (LEFT, RIGHT, or NONE).
     * @param digit_count The number of ASCII characters expected in the output.
     * @return The ASCII string represented by the BCD.
     */
    [[nodiscard]] static auto bcd_to_ascii(std::span<const std::byte> packed_bytes,
                             FieldPadding padding,
                             std::size_t digit_count) -> std::string;

    /**
     * Converts raw bytes to an ASCII string starting from a specific offset.
     * @param packed_bytes The source span of bytes to read.
     * @param index The current read offset in the span. It will be advanced.
     * @param byte_count The number of bytes to read.
     * @return The ASCII string represented by those bytes.
     */
    [[nodiscard]] static auto bytes_to_ascii(std::span<const std::byte> packed_bytes,
                               std::size_t& index,
                               std::size_t byte_count) -> std::string;

    /**
     * Converts raw bytes to an ASCII string.
     * @param packed_bytes The source span of bytes to read.
     * @param byte_count The number of bytes to read.
     * @return The ASCII string represented by those bytes.
     */
    [[nodiscard]] static auto bytes_to_ascii(std::span<const std::byte> packed_bytes,
                               std::size_t byte_count) -> std::string;

    /**
     * Converts EBCDIC bytes to an ASCII string starting from a specific offset.
     * @param packed_bytes The source span of EBCDIC bytes to read.
     * @param index The current read offset in the span. It will be advanced.
     * @param byte_count The number of bytes to read.
     * @return The ASCII string represented by those EBCDIC bytes.
     */
    [[nodiscard]] static auto ebcdic_to_ascii(std::span<const std::byte> packed_bytes,
                                std::size_t& index,
                                std::size_t byte_count) -> std::string;

    /**
     * Converts EBCDIC bytes to an ASCII string.
     * @param packed_bytes The source span of EBCDIC bytes to read.
     * @param byte_count The number of bytes to read.
     * @return The ASCII string represented by those EBCDIC bytes.
     */
    [[nodiscard]] static auto ebcdic_to_ascii(std::span<const std::byte> packed_bytes,
                                std::size_t byte_count) -> std::string;

private:
    static constexpr std::array<std::byte, 256> hex_lookup = {
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

    static constexpr std::array<std::byte, 256> ascii_to_ebcdic_table = {
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

    static constexpr std::array<std::byte, 256> ebcdic_to_ascii_table = {
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
};

#endif //CODEMORPH_LIBRARY_H
