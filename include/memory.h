#ifndef sabrina_memory_h
#define sabrina_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, ptr, old_cnt, new_cnt) \
	reallocate(ptr, sizeof(type) * (old_cnt), \
	sizeof(type) * (new_cnt))

#define FREE_ARRAY(type, ptr, old_cnt) \
	reallocate(ptr, sizeof(type) * old_cnt, 0)

void* reallocate(void *ptr, size_t old_sz, size_t new_sz);
#endif
