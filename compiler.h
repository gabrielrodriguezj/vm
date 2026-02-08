#ifndef VM_COMPILER_H
#define VM_COMPILER_H

#include "object.h"
#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif //VM_COMPILER_H