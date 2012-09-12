#include "util.h"

void *util_alloc(void *ptr, size_t size)
{
	void *temp = realloc(ptr, size);
	if (temp != NULL) 
	{
		ptr = temp;
		return ptr;
	}
	
	return NULL;
}