#include "trie.h"

int trie_next(const Trie *trie, int node, char c) {
  if (node < 0 || node >= trie->count || c < 'a' || c > 'z')
    return 0;

  return trie->children[CHILD(node, c)];
}

bool trie_insert(Trie *trie, const char *str, TokenType type) {
  int node = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    char c = str[i];

    if (c < 'a' || c > 'z')
      return false;

    int pos = CHILD(node, c);
    int next = trie->children[pos];

    if (next == 0) {
      assert(trie->count < MAX_NODES);
      next = trie->count++;
      trie->children[pos] = next;
    }

    node = next;
  }

  trie->token[node] = type;
  trie->terminal[node] = true;

  return true;
}
