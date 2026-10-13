#ifndef CODEMORPH_CODEMORPH_HPP
#define CODEMORPH_CODEMORPH_HPP

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace codemorph {

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
[[nodiscard]] auto hex_to_bytes(std::string_view value) -> std::vector<std::byte>;

/**
 * Converts a hexadecimal string to bytes and writes them into a destination buffer.
 * @param value The hexadecimal string to convert.
 * @param packed_bytes The destination span to store the resulting bytes.
 * @param index The current write offset in the destination span. It will be advanced.
 */
void hex_to_bytes(std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index);

/**
 * Converts a span of bytes to a hexadecimal string.
 * @param bytes The span of bytes to convert.
 * @return A string representing the bytes in hexadecimal format.
 */
[[nodiscard]] auto bytes_to_hex(std::span<const std::byte> bytes) -> std::string;

/**
 * Converts a section of a span of bytes to a hexadecimal string.
 * @param packed_bytes The source span of bytes to convert.
 * @param index The current read offset in the span. It will be advanced.
 * @param num_bytes The number of bytes to convert.
 * @return A string representing the bytes in hexadecimal format.
 */
[[nodiscard]] auto bytes_to_hex(std::span<const std::byte> packed_bytes, std::size_t& index, std::size_t num_bytes)
    -> std::string;

/**
 * Converts an integer to bytes (binary/hex digit packing) and stores them in a destination buffer.
 * @param value The integer to convert.
 * @param packed_bytes The destination span to store the resulting bytes.
 * @param index The current write offset in the destination span. It will be advanced.
 * @param byte_width The number of hexadecimal digits of `value` to encode.
 */
void int_to_bytes(int32_t value, std::span<std::byte> packed_bytes, std::size_t& index, std::size_t byte_width);

/**
 * Converts an integer to a vector of bytes.
 * @param value The integer to convert.
 * @param byte_width The number of hexadecimal digits of `value` to encode.
 * @return A vector of bytes representing the integer.
 */
[[nodiscard]] auto int_to_bytes(int32_t value, std::size_t byte_width) -> std::vector<std::byte>;

/**
 * Converts an integer to Binary-Coded Decimal (BCD) and stores it in a destination buffer.
 * @param value The integer to convert.
 * @param packed_bytes The destination span to store the resulting BCD.
 * @param index The current write offset in the destination span. It will be advanced.
 * @param digit_count The number of decimal digits to encode as BCD.
 */
void int_to_bcd(int32_t value, std::span<std::byte> packed_bytes, std::size_t& index, std::size_t digit_count);

/**
 * Converts an integer to a vector of Binary-Coded Decimal (BCD).
 * @param value The integer to convert.
 * @param digit_count The number of decimal digits to encode as BCD.
 * @return A vector of bytes representing the BCD.
 */
[[nodiscard]] auto int_to_bcd(int32_t value, std::size_t digit_count) -> std::vector<std::byte>;

/**
 * Converts a 64-bit unsigned integer to a vector of Binary-Coded Decimal (BCD).
 * Supports values up to 19 digits (max uint64_t).
 * @param value The 64-bit integer to convert.
 * @param digit_count The number of decimal digits to encode as BCD.
 * @return A vector of bytes representing the BCD.
 */
[[nodiscard]] auto int_to_bcd(uint64_t value, std::size_t digit_count) -> std::vector<std::byte>;

/**
 * Converts BCD bytes to a 64-bit unsigned integer.
 * @param packed_bytes The source span of BCD bytes to read.
 * @param digit_count The number of decimal digits encoded in BCD to read.
 * @return The decoded 64-bit unsigned integer value.
 */
[[nodiscard]] auto bcd_to_uint64(std::span<const std::byte> packed_bytes, std::size_t digit_count) -> uint64_t;

/**
 * Converts an ASCII string of decimal digits to Binary-Coded Decimal (BCD)
 * and writes it into a destination buffer.
 * @param value The ASCII string to convert.
 * @param packed_bytes The destination span to store the resulting BCD.
 * @param index The current write offset in the destination span. It will be advanced.
 * @param padding The padding to apply (LEFT, RIGHT, or NONE) when the length is odd.
 */
void ascii_to_bcd(std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index, FieldPadding padding);

/**
 * Converts an ASCII string of decimal digits to Binary-Coded Decimal (BCD).
 * @param value The ASCII string to convert.
 * @param padding The padding to apply (LEFT, RIGHT, or NONE) when the length is odd.
 * @return A vector of bytes representing the BCD.
 */
[[nodiscard]] auto ascii_to_bcd(std::string_view value, FieldPadding padding) -> std::vector<std::byte>;

/**
 * Converts an ASCII string to raw bytes and writes them into a destination buffer.
 * @param str_ascii_string The ASCII string to convert.
 * @param packed_bytes The destination span to store the resulting bytes.
 * @param index The current write offset in the destination span. It will be advanced.
 */
void ascii_to_bytes(std::string_view str_ascii_string, std::span<std::byte> packed_bytes, std::size_t& index);

/**
 * Converts an ASCII string to a vector of raw bytes.
 * @param str_ascii_string The ASCII string to convert.
 * @return A vector of bytes representing the ASCII string.
 */
[[nodiscard]] auto ascii_to_bytes(std::string_view str_ascii_string) -> std::vector<std::byte>;

/**
 * Converts an ASCII string to EBCDIC bytes and writes them into a destination buffer.
 * @param value The ASCII string to convert.
 * @param packed_bytes The destination span to store the resulting EBCDIC bytes.
 * @param index The current write offset in the destination span. It will be advanced.
 */
void ascii_to_ebcdic(std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index);

/**
 * Converts an ASCII string to a vector of EBCDIC bytes.
 * @param value The ASCII string to convert.
 * @return A vector of bytes representing the EBCDIC encoding.
 */
[[nodiscard]] auto ascii_to_ebcdic(std::string_view value) -> std::vector<std::byte>;

/**
 * VISA variant: converts ASCII to EBCDIC using the mapping where '^' encodes to 0x5F
 * (Track 1 field separator). Use this when generating VISA-specific EBCDIC payloads.
 */
void ascii_to_ebcdic_visa(std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index);

/**
 * VISA variant: converts ASCII to a vector of EBCDIC bytes ( '^' -> 0x5F ).
 */
[[nodiscard]] auto ascii_to_ebcdic_visa(std::string_view value) -> std::vector<std::byte>;

/**
 * Converts bytes to an integer starting from a specific offset.
 * @param packed_bytes The source span of bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param byte_width The number of hexadecimal digits to read/interpret.
 * @return The integer represented by the bytes.
 */
[[nodiscard]] auto bytes_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, std::size_t byte_width)
    -> int32_t;

