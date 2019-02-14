#include <iostream>
#include <iomanip>

#include <utility.h>

void func(Utility::IUtfConvertor& iconv, std::string data);

int main()
{
	
	// UTF-8 narrow multibyte encoding
	std::string data = u8"z\u00df\u6c34\U0001f34c";
	// or u8"zß水🍌"
	// or "\x7a\xc3\x9f\xe6\xb0\xb4\xf0\x9f\x8d\x8c";
    auto convertor = Utility::IUtfConvertor::Create();
    func(*convertor, std::move(data));//we do not pass sownersip of convertor - just let it use our object for a time it is running

    //as soon asfunc exists - convertor is again our responsibility

	
}


void func(Utility::IUtfConvertor& iconv, std::string data)
{
    for (auto i = 0; i < 1; i++)
    {
        std::wstring strw = iconv.utf8toutf16(data);
        std::cout << "The UTF-8 string contains the following UTF-16 code points: \n";
        for (wchar_t c : strw) {
            std::cout << ": U+" << std::hex << std::setw(4) << std::setfill('0') << c << '\n';
        }
    }
}
