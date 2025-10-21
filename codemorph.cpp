#include "codemorph.hpp"

#include <cstdint>
#include <stdexcept>

auto CodeMorph::hex_to_bytes(const std::string& value) -> std::vector<std::byte> {
	const size_t bin_length = value.length() / 2;
	std::vector<std::byte> packed_bytes(bin_length);
	constexpr size_t index = 0;

	for (size_t i = 0, j = index; i < bin_length; i++, j++) {
		packed_bytes[j] = static_cast<std::byte>(
			std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
			std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])])
		);
	}

	return packed_bytes;
}

void CodeMorph::hex_to_bytes(const std::string& value, std::vector<std::byte>& packed_bytes, size_t& index) {
	const size_t binLength = value.length() / 2;
	packed_bytes.resize(index + binLength);

	for (size_t i = 0, j = index; i < binLength; i++, j++) {
		packed_bytes[j] = static_cast<std::byte>(
			std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
			 std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])])
		);
	}

	index += binLength;
}

auto CodeMorph::bytes_to_hex(const std::span<const std::byte> bytes) -> std::string {
	static constexpr std::array kHexDigits{
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	const std::size_t n = bytes.size();
	std::string out(n * 2, '\0');  // preallocate full size
	char* dst = out.data();

	for (std::size_t i = 0; i < n; ++i) {
		const auto v = std::to_integer<unsigned>(bytes[i]);
		dst[2 * i]     = kHexDigits[(v >> 4) & 0x0F];
		dst[2 * i + 1] = kHexDigits[v & 0x0F];
	}

	return out;
}

auto CodeMorph::bytes_to_hex(const std::span<const std::byte> packed_bytes, int& index, const int num_bytes) -> std::string {
	std::string basic_string;
	basic_string.reserve(num_bytes * 2);

	for (int i = 0; i < num_bytes; ++i) {
		basic_string.append(hex_string_lookup[std::to_integer<uint8_t>(packed_bytes[index + i])]);
	}

	index += num_bytes;
	return basic_string;
}

void CodeMorph::int_to_bytes(const int value, std::span<std::byte> &packed_bytes, int &index,
                             const int num_hex_digits) {
	for (int i = 0; i < num_hex_digits; i++) {
		packed_bytes[index + i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
	}
	index += num_hex_digits;
}

auto CodeMorph::int_to_bytes(const int value, const int num_hex_digits) -> std::vector<std::byte> {
	std::vector<std::byte> result;

	result.resize(num_hex_digits);
	for (int i = 0; i < num_hex_digits; i++) {
		result[i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
	}

	return result;
}

auto CodeMorph::int_to_bcd(int value, int num_digits) -> std::vector<std::byte> {
	num_digits /= 2;
	std::vector<std::byte> result(num_digits);

	for (int i = num_digits - 1; i >= 0; --i) {
		const int digit = value % 100;
		value /= 100;
		const int bcd = (digit / 10) << 4 | digit % 10;
		result[i] = static_cast<std::byte>(bcd & 0xFF);
	}

	return result;
}

void CodeMorph::ascii_to_bcd(const std::string &value, std::span<std::byte> &packed_bytes, int &index,
                             const FieldPadding padding) {
	auto value_length = value.length();
	int start_index = 0;
	const bool need_padding = value_length % 2 != 0;

	if (need_padding && padding == FieldPadding::LEFT) {
		packed_bytes[index++] = static_cast<std::byte>(value[0] - 0x30);
		start_index++;
	} else if (need_padding && padding == FieldPadding::RIGHT) {
		value_length--;
	}

	for (unsigned int i = start_index; i < value_length; i += 2) {
		packed_bytes[index++] = static_cast<std::byte>((value[i] - 0x30) * 0x10 + value[i + 1] - 0x30);
	}

	if (need_padding && padding == FieldPadding::RIGHT) {
		packed_bytes[index++] = static_cast<std::byte>((value[value_length] - 0x30) * 0x10);
	}
}

auto CodeMorph::ascii_to_bcd(const std::string &value, const FieldPadding padding) -> std::vector<std::byte> {
	const size_t value_length = value.length();
	const bool need_padding = value_length % 2 != 0;

	const size_t bcd_length = (value_length + 1) / 2;
	std::vector<std::byte> result;
	result.reserve(bcd_length);

	size_t start_index = 0;

	if (need_padding && padding == FieldPadding::LEFT) {
		result.emplace_back(static_cast<std::byte>(value[0] - '0'));
		start_index = 1;
	}

	for (size_t i = start_index; i + 1 < value_length; i += 2) {
		const auto byte = static_cast<std::byte>(
			(value[i] - '0') << 4 | value[i + 1] - '0'
		);
		result.emplace_back(byte);
	}

	if (need_padding && padding == FieldPadding::RIGHT) {
		const auto byte = static_cast<std::byte>((value[value_length - 1] - '0') << 4);
		result.emplace_back(byte);
	}

	return result;
}

void CodeMorph::ascii_to_bytes(const std::string &str_ascii_string, std::span<std::byte> &packed_bytes, size_t &index)
{
	const auto len = str_ascii_string.length();

	for (unsigned int i = 0; i < len; i++)
		packed_bytes[index + i] = static_cast<std::byte>(str_ascii_string[i]);

	index += len;
}

auto CodeMorph::ascii_to_bytes(const std::string &str_ascii_string) -> std::vector<std::byte> {
	const size_t len = str_ascii_string.length();
	std::vector<std::byte> result;
	result.reserve(len);

	for (char c: str_ascii_string) {
		result.emplace_back(static_cast<std::byte>(c));
	}

	return result;
}

void CodeMorph::ascii_to_ebcdic(const std::string& value, std::span<std::byte> packed_bytes, size_t& index)
{
	const auto src_length = value.length();

	for (unsigned int i = 0; i < src_length; i++)
	{
		packed_bytes[index + i] = ascii_to_ebcdic_table[static_cast<unsigned char>(value[i])];
	}

	index += src_length;
}

auto CodeMorph::ascii_to_ebcdic(const std::string& value) -> std::vector<std::byte> {
	const auto src_length = value.length();
	std::vector<std::byte> result;
	result.reserve(src_length);

	for (unsigned int i = 0; i < src_length; i++)
	{
		result[i] = ascii_to_ebcdic_table[static_cast<unsigned char>(value[i])];
	}

	return result;
}

auto CodeMorph::bytes_to_int(std::span<const std::byte> packed_bytes, int &index, const int num_hex_digits) -> int {
	int result = 0;
	int pos = (num_hex_digits / 2 - 1) * 8;

	for (int i = 0; i < num_hex_digits / 2; i++)
	{
		result |= static_cast<int>(packed_bytes[index + i]) << pos;
		pos -= 8;
	}

	index += num_hex_digits / 2;

	return result;
}

auto CodeMorph::bytes_to_int(std::span<const std::byte> packed_bytes, const int num_hex_digits) -> int {
	int result = 0;
	int pos = (num_hex_digits / 2 - 1) * 8;

	for (int i = 0; i < num_hex_digits / 2; i++)
	{
		result |= static_cast<int>(packed_bytes[i]) << pos;
		pos -= 8;
	}

	return result;
}

auto CodeMorph::bcd_to_int(std::span<const std::byte> packed_bytes, int& index, const int num_hex_digits) -> int {
	int result = 0;
	const int len = num_hex_digits / 2;

	for (int i = 0; i < len; ++i) {
		const auto byte = static_cast<int>(packed_bytes[index + i]);
		const int high = byte >> 4 & 0xF;
		const int low = byte & 0xF;
		result = result * 100 + high * 10 + low;
	}

	index += len;
	return result;
}

auto CodeMorph::bcd_to_int(std::span<const std::byte> packed_bytes, const int num_hex_digits) -> int {
	int result = 0;

	const int len = num_hex_digits / 2;

	for (int i = 0; i < len; ++i) {
		const auto byte = static_cast<int>(packed_bytes[i]);
		const int high = byte >> 4 & 0xF;
		const int low = byte & 0xF;
		result = result * 100 + high * 10 + low;
	}

	return result;
}

auto CodeMorph::bcd_to_ascii(std::span<const std::byte> packed_bytes, int &index, const FieldPadding padding,
							 const int value_length) -> std::string {
	std::string value(value_length, '0');
	if (value_length % 2 != 0) {
		if (padding == FieldPadding::LEFT) {
			value[0] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
			index++;
			for (int i = 1; i < value_length; i += 2) {
				value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
				value[i + 1] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
				index++;
			}
		} else {
			int i;
			for (i = 0; i < value_length - 1; i += 2) {
				value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
				value[i + 1] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
				index++;
			}
			value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
			index++;
		}
	} else {
		for (int i = 0; i < value_length; i += 2) {
			value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
			value[i + 1] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
			index++;
		}
	}
	return value;
}

auto CodeMorph::bcd_to_ascii(std::span<const std::byte> packed_bytes, const FieldPadding padding,
							 const int value_length) -> std::string {
	int index = 0;
	std::string value(value_length, '0');
	if (value_length % 2 != 0) {
		if (padding == FieldPadding::LEFT) {
			value[0] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
			index++;
			for (int i = 1; i < value_length; i += 2) {
				value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
				value[i + 1] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
				index++;
			}
		} else {
			int i;
			for (i = 0; i < value_length - 1; i += 2) {
				value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
				value[i + 1] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
				index++;
			}
			value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
		}
	} else {
		for (int i = 0; i < value_length; i += 2) {
			value[i] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) >> 4) + 0x30);
			value[i + 1] = static_cast<char>((static_cast<unsigned int>(packed_bytes[index]) & 0x0F) + 0x30);
			index++;
		}
	}
	return value;
}

