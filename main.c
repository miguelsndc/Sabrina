#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(void) {
  vm_init();

  Chunk chunk;
  chunk_init(&chunk);

  int constant = add_constant(&chunk, 1.5);
  chunk_write(&chunk, OP_CONSTANT, 1);
  chunk_write(&chunk, constant, 1);
  chunk_write(&chunk, OP_NEGATE, 1);
  chunk_write(&chunk, OP_RETURN, 1);
  disassemble_chunk(&chunk, "test chunk");
  vm_interpret(&chunk);
  vm_free();
  chunk_free(&chunk);
}
