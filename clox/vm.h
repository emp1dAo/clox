#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk* chunk;
  
  // IP means instruction pointer.
  // x86, x64, and the CLR call it “IP”. 68k, PowerPC, ARM, p-code
  // and the JVM call it “PC”, for program counter.
  uint8_t* ip;
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();

void freeVM();

InterpretResult interpret(Chunk* chunk);

void push(Value value);

Value pop();

#endif
