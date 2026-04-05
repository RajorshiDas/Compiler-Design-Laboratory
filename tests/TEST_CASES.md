# Compiler Project Test Cases

This folder now targets the report-style language accepted by the upgraded compiler.

The suite includes:

- `#load mathLib.fx`
- `start() -> empty { ... }`
- declarations for `num`, `real`, `chr`, `logic`, and `text`
- arithmetic, modulus, `AND/OR/NOT/XOR`, and absolute value
- `read(...)` and multi-argument `write(...)`
- `chk / else_try / then`
- `repeat`, `until`, and `doing ... until`
- `decide / when / otherwise`
- user-defined functions with `-> returnType`
- recursive functions
- nested loops inside function bodies
- builtin math helpers like `power()` and `squart()`

## Valid Test Cases

### `valid_01_declarations.txt`
Focus:
- report-style declarations
- logic and char literals
- basic output

### `valid_02_assignments_expressions.txt`
Focus:
- arithmetic precedence
- modulus
- XOR
- absolute value

### `valid_03_read_write.txt`
Focus:
- `read(identifier)`
- multi-argument `write(...)`

### `valid_04_conditionals.txt`
Focus:
- `chk ... end chk`
- chained `else_try ... end else_try`
- `then ... end then`
- logical operators

### `valid_05_loops.txt`
Focus:
- `repeat(init, condition, update)`
- `until(condition)`
- `skip` and `stop`

### `valid_06_strings.txt`
Focus:
- text literals
- mixed string output in `write`

### `valid_07_functions.txt`
Focus:
- `fx name(...) -> type`
- `send expr;`
- builtin math helpers

### `valid_08_decide.txt`
Focus:
- `decide selector`
- `when(value) => ...`
- `otherwise => ...`

### `valid_09_scope_blocks.txt`
Focus:
- nested block scope
- variable shadowing

### `valid_10_full_program.txt`
Focus:
- integrated program with functions, loops, and decide

### `valid_11_recursion.txt`
Focus:
- self-recursive function calls
- base case and recursive case with `send`

### `valid_12_nested_loops_in_function.txt`
Focus:
- nested `repeat` loops inside a user-defined function
- function return after loop-based accumulation

## Build Command

```powershell
bison -d -o parser.tab.c parser.y
flex scanner.l
gcc -Wall -Wextra -o compiler.exe parser.tab.c lex.yy.c symtab.c ast.c ir.c interpreter.c codegen.c optimize.c main.c -lm
```

## Run One Test

```powershell
.\compiler.exe tests\valid_05_loops.txt
```

## Batch Run

```powershell
powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1
```
