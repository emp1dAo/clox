#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
  Chunk* chunk;
  
  // IP means instruction pointer.
  // x86, x64, and the CLR call it “IP”. 68k, PowerPC, ARM, p-code
  // and the JVM call it “PC”, for program counter.
  uint8_t* ip; 
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();

void freeVM();

InterpretResult interpret(Chunk* chunk);

#endif
