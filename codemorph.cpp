#include "codemorph.hpp"

#include <cstdint>
#include <stdexcept>

auto CodeMorph::hex_to_bytes(const std::string_view value) -> std::vector<std::byte> {
    const std::size_t bin_length = value.length() / 2;
    std::vector<std::byte> packed_bytes(bin_length);

    for (std::size_t i = 0, j = 0; i < bin_length; i++, j++) {
        packed_bytes[j] = static_cast<std::byte>(
            std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
            std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])])
        );
    }

    return packed_bytes;
}

void CodeMorph::hex_to_bytes(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index) {
    const std::size_t bin_length = value.length() / 2;

    for (std::size_t i = 0, j = index; i < bin_length; i++, j++) {
        packed_bytes[j] = static_cast<std::byte>(
            std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
            std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])])
        );
    }

    index += bin_length;
}

auto CodeMorph::bytes_to_hex(const std::span<const std::byte> bytes) -> std::string {
    static constexpr std::array HEX_DIGITS{
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

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

auto CodeMorph::bytes_to_hex(const std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t num_bytes) -> std::string {
    static constexpr std::array HEX_DIGITS = {
        '0','1','2','3','4','5','6','7',
        '8','9','A','B','C','D','E','F'
    };

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

void CodeMorph::int_to_bytes(const int32_t value, std::span<std::byte> packed_bytes, std::size_t& index,
                             const std::size_t byte_width) {
    for (std::size_t i = 0; i < byte_width; i++) {
        packed_bytes[index + i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
    }
    index += byte_width;
}

auto CodeMorph::int_to_bytes(const int32_t value, const std::size_t byte_width) -> std::vector<std::byte> {
    std::vector<std::byte> result(byte_width);

    for (std::size_t i = 0; i < byte_width; i++) {
        result[i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
    }

    return result;
}

void CodeMorph::int_to_bcd(int32_t value,
                           std::span<std::byte> packed_bytes,
                           std::size_t& index,
                           const std::size_t digit_count) {
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

auto CodeMorph::int_to_bcd(int32_t value, const std::size_t digit_count) -> std::vector<std::byte> {
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

auto CodeMorph::int_to_bcd(uint64_t value, const std::size_t digit_count) -> std::vector<std::byte> {
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

auto CodeMorph::bcd_to_uint64(std::span<const std::byte> packed_bytes, const std::size_t digit_count) -> uint64_t {
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

void CodeMorph::ascii_to_bcd(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index,
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
        packed_bytes[index++] = static_cast<std::byte>(
            (value[i] - 0x30) * 0x10 + value[i + 1] - 0x30
        );
    }

    if (need_padding && padding == FieldPadding::RIGHT) {
        packed_bytes[index++] = static_cast<std::byte>(
            (value[value_length] - 0x30) * 0x10
        );
    }
}

auto CodeMorph::ascii_to_bcd(const std::string_view value,
                             const FieldPadding padding) -> std::vector<std::byte> {
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
        const auto d1 = static_cast<unsigned>(value[src_i]   - '0');
        const auto d2 = static_cast<unsigned>(value[src_i+1] - '0');
        result[dst_i++] = static_cast<std::byte>((d1 << 4) | d2);
        src_i += 2;
    }

    if (odd && padding == FieldPadding::RIGHT) {
        const auto d = static_cast<unsigned>(value[src_i] - '0');
        result[dst_i++] = static_cast<std::byte>(d << 4);
    }

    return result;
}

void CodeMorph::ascii_to_bytes(std::string_view str_ascii_string, std::span<std::byte> packed_bytes, std::size_t& index)
{
    const auto len = str_ascii_string.length();

    for (std::size_t i = 0; i < len; i++)
        packed_bytes[index + i] = static_cast<std::byte>(str_ascii_string[i]);

    index += len;
}

auto CodeMorph::ascii_to_bytes(std::string_view str_ascii_string) -> std::vector<std::byte> {
    const std::size_t len = str_ascii_string.length();
    std::vector<std::byte> result(len);

    for (std::size_t i = 0; i < len; ++i) {
        result[i] = static_cast<std::byte>(str_ascii_string[i]);
    }

    return result;
}

void CodeMorph::ascii_to_ebcdic(const std::string_view value, std::span<std::byte> packed_bytes, std::size_t& index)
{
    const auto src_length = value.length();

    for (std::size_t i = 0; i < src_length; i++)
    {
        packed_bytes[index + i] = ascii_to_ebcdic_table[static_cast<unsigned char>(value[i])];
    }

    index += src_length;
}

auto CodeMorph::ascii_to_ebcdic(const std::string_view value) -> std::vector<std::byte> {
    const auto src_length = value.length();
    std::vector<std::byte> result(src_length);

    for (std::size_t i = 0; i < src_length; i++)
    {
        result[i] = ascii_to_ebcdic_table[static_cast<unsigned char>(value[i])];
    }

    return result;
}

auto CodeMorph::bytes_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t byte_width) -> int32_t {
    int32_t result = 0;
    std::size_t pos = (byte_width / 2 - 1) * 8;

    for (std::size_t i = 0; i < byte_width / 2; i++)
    {
        result |= static_cast<int32_t>(packed_bytes[index + i]) << pos;
        pos -= 8;
    }

    index += byte_width / 2;
    return result;
}

auto CodeMorph::bytes_to_int(std::span<const std::byte> packed_bytes, const std::size_t byte_width) -> int32_t {
    int32_t result = 0;
    std::size_t pos = (byte_width / 2 - 1) * 8;

    for (std::size_t i = 0; i < byte_width / 2; i++)
    {
        result |= static_cast<int32_t>(packed_bytes[i]) << pos;
        pos -= 8;
    }

    return result;
}

auto CodeMorph::bcd_to_int(std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t digit_count) -> int32_t {
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

auto CodeMorph::bcd_to_int(std::span<const std::byte> packed_bytes, const std::size_t digit_count) -> int32_t {
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

auto CodeMorph::bcd_to_ascii(const std::span<const std::byte> packed_bytes, std::size_t& index, const FieldPadding padding,
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

auto CodeMorph::bcd_to_ascii(const std::span<const std::byte> packed_bytes, const FieldPadding padding,
                             const std::size_t digit_count) -> std::string {
    std::size_t index = 0;
    return bcd_to_ascii(packed_bytes, index, padding, digit_count);
}

auto CodeMorph::bytes_to_ascii(std::span<const std::byte> packed_bytes, std::size_t& index, const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++)
        result[i] = static_cast<char>(packed_bytes[index + i]);

    index += byte_count;
    return result;
}

auto CodeMorph::bytes_to_ascii(std::span<const std::byte> packed_bytes, const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++)
        result[i] = static_cast<char>(packed_bytes[i]);

    return result;
}

auto CodeMorph::ebcdic_to_ascii(const std::span<const std::byte> packed_bytes, std::size_t& index,
                                const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++) {
        const auto ebcdic_byte = std::to_integer<unsigned>(packed_bytes[index + i]);
        result[i] = static_cast<char>(ebcdic_to_ascii_table[ebcdic_byte]);
    }

    index += byte_count;
    return result;
}

auto CodeMorph::ebcdic_to_ascii(const std::span<const std::byte> packed_bytes,
                                const std::size_t byte_count) -> std::string {
    std::string result(byte_count, '0');

    for (std::size_t i = 0; i < byte_count; i++) {
        const auto ebcdic_byte = std::to_integer<unsigned>(packed_bytes[i]);
        result[i] = static_cast<char>(ebcdic_to_ascii_table[ebcdic_byte]);
    }

    return result;
}
