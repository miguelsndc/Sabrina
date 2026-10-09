#ifndef sabrina_vm_h
#define sabrina_vm_h

#include "chunk.h"
#include <stdint.h>

#define STACK_MAX 512

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value *stack_top;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void vm_init(void);
void vm_free(void);
void vm_st_push(Value);
Value vm_st_pop(void);
InterpretResult vm_interpret(Chunk *chunk);

#endif
