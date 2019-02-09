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
	auto res = MultiByteToWideChar(CP_UTF8, ignore_invalid?0:MB_ERR_INVALID_CHARS, input.c_str(), static_cast<int>(input.size()), nullptr, 0);
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
