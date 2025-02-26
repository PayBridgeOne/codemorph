#include "codemorph.hpp"

void CodeMorph::int2Bytes(int value, std::span<std::byte> &packedBytes, int &index, const int numHexDigits)
{
    if (numHexDigits == 2)
    {
        packedBytes[index] = static_cast<std::byte>(value);
        ++index;
    }
    else
    {
        for (int i = 0; i < numHexDigits; i++)
        {
            packedBytes[index + i] = static_cast<std::byte>(value >> i * 8 & 0xFF);
        }
        index += numHexDigits;
    }
}

void CodeMorph::int2Bcd(int value, std::span<std::byte> &packedBytes, int &index, int numBytes)
{
    numBytes /= 2;
    std::vector<std::byte> buffer(numBytes);

    for (int i = numBytes - 1; i >= 0; i--)
    {
        int digit = value % 100;
        value /= 100;
        buffer[i] = static_cast<std::byte>((digit / 10 * 16) + (digit % 10));
    }

    std::ranges::copy(buffer, packedBytes.begin() + index);
    index += numBytes;
}

void CodeMorph::ascii2Bcd(const std::string &value, std::span<std::byte> &packedBytes, int &index, const FieldPadding padding)
{
    auto valueLength = value.length();
    int startIndex = 0;
    const bool needPadding = valueLength % 2 != 0;

    if (needPadding && padding == FieldPadding::LEFT)
    {
        packedBytes[index++] = static_cast<std::byte>(value[0] - 0x30);
        startIndex++;
    }
    else if (needPadding && padding == FieldPadding::RIGHT)
    {
        valueLength--;
    }

    for (int i = startIndex; i < valueLength; i += 2)
    {
        packedBytes[index++] = static_cast<std::byte>((value[i] - 0x30) * 0x10 + value[i + 1] - 0x30);
    }

    if (needPadding && padding == FieldPadding::RIGHT)
    {
        packedBytes[index++] = static_cast<std::byte>((value[valueLength] - 0x30) * 0x10);
    }
}

void CodeMorph::ascii2Bytes(const std::string &strASCIIString, std::span<std::byte> &packedBytes, size_t &index)
{
    const auto len = strASCIIString.length();

    for (int i = 0; i < len; i++)
        packedBytes[index + i] = static_cast<std::byte>(strASCIIString[i]);

    index += len;
}

void CodeMorph::hex2Bytes(const std::string& value, std::vector<std::byte>& packedBytes, size_t& index) {
    const size_t binLength = value.length() / 2;
    packedBytes.resize(index + binLength);

    for (size_t i = 0, j = index; i < binLength; i++, j++) {
        packedBytes[j] = static_cast<std::byte>(
            std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2])]) << 4 |
             std::to_integer<uint8_t>(hex_lookup[static_cast<uint8_t>(value[i * 2 + 1])])
        );
    }

    index += binLength;
}

void CodeMorph::ascii2Ebcdic(const std::string &value, std::span<std::byte> &packedBytes, size_t &index)
{
    const auto srcLength = value.length();

    for (int i = 0; i < srcLength; i++)
    {
        packedBytes[index + i] = ascii_to_ebcdic[static_cast<unsigned char>(value[i])];
    }

    index += srcLength;
}

int CodeMorph::bytes2Int(const std::span<std::byte> &packedBytes, int &index, const int numHexDigits)
{
    int result = 0;
    int pos = (numHexDigits / 2 - 1) * 8;

    for (int i = 0; i < numHexDigits / 2; i++)
    {
        result |= static_cast<int>(packedBytes[index + i]) << pos;
        pos -= 8;
    }

    index += numHexDigits / 2;

    return result;
}

int CodeMorph::bcd2Int(const std::span<std::byte>& packedBytes, int& index, const int numHexDigits)
{
    int result = 0;
    const int len = numHexDigits / 2;

    for (int i = 0; i < len; i++)
    {
        result = result * 100 + ((static_cast<int>(packedBytes[index + i]) >> 4) * 10) + (static_cast<int>(packedBytes[index + i]) & 0xf);
    }

    index += len;

    return result;
}

std::string CodeMorph::bcd2Ascii(std::span<std::byte>& packedBytes, int& index, const FieldPadding padding, const int valueLength)
    {
        std::string value(valueLength, '0');

        if (valueLength % 2 != 0)
        {
            if (padding == FieldPadding::LEFT)
            {
                value[0] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) & 0x0F) + 0x30);
                index++;
                for (int i = 1; i < valueLength; i += 2)
                {
                    value[i] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) >> 4) + 0x30);
                    value[i + 1] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) & 0x0F) + 0x30);
                    index++;
                }
            }
            else
            {
                int i;
                for (i = 0; i < valueLength - 1; i += 2)
                {
                    value[i] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) >> 4) + 0x30);
                    value[i + 1] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) & 0x0F) + 0x30);
                    index++;
                }
                value[i] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) >> 4) + 0x30);
                index++;
            }
        }
        else
        {
            for (int i = 0; i < valueLength; i += 2)
            {
                value[i] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) >> 4) + 0x30);
                value[i + 1] = static_cast<char>((static_cast<unsigned int>(packedBytes[index]) & 0x0F) + 0x30);
                index++;
            }
        }
        return value;
    }

std::string CodeMorph::bytes2Ascii(std::span<std::byte>& packedBytes, int& index, const int numBytes)
{
    std::string result(numBytes, '0');

    for (int i = 0; i < numBytes; i++)
        result[i] = static_cast<char>(packedBytes[index + i]);

    index += numBytes;

    return result;
}

std::string CodeMorph::bytes2Hex(const std::span<std::byte>& packedBytes, int& index, const int numBytes) {
    std::string hexString;
    hexString.reserve(numBytes * 2);

    for (int i = 0; i < numBytes; ++i) {
        hexString.append(hex_string_lookup[std::to_integer<uint8_t>(packedBytes[index + i])]);
    }

    index += numBytes;
    return hexString;
}

std::string CodeMorph::bytes2Hex(const std::span<std::byte>& bytes, const int length) {
    std::string hexString;
    hexString.reserve(length * 2);

    for (int i = 0; i < length; ++i) {
        hexString.append(hex_string_lookup[std::to_integer<uint8_t>(bytes[i])]);
    }

    return hexString;
}

std::string CodeMorph::ebcdic2Ascii(std::span<std::byte>& packedBytes, int& index, const int numBytes)
{
    std::string result(numBytes, '0');

    for (int i = 0; i < numBytes; i++)
        result[i] = static_cast<char>(ebcdic_to_ascii[static_cast<unsigned int>(packedBytes[index + i])]);

    index += numBytes;

    return result;
}
