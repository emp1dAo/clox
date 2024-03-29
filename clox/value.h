#ifndef clox_value_h
#define clox_value_h

#include <string.h>
#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;
#ifdef NAN_BOXING

#define SIGN_BIT ((uint64_t)0x8000000000000000)
#define QNAN     ((uint64_t)0x7ffc000000000000)

#define TAG_NIL   1 // 01
#define TAG_FALSE 2 // 10
#define TAG_TRUE  3 // 11

typedef uint64_t Value;

//> is-bool
#define IS_BOOL(value)      (((value) | 1) == TRUE_VAL)
//< is-bool
//> is-nil
#define IS_NIL(value)       ((value) == NIL_VAL)
//< is-nil
#define IS_NUMBER(value)    (((value) & QNAN) != QNAN)
//< is-number
//> is-obj
#define IS_OBJ(value) \
    (((value) & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT))
//< is-obj
//> as-number

//> as-bool
#define AS_BOOL(value)      ((value) == TRUE_VAL)
//< as-bool
#define AS_NUMBER(value)    valueToNum(value)
//< as-number
//> as-obj
#define AS_OBJ(value) \
    ((Obj*)(uintptr_t)((value) & ~(SIGN_BIT | QNAN)))
//< as-obj
//> number-val

//> bool-val
#define BOOL_VAL(b)     ((b) ? TRUE_VAL : FALSE_VAL)
//< bool-val
//> false-true-vals
#define FALSE_VAL       ((Value)(uint64_t)(QNAN | TAG_FALSE))
#define TRUE_VAL        ((Value)(uint64_t)(QNAN | TAG_TRUE))
//< false-true-vals
//> nil-val
#define NIL_VAL         ((Value)(uint64_t)(QNAN | TAG_NIL))
//< nil-val
#define NUMBER_VAL(num) numToValue(num)
//< number-val
//> obj-val
#define OBJ_VAL(obj) \
    (Value)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))
//< obj-val
//> value-to-num

static inline double valueToNum(Value value) {
  double num;
  memcpy(&num, &value, sizeof(Value));
  return num;
}

static inline Value numToValue(double num) {
  Value value;
  memcpy(&value, &num, sizeof(double));
  return value;
}

#else

typedef enum {
  VAL_BOOL,
  VAL_NIL,
  VAL_NUMBER,
  VAL_OBJ,
} ValueType;

typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
    Obj* obj;
  } as; 
} Value;

#define IS_BOOL(value)    ((value).type == VAL_BOOL)
#define IS_NIL(value)     ((value).type == VAL_NIL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)
#define IS_OBJ(value)     ((value).type == VAL_OBJ)
#define AS_OBJ(value)     ((value).as.obj)
#define AS_BOOL(value)    ((value).as.boolean)
#define AS_NUMBER(value)  ((value).as.number)
#define BOOL_VAL(value)   ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL           ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object)   ((Value){VAL_OBJ, {.obj = (Obj*)object}})

#endif

typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

bool valuesEqual(Value a, Value b);

void initValueArray(ValueArray* array);

void writeValueArray(ValueArray* array, Value value);

void freeValueArray(ValueArray* array);

void printValue(Value value);

#endif
