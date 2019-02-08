#include "stdafx.h"
#include "CppUnitTest.h"
#include "utility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
BEGIN_TEST_MODULE_ATTRIBUTE()
TEST_MODULE_ATTRIBUTE(L"Date", L"2019/02/07")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
    Logger::WriteMessage("In Module Initialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
    Logger::WriteMessage("In Module Cleanup");
}

namespace UnitTestUtility
{
    TEST_CLASS(Narrow2WideConverter)
    {
    public:

        BEGIN_TEST_METHOD_ATTRIBUTE(TestMixedu8String)
            TEST_OWNER(L"vart")
            TEST_PRIORITY(1)
        END_TEST_METHOD_ATTRIBUTE()

        TEST_METHOD(TestMixedu8String)
        {
            std::string data = u8"zß水🍌 שלום друзья";
            std::wstring result = utf8toutf16(data);
            Assert::AreEqual(result, std::wstring(L"zß水🍌 שלום друзья"));
        }

        BEGIN_TEST_METHOD_ATTRIBUTE(TestConstChar)
            TEST_OWNER(L"vart")
            TEST_PRIORITY(1)
        END_TEST_METHOD_ATTRIBUTE()
        TEST_METHOD(TestConstChar)
        {
            const char* data = u8"zß水🍌 שלום друзья";
            std::wstring result = utf8toutf16(data);
            Assert::AreEqual(result, std::wstring(L"zß水🍌 שלום друзья"));
        }
        BEGIN_TEST_METHOD_ATTRIBUTE(TestNullptr)
            TEST_OWNER(L"vart")
            TEST_PRIORITY(1)
            END_TEST_METHOD_ATTRIBUTE()
            TEST_METHOD(TestNullptr)
        {
            const char* data = nullptr;
            std::wstring result = utf8toutf16(data);
            Assert::AreEqual(result, std::wstring(L""));
        }

    };
}