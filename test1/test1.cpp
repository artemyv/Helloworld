#include "test.h"
#include <string>
#include <cstring>

extern "C" struct IFactoryApi
{
	virtual ~IFactoryApi() = default;

	virtual std::string GetString() const = 0;
	virtual void SetString(std::string&& val) = 0;
	virtual void SetString(const std::string_view& val) = 0;
};

class MyClass : public IFactoryApi
{
	std::string _val = "test";
public :
	std::string GetString() const override  {
		return _val;
	}
	void SetString(const std::string_view& val) override {
		_val = val;
	}
	void SetString(std::string&& val) override {
		_val = std::move(val);
	}
};

extern "C"  IFactoryApi* GetInstance()
{
	return new MyClass;
}

extern "C" size_t GetSize(const  IFactoryApi* p)
{
	return p->GetString().size()+1;
}
extern "C" size_t GetString(const IFactoryApi* p, char* buf, size_t len)
{
	auto res = p->GetString();
	if (len == 0 || buf == nullptr)
	{
		return res.length() + 1;
	}

	buf[0] = 0;
	strncat(buf, res.c_str(), len - 1);
	return res.length() + 1;
}

extern "C" void SetString(struct IFactoryApi* p, const char* buf)
{
	p->SetString(std::string_view{buf});
}


extern "C" void DestructInstance(IFactoryApi* p)
{
	delete p;
}
