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
- builtin math helpers like `power()` and `squart()`
- semantic, syntax, lexical, and runtime error cases

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

## Invalid / Error Test Cases

### `invalid_01_undeclared_variable.txt`
Focus:
- undeclared identifier use

### `invalid_02_duplicate_declaration.txt`
Focus:
- duplicate declaration in one scope

### `invalid_03_invalid_assignment.txt`
Focus:
- incompatible assignment and invalid arithmetic

### `invalid_04_syntax_error.txt`
Focus:
- malformed `repeat(...)`

### `invalid_05_invalid_token.txt`
Focus:
- lexical rejection of unsupported symbols

### `invalid_06_division_by_zero.txt`
Focus:
- runtime division-by-zero detection

### `invalid_07_uninitialized_variable.txt`
Focus:
- non-logic expression inside `chk`

### `invalid_08_wrong_function_arguments.txt`
Focus:
- wrong function argument count

### `invalid_09_return_outside_function.txt`
Focus:
- `skip` used outside a loop

### `invalid_10_function_type_mismatch.txt`
Focus:
- function declared return type mismatch

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
