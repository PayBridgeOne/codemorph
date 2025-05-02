//
// Created by greye on 2/16/2025.
//
#include <catch2/catch_test_macros.hpp>
#include "../codemorph.hpp"

TEST_CASE("hex_to_bytes converts hex string to byte vector correctly", "[hex_to_bytes]") {
    const std::string hex_input = "4F20A1";
    auto result = CodeMorph::hex_to_bytes(hex_input);

    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == std::byte{0x4F});
    REQUIRE(result[1] == std::byte{0x20});
    REQUIRE(result[2] == std::byte{0xA1});
}

TEST_CASE("bytes_to_hex converts byte vector to hex string correctly", "[bytes_to_hex]") {
    std::vector<std::byte> bytes = {std::byte{0x4F}, std::byte{0x20}, std::byte{0xA1}};
    auto result = CodeMorph::bytes_to_hex(bytes);

    REQUIRE(result == "4F20A1");
}

TEST_CASE("int_to_bytes converts integer to byte vector correctly", "[int_to_bytes]") {
    const int value = 12345;
    auto result = CodeMorph::int_to_bytes(value, 4);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == std::byte{0x30});
    REQUIRE(result[1] == std::byte{0x39});
}

TEST_CASE("bytes_to_int converts byte vector to integer correctly", "[bytes_to_int]") {
    std::vector<std::byte> bytes = {std::byte{0x30}, std::byte{0x39}};
    const auto result = CodeMorph::bytes_to_int(bytes, 4);

    REQUIRE(result == 12345);
}

TEST_CASE("ascii_to_bcd converts ASCII string to BCD correctly", "[ascii_to_bcd]") {
    const std::string ascii = "1234";
    auto result = CodeMorph::ascii_to_bcd(ascii, CodeMorph::FieldPadding::NONE);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == std::byte{0x12});
    REQUIRE(result[1] == std::byte{0x34});
}

TEST_CASE("bcd_to_ascii converts BCD to ASCII string correctly", "[bcd_to_ascii]") {
    std::vector<std::byte> bcd = {std::byte{0x12}, std::byte{0x34}};
    auto result = CodeMorph::bcd_to_ascii(bcd, CodeMorph::FieldPadding::NONE, 4);

    REQUIRE(result == "1234");
}

TEST_CASE("ascii_to_ebcdic and ebcdic_to_ascii roundtrip", "[ascii_to_ebcdic][ebcdic_to_ascii]") {
    std::string text = "AB";
    std::vector<std::byte> buffer(2);
    size_t index = 0;

    CodeMorph::ascii_to_ebcdic(text, buffer, index);

    index = 0;
    std::string result = CodeMorph::ebcdic_to_ascii(buffer, index, 2);

    REQUIRE(result == text);
}

TEST_CASE("bcd_to_int with index converts BCD to integer correctly", "[bcd_to_int]") {
    std::vector<std::byte> bcd = {std::byte{0x12}, std::byte{0x34}};
    int index = 0;
    int result = CodeMorph::bcd_to_int(bcd, index, 4);

    REQUIRE(result == 1234);
    REQUIRE(index == 2);
}

TEST_CASE("bcd_to_int without index converts BCD to integer correctly", "[bcd_to_int]") {
    std::vector<std::byte> bcd = {std::byte{0x12}, std::byte{0x34}};
    int result = CodeMorph::bcd_to_int(bcd, 4);

    REQUIRE(result == 1234);
}

TEST_CASE("bcd_to_ascii with index converts BCD to ASCII correctly", "[bcd_to_ascii]") {
    std::vector<std::byte> bcd = {std::byte{0x12}, std::byte{0x34}};
    int index = 0;
    std::string result = CodeMorph::bcd_to_ascii(bcd, index, CodeMorph::FieldPadding::NONE, 4);

    REQUIRE(result == "1234");
    REQUIRE(index == 2);
}

TEST_CASE("bcd_to_ascii without index converts BCD to ASCII correctly", "[bcd_to_ascii]") {
    std::vector<std::byte> bcd = {std::byte{0x12}, std::byte{0x34}};
    std::string result = CodeMorph::bcd_to_ascii(bcd, CodeMorph::FieldPadding::NONE, 4);

    REQUIRE(result == "1234");
}

TEST_CASE("bytes_to_ascii with index converts bytes to ASCII correctly", "[bytes_to_ascii]") {
    std::vector<std::byte> bytes = {std::byte{'A'}, std::byte{'B'}};
    int index = 0;
    std::string result = CodeMorph::bytes_to_ascii(bytes, index, 2);

    REQUIRE(result == "AB");
    REQUIRE(index == 2);
}

TEST_CASE("bytes_to_ascii without index converts bytes to ASCII correctly", "[bytes_to_ascii]") {
    std::vector<std::byte> bytes = {std::byte{'A'}, std::byte{'B'}};
    std::string result = CodeMorph::bytes_to_ascii(bytes, 2);

    REQUIRE(result == "AB");
}

TEST_CASE("ebcdic_to_ascii with index converts EBCDIC to ASCII correctly", "[ebcdic_to_ascii]") {
    std::vector<std::byte> ebcdic = {std::byte{0xC1}, std::byte{0xC2}}; // EBCDIC for "AB"
    size_t index = 0;
    std::string result = CodeMorph::ebcdic_to_ascii(ebcdic, index, 2);

    REQUIRE(result == "AB");
    REQUIRE(index == 2);
}

TEST_CASE("ebcdic_to_ascii without index converts EBCDIC to ASCII correctly", "[ebcdic_to_ascii]") {
    std::vector<std::byte> ebcdic = {std::byte{0xC1}, std::byte{0xC2}}; // EBCDIC for "AB"
    std::string result = CodeMorph::ebcdic_to_ascii(ebcdic, 2);

    REQUIRE(result == "AB");
}
