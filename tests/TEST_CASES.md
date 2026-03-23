# Compiler Project Test Cases

This folder now covers the interpreter features as well as parsing and semantic checking.

The suite includes:

- declarations and assignments
- arithmetic expressions
- `read(...)` and `write(...)`
- strings
- `chk ... then ... else_try`
- `repeat doing ... until`
- `decide / when / otherwise`
- block scope
- function definitions, calls, and returns
- semantic, syntax, lexical, and runtime error cases

## Valid Test Cases

### `valid_01_declarations.txt`
Focus:
- variable declarations
- comma-separated declarations
- initialized declarations

### `valid_02_assignments_expressions.txt`
Focus:
- arithmetic execution
- assignment execution
- implicit numeric conversion

### `valid_03_read_write.txt`
Focus:
- `read(identifier);`
- `write(identifier);`
- `write(expression);`
- `write("string");`

Note:
- if no runtime input is provided, the sample still runs using the initial value of `a`

### `valid_04_conditionals.txt`
Focus:
- `chk (...) then { ... } else_try { ... }`
- relational evaluation
- branch execution

### `valid_05_loops.txt`
Focus:
- `repeat doing { ... } until (...)`
- loop body execution
- accumulating values across iterations

### `valid_06_strings.txt`
Focus:
- text variable initialization
- text variable output
- direct string literal output

### `valid_07_functions.txt`
Focus:
- `fx` function definitions
- parameter passing
- `stop expr;` return values
- using function calls inside assignments

### `valid_08_decide.txt`
Focus:
- `decide (...) { when ... otherwise ... }`
- first matching `when` branch execution

### `valid_09_scope_blocks.txt`
Focus:
- nested block scopes
- shadowed variables

### `valid_10_full_program.txt`
Focus:
- mixed execution in one file
- functions + loops + conditionals + decide

## Invalid / Error Test Cases

### `invalid_01_undeclared_variable.txt`
Focus:
- use of undeclared identifiers

### `invalid_02_duplicate_declaration.txt`
Focus:
- duplicate declarations in the same scope

### `invalid_03_invalid_assignment.txt`
Focus:
- invalid assignment types
- invalid arithmetic involving text

### `invalid_04_syntax_error.txt`
Focus:
- malformed statements
- parser recovery

### `invalid_05_invalid_token.txt`
Focus:
- lexer rejection of invalid characters

### `invalid_06_division_by_zero.txt`
Focus:
- runtime division-by-zero detection

### `invalid_07_uninitialized_variable.txt`
Focus:
- runtime use of uninitialized variables

### `invalid_08_wrong_function_arguments.txt`
Focus:
- semantic check for wrong function argument count

### `invalid_09_return_outside_function.txt`
Focus:
- semantic rejection of `stop expr;` outside a function

### `invalid_10_function_type_mismatch.txt`
Focus:
- semantic rejection of assigning a function's returned text value to a numeric variable

## Build Command

```powershell
bison -d -o parser.tab.c parser.y
flex scanner.l
gcc -Wall -Wextra -o compiler.exe parser.tab.c lex.yy.c symtab.c ast.c interpreter.c main.c
```

## Run One Test

```powershell
.\compiler.exe tests\valid_05_loops.txt
```

## Suggested Run Order

1. `valid_01_declarations.txt`
2. `valid_02_assignments_expressions.txt`
3. `valid_04_conditionals.txt`
4. `valid_05_loops.txt`
5. `valid_06_strings.txt`
6. `valid_07_functions.txt`
7. `valid_08_decide.txt`
8. `valid_10_full_program.txt`

## Quick Batch Run

```powershell
Get-ChildItem tests\valid_*.txt | ForEach-Object {
    Write-Host "`n=== $($_.Name) ==="
    .\compiler.exe $_.FullName
}
```
