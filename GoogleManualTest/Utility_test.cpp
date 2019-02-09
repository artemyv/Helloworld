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
        for(auto i=0;i<2048;i++)
            data += u8"水";
        std::wstring expected;
        for (auto i = 0; i < 2048; i++)
            expected += L"水";
        auto result = utf8toutf16(data);
        ASSERT_EQ(result, expected);
    }

}  // namespace
