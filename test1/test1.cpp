#include "test.h"

#include <iostream>
//#include <fstream>
//#include <string>
//#include <locale>
#include <iomanip>
//#include <codecvt>

#define WIN32_LEAN_AND_MEAN 
#pragma warning ( push , 1 )
#include <windows.h>
#pragma warning ( pop )

std::wstring utf8toutf16(const std::string input)
{
	auto res = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), static_cast<int>(input.size()), nullptr, 0);
	if (res <= 0)
	{
		return L"";
	}
	std::wstring buf;
	buf.resize(res);
	res = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), static_cast<int>(input.size()), &buf[0], res);
	if (res <= 0)
	{
		return L"";
	}
	return buf;
}

int main()
{
	
	// UTF-8 narrow multibyte encoding
	std::string data = u8"z\u00df\u6c34\U0001f34c";
	// or u8"zß水🍌"
	// or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";

	for(auto i=0;i<1; i++)
	{
		std::wstring strw = utf8toutf16(data);
		std::cout << "The UTF-8 string contains the following UTF-16 code points: \n";
		for (wchar_t c : strw) {
			std::cout << ": U+" << std::hex << std::setw(4) << std::setfill('0') << c << '\n';
		}
	}

	//{
	//	std::ifstream f("text.txt", std::ios::in | std::ios::binary);
	//	if (f)
	//	{
	//		std::string contents;
	//		f.seekg(0, std::ios::end);
	//		contents.resize(static_cast<size_t>(f.tellg()));
	//		f.seekg(0, std::ios::beg);
	//		f.read(&contents[0], contents.size());
	//		f.close();


	//		std::wstring strw = utf8toutf16(contents);
	//		std::cout << "The UTF-8 string read from file contains the following UTF-16 code points: \n";
	//		for (wchar_t c : strw) {
	//			std::cout << ": U+" << std::hex << std::setw(4) << std::setfill('0') << c << '\n';
	//		}
	//	}
	//}
}