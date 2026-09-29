#include "chunk.h"
#include "debug.h"

int main(int argc, char *argv[]) {
  Chunk chunk;
  chunk_init(&chunk);

  int constant = add_constant(&chunk, 1.5);
  chunk_write(&chunk, OP_CONSTANT, 1);
  chunk_write(&chunk, constant, 1);
  chunk_write(&chunk, OP_RETURN, 1);
  disassemble_chunk(&chunk, "test chunk");
  chunk_free(&chunk);
}
