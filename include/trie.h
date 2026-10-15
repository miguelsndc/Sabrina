#ifndef sabrina_trie_h
#define sabrina_trie_h

#include "scanner.h"
#include <assert.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define MAX_NODES 1024

#define CHILD(node, c) ((node) * ALPHABET_SIZE + ((c) - 'a'))

typedef struct {
  int children[MAX_NODES * ALPHABET_SIZE];
  TokenType token[MAX_NODES];
  bool terminal[MAX_NODES];
  int count;
} Trie;

int trie_next(const Trie *trie, int node, char c);
bool trie_insert(Trie *trie, const char *str, TokenType type);
#endif
