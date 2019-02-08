#include  <string>
#include <utility.h>

#define WIN32_LEAN_AND_MEAN 
#pragma warning ( push , 1 )
#include <windows.h>
#pragma warning ( pop )

std::wstring utf8toutf16(const char* input)
{
    if (nullptr == input) return L"";
    return utf8toutf16(std::string(input));
}

std::wstring utf8toutf16(const std::string& input)
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
