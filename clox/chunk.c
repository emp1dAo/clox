#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "vm.h"
#include "value.h"

// Initialize a new chunk;
void initChunk(Chunk* chunk) {
  chunk -> count = 0;
  chunk -> capacity = 0;
  chunk -> code = NULL;
  chunk -> lines = NULL;
  initValueArray(&chunk -> constants);
}

// Append a byte to the end of the chunk;
void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk -> capacity < chunk -> count + 1) {
    int oldCapacity = chunk -> capacity;
    chunk -> capacity = GROW_CAPACITY(oldCapacity);
    chunk -> code = GROW_ARRAY(uint8_t, chunk -> code,
                               oldCapacity, chunk -> capacity);
    chunk -> lines = GROW_ARRAY(int, chunk -> lines,
                                oldCapacity, chunk -> capacity);
  }
  chunk -> code[chunk -> count] = byte;
  chunk -> lines[chunk -> count] = line;
  chunk -> count ++;
}

int addConstant(Chunk* chunk, Value value) {
  push(value);
  writeValueArray(&chunk -> constants, value);
  return chunk -> constants.count - 1;
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk -> code, chunk -> capacity);
  FREE_ARRAY(int, chunk -> lines, chunk -> capacity);
  freeValueArray(&chunk -> constants);
  initChunk(chunk);
}
