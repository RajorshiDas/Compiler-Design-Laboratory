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

### `t01_decl.txt`
Focus:
- report-style declarations
- logic and char literals
- basic output

### `t02_expr.txt`
Focus:
- arithmetic precedence
- modulus
- XOR
- absolute value

### `t03_io.txt`
Focus:
- `read(identifier)`
- multi-argument `write(...)`

### `t04_cond.txt`
Focus:
- `chk ... end chk`
- chained `else_try ... end else_try`
- `then ... end then`
- logical operators

### `t05_loops.txt`
Focus:
- `repeat(init, condition, update)`
- `until(condition)`
- `skip` and `stop`

### `t06_text.txt`
Focus:
- text literals
- mixed string output in `write`

### `t07_funcs.txt`
Focus:
- `fx name(...) -> type`
- `send expr;`
- builtin math helpers

### `t08_decide.txt`
Focus:
- `decide selector`
- `when(value) => ...`
- `otherwise => ...`

### `t09_scope.txt`
Focus:
- nested block scope
- variable shadowing

### `t10_full.txt`
Focus:
- integrated program with functions, loops, and decide

### `t11_rec.txt`
Focus:
- self-recursive function calls
- base case and recursive case with `send`

### `t12_nested.txt`
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
.\compiler.exe tests\t05_loops.txt
```

## Batch Run

```powershell
powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1
```

