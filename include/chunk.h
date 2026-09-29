#ifndef sabrina_chunk_h
#define sabrina_chunk_h

#include "value.h"
#include <assert.h>
#include <stdint.h>

typedef enum { OP_RETURN, OP_CONSTANT } OpCode;

typedef struct {
  int number;
  int count;
} EncodedPair;

typedef struct {
  int count;
  int capacity;
  EncodedPair *buffer;
} LineEncoding;

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  ValueArray constants;
  LineEncoding lines;
} Chunk;

void chunk_init(Chunk *chunk);
void chunk_write(Chunk *chunk, uint8_t byte, int line);
void chunk_free(Chunk *chunk);
int chunk_get_line(Chunk *chunk, int idx);
int add_constant(Chunk *chunk, Value constant);

#endif
