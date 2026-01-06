#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
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
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk,
                               (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
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