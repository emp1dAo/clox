#include <stdlib.h>

#include "memory.h"

// Allocating memory, freeing memory and changing the size of an existing allocation;
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, newSize);
  if (result == NULL) exit(1);
  return result;
} 