/**
 * Converts bytes to an integer.
 * @param packed_bytes The source span of bytes to read.
 * @param byte_width The number of hexadecimal digits to read/interpret.
 * @return The integer represented by the bytes.
 */
[[nodiscard]] auto bytes_to_int(std::span<const std::byte> packed_bytes, std::size_t byte_width) -> int32_t;

/**
 * Converts BCD bytes to an integer starting from a specific offset.
 * @param packed_bytes The source span of BCD bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param digit_count The number of decimal digits encoded in BCD to read.
 * @return The decoded integer value.
 */
[[nodiscard]] auto bcd_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, std::size_t digit_count)
    -> int32_t;

/**
 * Converts BCD bytes to an integer.
 * @param packed_bytes The source span of BCD bytes to read.
 * @param digit_count The number of decimal digits encoded in BCD to read.
 * @return The decoded integer value.
 */
[[nodiscard]] auto bcd_to_int(std::span<const std::byte> packed_bytes, std::size_t digit_count) -> int32_t;

/**
 * Converts BCD bytes to an ASCII string starting from a specific offset.
 * @param packed_bytes The source span of BCD bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param padding The padding that was originally applied (LEFT, RIGHT, or NONE).
 * @param digit_count The number of ASCII characters expected in the output.
 * @return The ASCII string represented by the BCD.
 */
[[nodiscard]] auto bcd_to_ascii(std::span<const std::byte> packed_bytes, std::size_t& index, FieldPadding padding,
                                std::size_t digit_count) -> std::string;

/**
 * Converts BCD bytes to an ASCII string.
 * @param packed_bytes The source span of BCD bytes to read.
 * @param padding The padding that was originally applied (LEFT, RIGHT, or NONE).
 * @param digit_count The number of ASCII characters expected in the output.
 * @return The ASCII string represented by the BCD.
 */
[[nodiscard]] auto bcd_to_ascii(std::span<const std::byte> packed_bytes, FieldPadding padding, std::size_t digit_count)
    -> std::string;

/**
 * Converts raw bytes to an ASCII string starting from a specific offset.
 * @param packed_bytes The source span of bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param byte_count The number of bytes to read.
 * @return The ASCII string represented by those bytes.
 */
[[nodiscard]] auto bytes_to_ascii(std::span<const std::byte> packed_bytes, std::size_t& index, std::size_t byte_count)
    -> std::string;

