#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int main()
{
	struct IFactoryApi* p = GetInstance();

	size_t len = GetSize(p);

	char* buf = malloc(len);

	if (buf)
	{
		GetString(p, buf, len);
		printf("%s\n", buf);
		free(buf);
	}

	SetString(p, "test2");

	len = GetSize(p);

	buf = malloc(len);

	if (buf)
	{
		GetString(p, buf, len);
		printf("%s\n", buf);
		free(buf);
	}
	DestructInstance(p);
}