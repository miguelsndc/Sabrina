#include "memory.h"
#include <stdlib.h>

void *reallocate(void *ptr, size_t old_sz, size_t new_sz) {
  if (new_sz == 0) {
    free(ptr);
    return NULL;
  }
  void *result = realloc(ptr, new_sz);
  if (result == NULL)
    exit(1);
  return result;
}
