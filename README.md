# Flex + Bison Compiler Project

This project is a small compiler design laboratory project built with:

- Flex for lexical analysis
- Bison for syntax analysis
- C for semantic analysis and the symbol table

It supports:

- variable declarations
- assignments
- arithmetic expressions
- `read(...)`
- `write(...)`
- basic semantic checking
- simple syntax error recovery

## Project Files

- `scanner.l` - Flex lexer specification
- `parser.y` - Bison parser specification
- `symtab.h` - symbol table declarations and data types
- `symtab.c` - symbol table implementation and semantic checks
- `main.c` - driver program that calls `yyparse()`

Generated files after build:

- `parser.tab.c`
- `parser.tab.h`
- `lex.yy.c`
- `compiler.exe` or `compiler`

## Features

### Lexical Analysis

The lexer recognizes:

- keywords: `load`, `set`, `num`, `real`, `bigreal`, `chr`, `logic`, `text`, `read`, `write`, `fx`, `chk`, `else_try`, `then`, `repeat`, `until`, `doing`, `skip`, `decide`, `when`, `otherwise`, `stop`
- identifiers
- integer literals
- floating-point literals
- string literals
- operators: `+ - * / = == != < > <= >=`
- punctuation: `; , ( ) { }`

It also:

- ignores whitespace
- supports single-line comments using `@@`
- supports multi-line comments using `@{ ... }@`
- reports invalid tokens with line numbers

### Syntax Analysis

The parser supports:

- declarations
- assignments
- arithmetic expressions
- read statements
- write statements
- blocks
- a few control-flow constructs

It also uses simple error recovery with the Bison `error` token so parsing can continue after common statement-level syntax errors.

### Semantic Analysis

The symbol table:

- stores variable names and declared types
- detects undeclared variables
- detects duplicate declarations
- checks assignments
- rejects invalid arithmetic such as text with numeric operands
- allows implicit numeric conversion:
  - `num -> real`
  - `num -> bigreal`
  - `real -> bigreal`

## Supported Statement Examples

### Declarations

```txt
num a;
real b;
bigreal x, y, z;
num count = 5;
real rate = 3.14;
load num total;
```

### Assignments

```txt
a = 5;
b = a + 3.2;
c = (a + b) * 2;
set a = 10;
```

### Input and Output

```txt
read(a);
write(a);
write(a + b);
write("hello");
```

## Build Instructions

Important:

- Run Bison first
- Run Flex second
- Compile with GCC last
- Do not run `flex` on `lex.yy.c`
- Always run `flex` on `scanner.l`

### Linux

Install tools first:

```bash
sudo apt update
sudo apt install flex bison gcc
```

Build:

```bash
bison -d -o parser.tab.c parser.y
flex -o lex.yy.c scanner.l
gcc -Wall -Wextra -o compiler parser.tab.c lex.yy.c symtab.c ast.c ir.c interpreter.c codegen.c optimize.c main.c -lfl
```

If your Flex installation works without `-lfl`, this may also work:

```bash
gcc -Wall -Wextra -o compiler parser.tab.c lex.yy.c symtab.c ast.c ir.c interpreter.c codegen.c optimize.c main.c
```

### Windows with MinGW or MSYS2

Make sure `flex`, `bison`, and `gcc` are available in your terminal.

Build:

```powershell
bison -d -o parser.tab.c parser.y
flex -o lex.yy.c scanner.l
gcc -Wall -Wextra -o compiler.exe parser.tab.c lex.yy.c symtab.c ast.c ir.c interpreter.c codegen.c optimize.c main.c
```

### Clean Rebuild

If generated files already exist and you want a fresh rebuild:

```powershell
Remove-Item parser.tab.c, parser.tab.h, lex.yy.c, compiler.exe -ErrorAction SilentlyContinue
bison -d -o parser.tab.c parser.y
flex -o lex.yy.c scanner.l
gcc -Wall -Wextra -o compiler.exe parser.tab.c lex.yy.c symtab.c ast.c ir.c interpreter.c codegen.c optimize.c main.c
```

## How To Run

### Run with an Input File

Windows:

```powershell
.\compiler.exe input.txt
```

Linux:

```bash
./compiler input.txt
```

### Run from Keyboard Input

Windows:

```powershell
.\compiler.exe
```

Then type the program and finish with `Ctrl+Z` then `Enter`.

Linux:

```bash
./compiler
```

Then type the program and finish with `Ctrl+D`.

## Example Input Program

```txt
num a = 5;
real b = 2.5;
bigreal c;

read(a);
b = a + 3.2;
c = (a + b) * 2;

write(a);
write(a + b);
write("done");
```

## Expected Output Style

For a valid program:

- `Starting parsing...`
- `Parsing completed successfully.`
- symbol table output

For semantic problems, messages may include:

- undeclared variable errors
- duplicate declaration errors
- invalid assignment errors
- implicit conversion notes

For syntax problems, messages may include:

- line number
- nearby token text
- recovery to the next semicolon when possible

For lexical problems, messages may include:

- line number
- invalid token text

## User Guide

### 1. Write a source program

Create a plain text file such as `input.txt`.

### 2. Follow the language style

Use semicolons at the end of statements:

```txt
num a = 5;
write(a);
```

### 3. Declare variables before using them

Correct:

```txt
num a;
a = 5;
```

Wrong:

```txt
a = 5;
```

### 4. Use compatible types

Allowed:

```txt
num a = 5;
real b;
b = a;
```

Not allowed:

```txt
num a;
text msg = "hello";
a = msg;
```

### 5. Use valid arithmetic

Allowed:

```txt
num a = 5;
real b = 2.5;
write((a + b) * 2);
```

Not allowed:

```txt
text msg = "hello";
write(msg + 1);
```

## Common Errors and Fixes

### Error: `parser.tab.h: No such file or directory`

Cause:

- You ran Flex before Bison

Fix:

```powershell
bison -d -o parser.tab.c parser.y
flex -o lex.yy.c scanner.l
```

### Error: many `bad character: #` messages from `scanner.l` or `lex.yy.c`

Cause:

- You ran `flex` on `lex.yy.c` instead of `scanner.l`

Wrong:

```powershell
flex lex.yy.c
```

Correct:

```powershell
flex -o lex.yy.c scanner.l
```

### Error: undeclared variable

Cause:

- variable used before declaration

Fix:

Declare it first:

```txt
num a;
a = 5;
```

### Error: duplicate declaration

Cause:

- same variable declared more than once

Fix:

Use a different name or remove the repeated declaration.

### Error: invalid assignment

Cause:

- incompatible types on the left and right side

Fix:

Use a compatible type or convert the design of the statement.

## Notes for Submission

This project is organized in a student-friendly way:

- lexer in `scanner.l`
- parser in `parser.y`
- semantic analysis in `symtab.c`
- project driver in `main.c`

It is suitable for demonstrating:

- lexical analysis
- parsing
- syntax error recovery
- symbol table usage
- simple semantic analysis