/**
 * Converts raw bytes to an ASCII string.
 * @param packed_bytes The source span of bytes to read.
 * @param byte_count The number of bytes to read.
 * @return The ASCII string represented by those bytes.
 */
[[nodiscard]] auto bytes_to_ascii(std::span<const std::byte> packed_bytes, std::size_t byte_count) -> std::string;

/**
 * Converts EBCDIC bytes to an ASCII string starting from a specific offset.
 * @param packed_bytes The source span of EBCDIC bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param byte_count The number of bytes to read.
 * @return The ASCII string represented by those EBCDIC bytes.
 */
[[nodiscard]] auto ebcdic_to_ascii(std::span<const std::byte> packed_bytes, std::size_t& index, std::size_t byte_count)
    -> std::string;

/**
 * Converts EBCDIC bytes to an ASCII string.
 * @param packed_bytes The source span of EBCDIC bytes to read.
 * @param byte_count The number of bytes to read.
 * @return The ASCII string represented by those EBCDIC bytes.
 */
[[nodiscard]] auto ebcdic_to_ascii(std::span<const std::byte> packed_bytes, std::size_t byte_count) -> std::string;

// ========================================================================
// EBCDIC VISA Variant (for payment systems)
// ========================================================================
// VISA uses a slightly different EBCDIC mapping where 0x5F = '^' (caret)
// instead of the standard IBM-037 mapping where 0x5F = control character.
// This is important for Track 1 data where '^' is the field separator.

/**
 * Converts EBCDIC bytes to ASCII using VISA's EBCDIC variant.
 * Key difference: 0x5F maps to '^' (caret, 0x5E) for Track 1 separators.
 * @param packed_bytes The source span of EBCDIC bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param byte_count The number of bytes to read.
 * @return The ASCII string represented by those EBCDIC bytes.
 */
[[nodiscard]] auto ebcdic_to_ascii_visa(std::span<const std::byte> packed_bytes, std::size_t& index,
                                        std::size_t byte_count) -> std::string;

/**
 * Converts EBCDIC bytes to ASCII using VISA's EBCDIC variant.
 * Key difference: 0x5F maps to '^' (caret, 0x5E) for Track 1 separators.
 * @param packed_bytes The source span of EBCDIC bytes to read.
 * @param byte_count The number of bytes to read.
 * @return The ASCII string represented by those EBCDIC bytes.
 */
[[nodiscard]] auto ebcdic_to_ascii_visa(std::span<const std::byte> packed_bytes, std::size_t byte_count) -> std::string;

// ========================================================================
// EBCDIC Numeric Conversions (for Mastercard SMS and similar protocols)
// ========================================================================

/**
 * Converts an integer to EBCDIC numeric representation.
 * Each decimal digit becomes one EBCDIC byte (F0-F9).
 * Example: 123 with digit_count=3 -> F1 F2 F3
 * @param value The integer to convert.
 * @param packed_bytes The destination span to store the resulting EBCDIC bytes.
 * @param index The current write offset in the destination span. It will be advanced.
 * @param digit_count The number of decimal digits to encode (zero-padded on left).
 */
void int_to_ebcdic(int64_t value, std::span<std::byte> packed_bytes, std::size_t& index, std::size_t digit_count);

/**
 * Converts an integer to EBCDIC numeric representation.
 * @param value The integer to convert.
 * @param digit_count The number of decimal digits to encode (zero-padded on left).
 * @return A vector of EBCDIC bytes representing the integer.
 */
[[nodiscard]] auto int_to_ebcdic(int64_t value, std::size_t digit_count) -> std::vector<std::byte>;

/**
 * Converts EBCDIC numeric bytes to an integer.
 * Each EBCDIC byte (F0-F9) represents one decimal digit.
 * Example: F1 F2 F3 -> 123
 * @param packed_bytes The source span of EBCDIC bytes to read.
 * @param index The current read offset in the span. It will be advanced.
 * @param digit_count The number of EBCDIC digits to read.
 * @return The decoded integer value.
 */
[[nodiscard]] auto ebcdic_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, std::size_t digit_count)
    -> int64_t;

/**
 * Converts EBCDIC numeric bytes to an integer.
 * @param packed_bytes The source span of EBCDIC bytes to read.
 * @param digit_count The number of EBCDIC digits to read.
 * @return The decoded integer value.
 */
[[nodiscard]] auto ebcdic_to_int(std::span<const std::byte> packed_bytes, std::size_t digit_count) -> int64_t;

} // namespace codemorph

#endif // CODEMORPH_CODEMORPH_HPP
