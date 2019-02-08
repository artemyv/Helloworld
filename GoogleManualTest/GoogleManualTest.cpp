#include "utility.h"

#pragma warning (push,1)
#include "gtest/gtest.h"
#pragma warning (pop)

namespace {

    class Narrow2WideConverterTest:public ::testing::Test
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
    TEST_F(Narrow2WideConverterTest, TestTobeFailed)
    {
        const char* data = "Yes";
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"No"));
    }

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}