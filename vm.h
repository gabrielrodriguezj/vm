#ifndef VM_VM_H
#define VM_VM_H

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    /*
     * x86, x64, and the CLR call it “IP”. 68k, PowerPC, ARM, p-code, and the JVM
     * call it “PC”, for program counter.
     */
    uint8_t* ip; // instruction pointer
} VM;


typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
  } InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
#endif //VM_VM_H