#include "scanner.h"
#include "trie.h"
#include <stdbool.h>
#include <string.h>

Scanner scanner;
Trie trie = {.count = 1};

static bool is_at_end(void) { return *scanner.current == '\0'; }

static Token make_token(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

static Token error_token(const char *message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;
  return token;
}

static char advance(void) {
  char c = *scanner.current;
  scanner.current++;
  return c;
}

static bool match(char expected) {
  if (is_at_end())
    return false;
  if (*scanner.current != expected)
    return false;
  scanner.current++;
  return true;
}

static char peek(void) { return *scanner.current; }

static char peek_next(void) {
  if (is_at_end())
    return '\0';
  return scanner.current[1];
}

static void skip_whitespace(void) {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      scanner.line++;
      advance();
      break;
    case '\\':
      if (peek_next() == '\\') {
        while (peek() != '\n' && !is_at_end())
          advance();
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

static Token string(void) {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n')
      scanner.line++;
    advance();
  }
  if (is_at_end())
    return error_token("Unterminated string");
  advance();
  return make_token(TOKEN_STRING);
}

static bool is_digit(char c) { return c >= '0' && c <= '9'; }

static Token number(void) {
  while (is_digit(peek()))
    advance();
  if (peek() == '.' && is_digit(peek_next())) {
    advance();
    while (is_digit(peek()))
      advance();
  }
  return make_token(TOKEN_NUMBER);
}

static bool is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static TokenType identifier_type(void) {
  int node = 0;
  for (const char *p = scanner.start; p < scanner.current; p++) {
    node = trie_next(&trie, node, *p);
    if (node == 0) {
      return TOKEN_IDENTIFIER;
    }
  }
  if (trie.terminal[node]) {
    return trie.token[node];
  }
  return TOKEN_IDENTIFIER;
}

static Token identifier(void) {
  while (is_alpha(peek()) || is_digit(peek()))
    advance();
  return make_token(identifier_type());
}

void scanner_init(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;

  trie_insert(&trie, "and", TOKEN_AND);
  trie_insert(&trie, "class", TOKEN_CLASS);
  trie_insert(&trie, "else", TOKEN_ELSE);
  trie_insert(&trie, "false", TOKEN_FALSE);
  trie_insert(&trie, "for", TOKEN_FOR);
  trie_insert(&trie, "fun", TOKEN_FUN);
  trie_insert(&trie, "if", TOKEN_IF);
  trie_insert(&trie, "nil", TOKEN_NIL);
  trie_insert(&trie, "or", TOKEN_OR);
  trie_insert(&trie, "print", TOKEN_PRINT);
  trie_insert(&trie, "return", TOKEN_RETURN);
  trie_insert(&trie, "super", TOKEN_SUPER);
  trie_insert(&trie, "this", TOKEN_THIS);
  trie_insert(&trie, "true", TOKEN_TRUE);
  trie_insert(&trie, "var", TOKEN_VAR);
  trie_insert(&trie, "while", TOKEN_WHILE);
}

Token scanner_get_token(void) {
  skip_whitespace();
  scanner.start = scanner.current;
  if (is_at_end())
    return make_token(TOKEN_EOF);

  char c = advance();

  if (is_digit(c))
    return number();
  if (is_alpha(c))
    return identifier();

  switch (c) {
  case '(':
    return make_token(TOKEN_LEFT_PAREN);
  case ')':
    return make_token(TOKEN_RIGHT_PAREN);
  case '{':
    return make_token(TOKEN_LEFT_BRACE);
  case '}':
    return make_token(TOKEN_RIGHT_BRACE);
  case ';':
    return make_token(TOKEN_SEMICOLON);
  case ',':
    return make_token(TOKEN_COMMA);
  case '.':
    return make_token(TOKEN_DOT);
  case '-':
    return make_token(TOKEN_MINUS);
  case '+':
    return make_token(TOKEN_PLUS);
  case '/':
    return make_token(TOKEN_SLASH);
  case '*':
    return make_token(TOKEN_STAR);
  case '!':
    return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  case '"':
    return string();
  }
  return error_token("Unexpected character. ");
}
