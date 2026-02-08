#ifndef VM_OBJECT_H
#define VM_OBJECT_H

/**
 * Interesting definition: type punning
 *
 * It’s an example of type punning, but that term is too broad. In the absence
 * of any better ideas, I’ll call it struct inheritance, because it relies
 * on structs and roughly follows how single-inheritance of state works in
 * object-oriented languages.
 *
 * Like a tagged union, each Obj starts with a tag field that identifies
 * what kind of object it is—string, instance, etc. Following that are the
 * payload fields. Instead of a union with cases for each type, each type
 * is its own separate struct.  The tricky part is how to treat these structs
 * uniformly since C  * has no concept of inheritance or polymorphism.
 * I’ll explain that soon,  * but first lets get the preliminary stuff out
 * of the way.
 *
 * "Robert Nystrom"
 */


#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)        (AS_OBJ(value)->type)

#define IS_STRING(value)       isObjType(value, OBJ_STRING)

#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)

typedef enum {
    OBJ_STRING,
} ObjType;

struct Obj {
    ObjType type;
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
};

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}


#endif //VM_OBJECT_H