#include "test.h"
#include <string>
#include <cstring>

class MyClass : public MY_HANDLE_IMPL
{
	std::string _val = "test";
public :
	size_t GetString(char* buf, size_t len) const noexcept override  {
		if (len == 0 || buf == nullptr)
		{
			return _val.length() + 1;
		}

		buf[0] = 0;
		strncat(buf, _val.c_str(), len - 1);
		return _val.length() + 1;
	}
};

extern "C" MY_HANDLE GetInstance()
{
	return new MyClass;
}

extern "C" size_t GetSize( MY_HANDLE p)
{
	return p->GetString(nullptr, 0);
}
extern "C" size_t GetString( MY_HANDLE p, char* buf, size_t len)
{
	return p->GetString(buf, len);
}

extern "C" void DestructInstance(MY_HANDLE p)
{
	delete p;
}
