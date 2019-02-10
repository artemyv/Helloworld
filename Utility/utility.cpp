#include  <string>
#include <utility.h>

#define WIN32_LEAN_AND_MEAN 
#pragma warning ( push , 1 )
#include <windows.h>
#pragma warning ( pop )

namespace Utility
{
    class CUtfConvertor:public IUtfConvertor
    {
    protected:
        std::wstring utf8toutf16(const std::string& input, bool ignore_invalid = true) override;
        std::wstring utf8toutf16(const char* input, bool ignore_invalid = true) override;
    };
}

std::unique_ptr<Utility::IUtfConvertor>  Utility::IUtfConvertor::Create()
{
    auto result = std::make_unique<Utility::CUtfConvertor>();
    return result;
}

std::wstring Utility::CUtfConvertor::utf8toutf16(const char* input, bool ignore_invalid)
{
    if (nullptr == input) return L"";
    return utf8toutf16(std::string(input), ignore_invalid);
}

std::wstring Utility::CUtfConvertor::utf8toutf16(const std::string& input, bool ignore_invalid)
{
    auto res = MultiByteToWideChar(CP_UTF8, ignore_invalid ? 0 : MB_ERR_INVALID_CHARS, input.c_str(), static_cast<int>(input.size()), nullptr, 0);
    if (res <= 0)
    {
        return L"";
    }
    std::wstring buf;
    buf.resize(res);
    res = MultiByteToWideChar(CP_UTF8, ignore_invalid ? 0 : MB_ERR_INVALID_CHARS, input.c_str(), static_cast<int>(input.size()), &buf[0], res);
    if (res <= 0)
    {
        return L"";
    }
    return buf;
}

#ifdef GOOGLE_TEST
#pragma warning (push,1)
#include "gtest/gtest.h"
#pragma warning (pop)

namespace {

    class Narrow2WideCConverterTest :public ::testing::Test, public Utility::CUtfConvertor
    {
    };
    // Tests that the Foo::Bar() method does Abc.
    TEST_F(Narrow2WideCConverterTest, TestMixedu8String) {
        std::string data = u8"zß水🍌 שלום друзья";
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"zß水🍌 שלום друзья"));
    }

    TEST_F(Narrow2WideCConverterTest, TestConstChar)
    {
        const char* data = u8"zß水🍌 שלום друзья";
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"zß水🍌 שלום друзья"));
    }
    TEST_F(Narrow2WideCConverterTest, TestNullptr)
    {
        const char* data = nullptr;
        std::wstring result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L""));
    }
    TEST_F(Narrow2WideCConverterTest, TestLongString)
    {
        std::string data;
        auto count = 10000;
        for (auto i = 0; i < count; i++)
            data += u8"水";
        std::wstring expected;
        for (auto i = 0; i < count; i++)
            expected += L"水";
        auto result = utf8toutf16(data);
        ASSERT_EQ(result, expected);
    }
    TEST_F(Narrow2WideCConverterTest, TestIgnore)
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

        auto result = utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"aaa\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFDbbb")); //incorrect UTF character - conversion skipped
    }
    TEST_F(Narrow2WideCConverterTest, Test00A9)
    {
        const char* const data = "aaa\x00A9" "bbb"; //©

        auto result = utf8toutf16(data, false);
        ASSERT_EQ(result, std::wstring(L"")); //incorrect UTF character - conversion failes
    }
    TEST_F(Narrow2WideCConverterTest, Test00B0)
    {
        const char* const data = "aaa\x00B0" "bbb"; //©

        auto result = utf8toutf16(data, false);
        ASSERT_EQ(result, std::wstring(L"")); //incorrect UTF character - conversion failes
    }

    class Narrow2WideIConverterTest :public ::testing::Test
    {
    public:
        std::unique_ptr<Utility::IUtfConvertor> convertor = Utility::IUtfConvertor::Create();
    };

    TEST_F(Narrow2WideIConverterTest, TestMixedu8String)
    {
        std::string data = u8"zß水🍌 שלום друзья";
        std::wstring result = convertor->utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"zß水🍌 שלום друзья"));
    }
    TEST_F(Narrow2WideIConverterTest, TestConstChar)
    {
        const char* data = u8"zß水🍌 שלום друзья";
        std::wstring result = convertor->utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"zß水🍌 שלום друзья"));
    }
    TEST_F(Narrow2WideIConverterTest, TestNullptr)
    {
        const char* data = nullptr;
        std::wstring result = convertor->utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L""));
    }
    TEST_F(Narrow2WideIConverterTest, TestLongString)
    {
        std::string data;
        auto count = 10000;
        for (auto i = 0; i < count; i++)
            data += u8"水";
        std::wstring expected;
        for (auto i = 0; i < count; i++)
            expected += L"水";
        auto result = convertor->utf8toutf16(data);
        ASSERT_EQ(result, expected);
    }
    TEST_F(Narrow2WideIConverterTest, TestIgnore)
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

        auto result = convertor->utf8toutf16(data);
        ASSERT_EQ(result, std::wstring(L"aaa\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFD\uFFFDbbb")); //incorrect UTF character - conversion skipped
    }
    TEST_F(Narrow2WideIConverterTest, Test00A9)
    {
        const char* const data = "aaa\x00A9" "bbb"; //©

        auto result = convertor->utf8toutf16(data, false);
        ASSERT_EQ(result, std::wstring(L"")); //incorrect UTF character - conversion failes
    }
    TEST_F(Narrow2WideIConverterTest, Test00B0)
    {
        const char* const data = "aaa\x00B0" "bbb"; //©

        auto result = convertor->utf8toutf16(data, false);
        ASSERT_EQ(result, std::wstring(L"")); //incorrect UTF character - conversion failes
    }
}// namespace

#endif
