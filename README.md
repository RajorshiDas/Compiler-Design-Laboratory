# Simple Flex Lexer (Keywords, Integers, Ignored Comments)

This project provides a Flex lexer that:
- Prints `key(yytext)` for `if`, `else`, `return`.
- Prints `INT(yytext)` for `[0-9]+`.
- Ignores single-line (`// ...`) and multi-line (`/* ... */`) comments using exclusive states.
- Ignores other identifiers, symbols, and whitespace.

## Files
- scanner.l — Flex lexer specification
- main.c — C driver that reads from terminal if no filename is provided, else reads from file

## Build (Windows)
Requires Flex and a C compiler (e.g., MinGW GCC). After installing, run:

```
flex -o scanner.c scanner.l
gcc -o lexer.exe scanner.c main.c
```

## Run
- Read from terminal:
```
./lexer.exe
```
Type input and end with `Ctrl+Z` then `Enter`.

- Read from file:
```
./lexer.exe input.txt
```

## Example Input
```
if else return 123
// single line comment
/* multi
   line comment */
456 foo bar
```

## Example Output
```
key(if)
key(else)
key(return)
INT(123)
INT(456)
```
