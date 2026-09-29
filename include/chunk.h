#ifndef sabrina_chunk_h
#define sabrina_chunk_h

#include <stdint.h>
#include "value.h"

typedef enum {
    OP_RETURN,
    OP_CONSTANT
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    ValueArray constants;
} Chunk;

void chunk_init(Chunk* chunk);
void chunk_write(Chunk* chunk, uint8_t byte);
void chunk_free(Chunk *chunk);
int add_constant(Chunk *chunk, Value constant);

#endif
