#ifndef VM_VALUE_H
#define VM_VALUE_H

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum {
    VAL_BOOL,
    VAL_NULL,
    VAL_NUMBER,
    VAL_OBJ,
    // When a Value’s type is VAL_OBJ, the payload is a pointer to the
    // heap memory, so we add another case to the union for that.
  } ValueType;

// Data structure "Tagged union"
typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Obj* obj;
    } as;
} Value;

// These macros return true if the Value has that type.
#define IS_BOOL(value)    ((value).type == VAL_BOOL)
#define IS_NULL(value)     ((value).type == VAL_NULL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)
#define IS_OBJ(value)     ((value).type == VAL_OBJ)

// There’s no AS_NULL macro because there is only one null value, so
// a Value with type VAL_NULL doesn't carry any extra data.
#define AS_OBJ(value)     ((value).as.obj)
#define AS_BOOL(value)    ((value).as.boolean)
#define AS_NUMBER(value)  ((value).as.number)

#define BOOL_VAL(value)   ((Value){VAL_BOOL, {.boolean = value}})
#define NULL_VAL           ((Value){VAL_NULL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object)   ((Value){VAL_OBJ, {.obj = (Obj*)object}})

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

#endif //VM_VALUE_H