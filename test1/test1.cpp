#include <iostream>
#include <iomanip>

#include <utility.h>


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



