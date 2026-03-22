# Compiler Project Test Cases

This folder contains simple test programs for demonstrating:

- lexical analysis
- syntax analysis
- semantic analysis

## Valid Test Cases

### `valid_01_declarations.txt`
Focus:
- variable declarations
- comma-separated declarations
- initialized declarations

Expected behavior:
- parsing succeeds
- symbol table contains all declared variables
- no semantic errors

### `valid_02_assignments_expressions.txt`
Focus:
- assignments
- arithmetic expressions
- parentheses
- implicit numeric conversion

Expected behavior:
- parsing succeeds
- one semantic note may appear for implicit conversion such as `real -> bigreal`
- no semantic errors

### `valid_03_read_write.txt`
Focus:
- `read(identifier);`
- `write(identifier);`
- `write(expression);`
- `write("string");`

Expected behavior:
- parsing succeeds
- declared identifiers are accepted in `read`
- expression types are computed for `write`
- no semantic errors

## Invalid Test Cases

### `invalid_01_undeclared_variable.txt`
Focus:
- use of undeclared variables

Expected behavior:
- semantic errors for undeclared identifiers

### `invalid_02_duplicate_declaration.txt`
Focus:
- duplicate declarations

Expected behavior:
- semantic error reporting duplicate declaration

### `invalid_03_invalid_assignment.txt`
Focus:
- invalid type assignment
- invalid arithmetic involving text

Expected behavior:
- semantic errors for type mismatch
- semantic error for invalid arithmetic

### `invalid_04_syntax_error.txt`
Focus:
- missing operands
- malformed statements

Expected behavior:
- syntax errors with line number
- parser attempts recovery and continues when possible

### `invalid_05_invalid_token.txt`
Focus:
- invalid characters not recognized by the lexer

Expected behavior:
- lexical error with line number and token text
- parser may also report syntax errors after the invalid token

## Suggested Run Commands

Build:

```bash
bison -d -o parser.tab.c parser.y
flex scanner.l
gcc -Wall -Wextra -o parser.exe parser.tab.c lex.yy.c symtab.c main.c
```

Run one test:

```bash
./parser.exe tests/valid_01_declarations.txt
```

Run another test:

```bash
./parser.exe tests/invalid_03_invalid_assignment.txt
```
