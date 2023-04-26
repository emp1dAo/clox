#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"
#include "object.h"

#define ALLOCATE(type, count) \
  (type*)reallocate(NULL, 0, sizeof(type) * (count))

#define FREE(type, pointer) \
  reallocate(pointer, sizeof(type), 0)

// This macro calculates a new capacity based on a given current capacity;
// It scales based on the old size, we grow by a factor of two;
#define GROW_CAPACITY(capacity) \
  ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
  (type*)reallocate(pointer, sizeof(type) * (oldCount), \
                    sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
  reallocate(pointer, sizeof(type) * (oldCount), 0)

// Allocating memory, freeing memory and changing the size of an existing allocation;
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

void markObject(Obj* object);

void markValue(Value value);

void collectGarbage();

void freeObjects();

#endif
