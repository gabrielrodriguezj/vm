#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void initVM() {
}

void freeVM() {
}

/*
 * When the interpreter executes a user’s program, it will spend something
 * like 90% of its time inside run(). It is the beating heart of the VM.
 */
static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {

#ifdef DEBUG_TRACE_EXECUTION
        disassembleInstruction(vm.chunk,
                               (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(Chunk* chunk) {
    /*
     * ip is initialized by pointing it at the first byte of code in the chunk.
     * That instructions haven’t been executed yet, so ip points to the instruction about to be executed.
     * This will be true during the entire time the VM is running: the IP always points to the next instruction,
     * not the one currently being handled.
     */
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}