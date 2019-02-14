#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <utility.h>

#include "..\test1\widget.cpp"

#include <sstream>

TEST_CASE("Test printer driver", "[Convertor]") {
 
    Printer wr('A');
    Printer wi(5);
    Driver n;
    std::ostringstream ss;
    ss << '<';
    n.usePrinter(ss,wr);
    n.usePrinter(ss, wi);
    ss << '>';

    REQUIRE(ss);
    REQUIRE(ss.str() == "<A,5,>");

}

TEST_CASE("Convertion performed properly", "[Convertor]") {
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);


    std::unique_ptr<Utility::IUtfConvertor> convertor = Utility::IUtfConvertor::Create();

    REQUIRE(convertor->utf8toutf16(u8"zß水🍌 שלום друзья") == std::wstring(L"zß水🍌 שלום друзья"));
    REQUIRE(convertor->utf8toutf16(std::string(u8"zß水🍌 שלום друзья")) == std::wstring(L"zß水🍌 שלום друзья"));
    REQUIRE(convertor->utf8toutf16(nullptr) == std::wstring(L""));

    std::string data;
    auto count = 10000;
    for (auto i = 0; i < count; i++)
        data += u8"水";
    std::wstring expected;
    for (auto i = 0; i < count; i++)
        expected += L"水";
    REQUIRE(convertor->utf8toutf16(data) == expected);
}

TEST_CASE("Ignore invalid characters", "[Convertor]") {

    std::unique_ptr<Utility::IUtfConvertor> convertor = Utility::IUtfConvertor::Create();

    /*
        "Copyright                     : U+00A9 (A9) : **[\xA9]**",
        "Degree                        : U+00B0 (B0) : **[\xB0]**",
        "Micro                         : U+00B5 (B5) : **[\xB5]**",
        "Capital A with diaeresis      : U+00C4 (C4) : **[\xC4]**",
        "Capital O with diaeresis      : U+00D6 (D6) : **[\xD6]**",
        "Small a with diaeresis        : U+00E4 (E4) : **[\xE4]**",
        "Small u with diaeresis        : U+00FC (FC) : **[\xFC]**",
        "Small letter y with diaeresis : U+00FF (FF) : **[\xFF]**"
     */
    REQUIRE(convertor->utf8toutf16("aaa\x00A9\x00B0\x00B5\x00C4\x00D6\x00E4\x00FC\x00FF" "bbb") == std::wstring(L"aaa\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFDbbb")); //incorrect UTF character - conversion skipped
}

TEST_CASE("Failed due to invalid characters", "[Convertor]") {
    std::unique_ptr<Utility::IUtfConvertor> convertor = Utility::IUtfConvertor::Create();

    REQUIRE(convertor->utf8toutf16("aaa\x00A9" "bbb", false) == std::wstring(L"")); //incorrect UTF character - conversion failes
    REQUIRE(convertor->utf8toutf16("aaa\x00B0" "bbb", false) == std::wstring(L"")); //incorrect UTF character - conversion failes
}