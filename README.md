# SabrinaC

SabrinaC is a bytecode-interpreted programming language written in C and based
on the `clox` interpreter from
[Crafting Interpreters](https://craftinginterpreters.com/).

The language uses complete Sabrina Carpenter lyric fragments as keywords. It
is a joke language on the surface, but the project is mainly an exercise in
understanding scanners, compilers, bytecode virtual machines and memory
management.

The project is currently under development.

## Syntax

Some of the planned keywords are:

| Phrase | Meaning |
| --- | --- |
| `AND I GOT THIS ONE BOY` | variable declaration |
| `THATS THAT` | assignment |
| `IS IT THAT SWEET` | equality |
| `WHEN THEY ACT THIS WAY` | conditional |
| `IM WORKING LATE CAUSE IM A SINGER` | function declaration |
| `I DREAM-CAME-TRUED IT FOR YA` | return |
| `SAY` | print |

Because keywords can contain several words, the scanner uses longest-match
recognition. It keeps reading while a phrase may still form a keyword and emits
the longest complete match it found. The parser and VM only receive regular
token types, so the unusual syntax remains isolated inside the scanner.

```text
AND I GOT THIS ONE BOY answer THATS THAT 6 SO OFTEN 7;
SAY answer;
```

## Current state

The runtime currently includes:

- growable bytecode chunks;
- a constant pool;
- compressed source-line information;
- memory helpers for dynamic arrays;
- bytecode disassembly;
- the initial value and VM structures.

## Roadmap

- Finish the scanner and parser.
- Compile expressions, variables and control flow to bytecode.
- Add functions and closures.
- Add strings, objects and hash tables.
- Implement mark-and-sweep garbage collection.
- Add tests and example programs.

## Build

```bash
make
./sabrina
```
