#include "chunk.h"
#include "memory.h"
#include "value.h"
#include <stdint.h>
#include <stdlib.h>

void chunk_init(Chunk *chunk) {
  chunk->lines.capacity = 0;
  chunk->lines.count = 0;
  chunk->lines.buffer = NULL;
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  value_array_init(&chunk->constants);
}

int chunk_get_line(Chunk *chunk, int idx) {
  assert(idx >= 0 && idx < chunk->count);
  for (int i = 0; i < chunk->lines.count; i++) {
    if (idx < chunk->lines.buffer[i].count) {
      return chunk->lines.buffer[i].number;
    }
    idx -= chunk->lines.buffer[i].count;
  }
  assert(false);
}

void chunk_write(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int old_cap = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(old_cap);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_cap, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->count++;

  LineEncoding *lines = &chunk->lines;

  if (lines->capacity == 0) {
    lines->capacity = GROW_CAPACITY(0);
    lines->buffer = GROW_ARRAY(EncodedPair, lines->buffer, 0, lines->capacity);
  }

  if (lines->count == 0) {
    lines->buffer[0].number = line;
    lines->buffer[0].count = 1;
    lines->count++;
  } else if (lines->buffer[lines->count - 1].number == line) {
    lines->buffer[lines->count - 1].count++;
  } else {
    if (lines->capacity < lines->count + 1) {
      int old_cap = lines->capacity;
      lines->capacity = GROW_CAPACITY(old_cap);
      lines->buffer =
          GROW_ARRAY(EncodedPair, lines->buffer, old_cap, lines->capacity);
    }

    lines->buffer[lines->count].count = 1;
    lines->buffer[lines->count].number = line;
    lines->count++;
  }
}

void chunk_free(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(EncodedPair, chunk->lines.buffer, chunk->lines.capacity);
  value_array_free(&chunk->constants);
  chunk_init(chunk);
}

int add_constant(Chunk *chunk, Value constant) {
  value_array_write(&chunk->constants, constant);
  return chunk->constants.count - 1;
}
