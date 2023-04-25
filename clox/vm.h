#ifndef clox_vm_h
#define clox_vm_h

#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
  ObjClosure* closure;
  ObjFunction* function;
  uint8_t* ip;
  Value* slots;
} CallFrame;

typedef struct {
  /*
    Chunk* chunk;
  
   // IP means instruction pointer.
    // x86, x64, and the CLR call it “IP”. 68k, PowerPC, ARM, p-code
    // and the JVM call it “PC”, for program counter.
    uint8_t* ip;
  */

  // Each CallFrame has its own ip and its own pointer to the ObjFunction
  CallFrame frames[FRAMES_MAX];
  int frameCount;
  Value stack[STACK_MAX]; 
  Value* stackTop;
  Table globals;
  Table strings;
  ObjUpvalue* openUpvalues;
  Obj* objects;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

extern VM vm;

void initVM();

void freeVM();

InterpretResult interpret(const char* chunk);

void push(Value value);

Value pop();

#endif
