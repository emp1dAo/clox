#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// Define opcode;
typedef enum {
  OP_RETURN,
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_POP,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_DEFINE_GLOBAL,
  OP_SET_GLOBAL,
  OP_GET_GLOBAL,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
} OpCode;

/*
  Byte is a series of instructions,
  which will include other data,
  use a struct to save these;
*/
typedef struct {
  // Have allocated;
  int count;
  // Allocated entries are actually in use;
  int capacity;
  // A dynamic array of instructions;
  uint8_t* code;
  int* lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);

void writeChunk(Chunk* chunk, uint8_t byte, int line);

int addConstant(Chunk* chunk, Value value);

void freeChunk(Chunk* chunk);

#endif
