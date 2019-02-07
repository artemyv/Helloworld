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

        BEGIN_TEST_METHOD_ATTRIBUTE(TestMixedString)
            TEST_OWNER(L"vart")
            TEST_PRIORITY(1)
        END_TEST_METHOD_ATTRIBUTE()

        TEST_METHOD(TestMixedString)
        {

            Logger::WriteMessage("TestMixedString Started for: ");
            std::string data = u8"zß水🍌";
            Logger::WriteMessage(data.c_str());
            std::wstring result = utf8toutf16(data);

            Logger::WriteMessage("Result: ");
            Logger::WriteMessage(result.c_str());

            Assert::AreEqual(result, std::wstring(L"zß水🍌"));
        }
        BEGIN_TEST_METHOD_ATTRIBUTE(TestRightToLeft)
            TEST_OWNER(L"vart")
            TEST_PRIORITY(1)
        END_TEST_METHOD_ATTRIBUTE()
        TEST_METHOD(TestRightToLeft)
        {

            Logger::WriteMessage("TestRightToLeft Started for: ");
            std::string data = u8"שלום друзья";
            Logger::WriteMessage(data.c_str());
            std::wstring result = utf8toutf16(data);

            Logger::WriteMessage("Result: ");
            Logger::WriteMessage(result.c_str());

            Assert::AreEqual(result, std::wstring(L"שלום друзья"));
        }

        BEGIN_TEST_METHOD_ATTRIBUTE(TestToBeFailed)
            TEST_OWNER(L"vart")
            TEST_PRIORITY(1)
            TEST_IGNORE()
        END_TEST_METHOD_ATTRIBUTE()
        TEST_METHOD(TestToBeFailed)
        {

            Logger::WriteMessage("TestToBeFailed Started for: ");
            std::string data = u8"aaa";
            Logger::WriteMessage(data.c_str());
            std::wstring result = utf8toutf16(data);

            Logger::WriteMessage("Result: ");
            Logger::WriteMessage(result.c_str());

            Assert::AreEqual(result, std::wstring(L"bbb"));
        }

    };
}