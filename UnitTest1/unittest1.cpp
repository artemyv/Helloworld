#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\test1\test.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here

			std::string data = u8"zß水🍌";
			std::wstring result = utf8toutf16(data);

			Assert::AreEqual(result, std::wstring(L"zß水🍌"));
		}

	};
}