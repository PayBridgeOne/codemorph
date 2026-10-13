// bench_codemorph.cpp
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <codemorph/codemorph.hpp>

TEST_CASE("hex_to_bytes performance", "[bench][hex_to_bytes]") {
    // Build a bigger input to get stable timings
    std::string hex_input;
    hex_input.reserve(6 * 10'000); // "4F20A1" repeated
    for (int i = 0; i < 10'000; ++i)
        hex_input += "4F20A1";

    BENCHMARK("hex_to_bytes 60 KB") {
        // Return the value so the compiler cannot optimize it away
        return codemorph::hex_to_bytes(hex_input);
    };
}

TEST_CASE("bytes_to_hex performance", "[bench][bytes_to_hex]") {
    std::vector<std::byte> data;
    data.reserve(30'000); // 30 KB (~60 KB hex output)
    for (int i = 0; i < 30'000; ++i)
        data.push_back(std::byte{static_cast<unsigned char>(i)});

    BENCHMARK("bytes_to_hex 30 KB") {
        return codemorph::bytes_to_hex(data);
    };
}

TEST_CASE("ascii/bcd roundtrip performance", "[bench][bcd]") {
    std::string ascii;
    ascii.reserve(20'000);
    for (int i = 0; i < 10'000; ++i)
        ascii += "1234"; // 40 KB ascii

    BENCHMARK("ascii_to_bcd 40 KB") {
        return codemorph::ascii_to_bcd(ascii, codemorph::FieldPadding::NONE);
    };

    auto bcd = codemorph::ascii_to_bcd(ascii, codemorph::FieldPadding::NONE);
    BENCHMARK("bcd_to_ascii 40 KB") {
        return codemorph::bcd_to_ascii(bcd, codemorph::FieldPadding::NONE, static_cast<int>(ascii.size()));
    };
}

TEST_CASE("EBCDIC roundtrip performance", "[bench][ebcdic]") {
    std::string text;
    text.reserve(40'000);
    for (int i = 0; i < 20'000; ++i)
        text += "AB";

    BENCHMARK("ascii_to_ebcdic 40 KB") {
        std::vector<std::byte> buf(text.size());
        size_t idx = 0;
        codemorph::ascii_to_ebcdic(text, buf, idx);
        return buf; // prevent optimization
    };

    std::vector<std::byte> ebcdic(text.size());
    {
        size_t idx = 0;
        codemorph::ascii_to_ebcdic(text, ebcdic, idx);
    }

    BENCHMARK("ebcdic_to_ascii 40 KB") {
        size_t idx = 0;
        return codemorph::ebcdic_to_ascii(ebcdic, idx, ebcdic.size());
    };
}
