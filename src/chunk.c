#include <stdlib.h>
#include <stdint.h>
#include "chunk.h"
#include "memory.h"
#include "value.h"

void chunk_init(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
	value_array_init(&chunk->constants);
}

void chunk_write(Chunk *chunk, uint8_t byte) {
	if (chunk->capacity < chunk->count + 1) {
		int old_cap = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(old_cap);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_cap, chunk->capacity);
	}
	chunk->code[chunk->count] = byte;
	chunk->count++;
}

void chunk_free(Chunk *chunk) {
	value_array_free(&chunk->constants);
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	chunk_init(chunk);
}

int add_constant(Chunk *chunk, Value constant) {
	value_array_write(&chunk->constants, constant);
	return chunk->constants.count - 1;
}
