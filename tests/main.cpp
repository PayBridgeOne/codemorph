//
// Created by greye on 2/16/2025.
//
#include <catch2/catch_test_macros.hpp>
#include "../codemorph.hpp"

TEST_CASE("test_hex_to_bytes converts hex string to byte vector correctly", "[test_hex_to_bytes]") {
    const std::string hex_input = "4F20A1";
    auto result = CodeMorph::test_hex_to_bytes(hex_input);

    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == std::byte{0x4F});
    REQUIRE(result[1] == std::byte{0x20});
    REQUIRE(result[2] == std::byte{0xA1});
}



// ───────────────────────────────────────────────
// 🔄 EBCDIC
// ───────────────────────────────────────────────
TEST_CASE("ascii_to_ebcdic + ebcdic_to_ascii roundtrip") {
    std::string text = "AB";
    std::vector<std::byte> buffer(2);
    size_t index = 0;

    CodeMorph::ascii_to_ebcdic(text, buffer, index);

    index = 0;
    std::string result = CodeMorph::ebcdic_to_ascii(buffer, index, 2);

    REQUIRE(result == text);
}