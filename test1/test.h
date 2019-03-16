#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

	struct MY_HANDLE_IMPL
	{
		int _dummy;
#ifdef __cplusplus
		virtual size_t GetString( char* buf, size_t len) const noexcept = 0;
		virtual ~MY_HANDLE_IMPL() = default;
#endif
	};
	typedef const struct MY_HANDLE_IMPL* MY_HANDLE;
	MY_HANDLE GetInstance();
	size_t GetSize( MY_HANDLE p);
	size_t GetString( MY_HANDLE p, char* buf, size_t len);
	void DestructInstance(MY_HANDLE p);
#ifdef __cplusplus
}
#endif
