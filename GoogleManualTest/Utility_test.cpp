#include "utility.cpp"

#pragma warning (push,1)
#include "gtest/gtest.h"
#pragma warning (pop)

namespace {

    class Narrow2WideConverterTest :public ::testing::Test
    {

    };
    // Tests that the Foo::Bar() method does Abc.
    TEST_F(Narrow2WideConverterTest, TestMixedu8String) {
        std::string data = u8"zß水🍌 שלום друзья";
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"zß水🍌 שלום друзья"));
    }

    TEST_F(Narrow2WideConverterTest, TestConstChar)
    {
        const char* data = u8"zß水🍌 שלום друзья";
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"zß水🍌 שלום друзья"));
    }
    TEST_F(Narrow2WideConverterTest, TestNullptr)
    {
        const char* data = nullptr;
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L""));
    }
    TEST_F(Narrow2WideConverterTest, TestLongString)
    {
        std::string data;
        auto count = 10000;
        for(auto i=0;i< count;i++)
            data += u8"水";
        std::wstring expected;
        for (auto i = 0; i < count; i++)
            expected += L"水";
        auto result = utf8toutf16(data);
        ASSERT_EQ(result, expected);
    }
    TEST_F(Narrow2WideConverterTest, TestIgnore)
    {
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
        const char* const data = "aaa\x00A9\x00B0\x00B5\x00C4\x00D6\x00E4\x00FC\x00FF" "bbb";

        auto result = utf8toutf16(data, true);
        ASSERT_EQ(result, std::wstring(L"aaa\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFDbbb")); //incorrect UTF character - conversion skipped
    }
    TEST_F(Narrow2WideConverterTest, Test00A9)
    {
        const char* const data = "aaa\x00A9" "bbb"; //©

        auto result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"")); //incorrect UTF character - conversion failes
    }
    TEST_F(Narrow2WideConverterTest, Test00B0)
    {
        const char* const data = "aaa\x00B0" "bbb"; //©

        auto result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"")); //incorrect UTF character - conversion failes
    }
}  // namespace
