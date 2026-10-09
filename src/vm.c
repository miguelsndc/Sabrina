#include "vm.h"
#include "chunk.h"
#include "value.h"
#include <stdbool.h>
#include <stdio.h>

VM vm;

static void reset_stack(void) { vm.stack_top = vm.stack; }

void vm_st_push(Value val) {
  *vm.stack_top = val;
  vm.stack_top++;
}

Value vm_st_pop(void) {
  vm.stack_top--;
  return *vm.stack_top;
}

static InterpretResult run(void) {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double b = vm_st_pop();                                                    \
    double a = vm_st_pop();                                                    \
    vm_st_push(a op b);                                                        \
  } while (false)
#ifdef DEBUG_TRACE_EXECUTION
  for (Value *slot = vm.stack; slot < vm.stack_top; slot++) {
    printf("[ ");
    print_value(*slot);
    printf(" ]");
  }
  printf("\n");
  disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
  uint8_t instruction;
  for (;;) {
    switch (instruction = READ_BYTE()) {
    case OP_RETURN:
      print_value(vm_st_pop());
      printf("\n");
      return INTERPRET_OK;
    case OP_NEGATE:
      vm_st_push(-vm_st_pop());
      break;
    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_MULTIPLY:
      BINARY_OP(*);
      break;
    case OP_SUBTRACT:
      BINARY_OP(-);
      break;
    case OP_DIVIDE:
      BINARY_OP(/);
      break;
    case OP_CONSTANT:
      Value constant = READ_CONSTANT();
      vm_st_push(constant);
      break;
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

void vm_init(void) { reset_stack(); }

void vm_free(void) {}

InterpretResult vm_interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = chunk->code;
  return run();
}
