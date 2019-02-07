#include <iostream>
#include <iomanip>

#include <utility.h>

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