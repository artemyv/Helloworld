#pragma once

#ifdef __cplusplus
#include <string>
extern "C"
{
#endif
	struct IFactoryApi;
	struct IFactoryApi* GetInstance();
	size_t GetSize(const struct IFactoryApi* p);
	size_t GetString(const struct IFactoryApi* p, char* buf, size_t len);
	void SetString(struct IFactoryApi* p, const char* buf);
	void DestructInstance(struct IFactoryApi* p);
#ifdef __cplusplus
}
#endif
