%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-label"
#endif

static char *copy_lexeme(void) {
    size_t length = strlen(yytext);
    char *text = (char *)malloc(length + 1);

    if (text == NULL) {
        fprintf(stderr, "Out of memory while copying token text.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(text, yytext);
    return text;
}
%}

%option noyywrap
%option yylineno
%option nounput
%option noinput

%x SCOMMENT MCOMMENT

DIGIT               [0-9]
LETTER              [A-Za-z_]
IDENTIFIER_PATTERN  {LETTER}({LETTER}|{DIGIT})*
INTEGER_PATTERN     {DIGIT}+
FLOAT_PATTERN       {DIGIT}+"."{DIGIT}+
STRING_PATTERN      \"([^\\\"\n]|\\.)*\"
CHAR_PATTERN        \'([^\\\n]|\\.)\'

%%

"@@"                    { BEGIN(SCOMMENT); }
"@{"                    { BEGIN(MCOMMENT); }

<SCOMMENT>[^\n]*        { }
<SCOMMENT>\n            { BEGIN(INITIAL); }
<SCOMMENT><<EOF>>       { BEGIN(INITIAL); return 0; }

<MCOMMENT>"}@"          { BEGIN(INITIAL); }
<MCOMMENT>\n            { }
<MCOMMENT>.             { }
<MCOMMENT><<EOF>>       {
                            fprintf(stderr, "Lexical error at line %d: unterminated multi-line comment\n", yylineno);
                            return 0;
                        }

[ \t\r\n]+              { }

"#load"[ \t]+{IDENTIFIER_PATTERN}"."{IDENTIFIER_PATTERN} {
                            yylval.strval = copy_lexeme();
                            return INCLUDE_DIRECTIVE;
                        }

"start"                 { return START; }
"fx"                    { return FX; }
"send"                  { return SEND; }
"empty"                 { return EMPTY; }
"num"                   { return NUM_TYPE; }
"real"                  { return REAL_TYPE; }
"bigreal"               { return BIGREAL_TYPE; }
"chr"                   { return CHR_TYPE; }
"logic"                 { return LOGIC_TYPE; }
"text"                  { return TEXT_TYPE; }
"read"                  { return READ; }
"write"                 { return WRITE; }
"chk"                   { return CHK; }
"else_try"              { return ELSE_TRY; }
"then"                  { return THEN; }
"end"                   { return END; }
"repeat"                { return REPEAT; }
"until"                 { return UNTIL; }
"doing"                 { return DOING; }
"skip"                  { return SKIP; }
"stop"                  { return STOP; }
"decide"                { return DECIDE; }
"when"                  { return WHEN; }
"otherwise"             { return OTHERWISE; }
"true"                  { return TRUE_LITERAL; }
"false"                 { return FALSE_LITERAL; }
"accept"                { return TRUE_LITERAL; }
"reject"                { return FALSE_LITERAL; }
"AND"                   { return AND; }
"OR"                    { return OR; }
"NOT"                   { return NOT; }
"XOR"                   { return XOR; }
"and"                   { return AND; }
"or"                    { return OR; }
"not"                   { return NOT; }
"xor"                   { return XOR; }

"=="                    { return EQ; }
"!="                    { return NEQ; }
"<="                    { return LE; }
">="                    { return GE; }
"->"                    { return ARROW; }
"=>"                    { return FAT_ARROW; }
"="                     { return ASSIGN; }
"<"                     { return LT; }
">"                     { return GT; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return STAR; }
"/"                     { return SLASH; }
"%"                     { return MOD; }
"|"                     { return PIPE; }

";"                     { return SEMICOLON; }
","                     { return COMMA; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }

{FLOAT_PATTERN}         {
                            yylval.floatval = (float)atof(yytext);
                            return FLOAT_LITERAL;
                        }

{INTEGER_PATTERN}       {
                            yylval.intval = atoi(yytext);
                            return INT_LITERAL;
                        }

{STRING_PATTERN}        {
                            yylval.strval = copy_lexeme();
                            return STRING;
                        }

{CHAR_PATTERN}          {
                            yylval.strval = copy_lexeme();
                            return CHAR_LITERAL;
                        }

{IDENTIFIER_PATTERN}    {
                            yylval.strval = copy_lexeme();
                            return ID;
                        }

.                       {
                            fprintf(stderr,
                                    "Lexical error at line %d: invalid token \"%s\" skipped\n",
                                    yylineno,
                                    yytext);
                        }

%%