auto CodeMorph::bytes_to_ascii(std::span<const std::byte> packed_bytes, int &index, const int num_bytes) -> std::string {
	std::string result(num_bytes, '0');

	for (int i = 0; i < num_bytes; i++)
		result[i] = static_cast<char>(packed_bytes[index + i]);

	index += num_bytes;

	return result;
}

auto CodeMorph::bytes_to_ascii(std::span<const std::byte> packed_bytes, const int num_bytes) -> std::string {
	std::string result(num_bytes, '0');

	for (int i = 0; i < num_bytes; i++)
		result[i] = static_cast<char>(packed_bytes[i]);

	return result;
}

auto CodeMorph::ebcdic_to_ascii(std::span<const std::byte> packed_bytes, size_t &index,
                                const int num_bytes) -> std::string {
	std::string result(num_bytes, '0');

	for (int i = 0; i < num_bytes; i++)
		result[i] = static_cast<char>(ebcdic_to_ascii_table[static_cast<unsigned int>(packed_bytes[index + i])]);

	index += num_bytes;

	return result;
}

auto CodeMorph::ebcdic_to_ascii(std::span<const std::byte> packed_bytes,
                                const int num_bytes) -> std::string {
	std::string result(num_bytes, '0');

	for (int i = 0; i < num_bytes; i++)
		result[i] = static_cast<char>(ebcdic_to_ascii_table[static_cast<unsigned int>(packed_bytes[i])]);

	return result;
}
