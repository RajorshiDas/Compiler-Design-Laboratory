%{
#include <stdio.h>
int token_count = 0;
%}

%x SCOMMENT MCOMMENT

%%

"#load"            { printf("key(%s)\n", yytext); token_count++; }
"#set"             { printf("key(%s)\n", yytext); token_count++; }
"num"              { printf("key(%s)\n", yytext); token_count++; }
"real"             { printf("key(%s)\n", yytext); token_count++; }
"bigreal"          { printf("key(%s)\n", yytext); token_count++; }
ln\ num            { printf("key(%s)\n", yytext); token_count++; }
"chr"              { printf("key(%s)\n", yytext); token_count++; }
"logic"            { printf("key(%s)\n", yytext); token_count++; }
"empty"            { printf("key(%s)\n", yytext); token_count++; }
"stop"             { printf("key(%s)\n", yytext); token_count++; }
"read"             { printf("key(%s)\n", yytext); token_count++; }
"write"            { printf("key(%s)\n", yytext); token_count++; }
"fx"               { printf("key(%s)\n", yytext); token_count++; }
"chk"              { printf("key(%s)\n", yytext); token_count++; }
end\ chk           { printf("key(%s)\n", yytext); token_count++; }
"else_try"         { printf("key(%s)\n", yytext); token_count++; }
end\ else_try      { printf("key(%s)\n", yytext); token_count++; }
"then"             { printf("key(%s)\n", yytext); token_count++; }
end\ then          { printf("key(%s)\n", yytext); token_count++; }
"repeat"           { printf("key(%s)\n", yytext); token_count++; }
"until"            { printf("key(%s)\n", yytext); token_count++; }
"doing"            { printf("key(%s)\n", yytext); token_count++; }
"skip"             { printf("key(%s)\n", yytext); token_count++; }
"decide"           { printf("key(%s)\n", yytext); token_count++; }
"when"             { printf("key(%s)\n", yytext); token_count++; }
"otherwise"        { printf("key(%s)\n", yytext); token_count++; }
"AND"              { printf("key(%s)\n", yytext); token_count++; }
"OR"               { printf("key(%s)\n", yytext); token_count++; }
"NOT"              { printf("key(%s)\n", yytext); token_count++; }
"XOR"              { printf("key(%s)\n", yytext); token_count++; }
"power"            { printf("key(%s)\n", yytext); token_count++; }
"squart"           { printf("key(%s)\n", yytext); token_count++; }
"upper"            { printf("key(%s)\n", yytext); token_count++; }
"lower"            { printf("key(%s)\n", yytext); token_count++; }
"log"              { printf("key(%s)\n", yytext); token_count++; }
"sin"              { printf("key(%s)\n", yytext); token_count++; }
"cos"              { printf("key(%s)\n", yytext); token_count++; }
"tan"              { printf("key(%s)\n", yytext); token_count++; }
"asin"             { printf("key(%s)\n", yytext); token_count++; }
"acos"             { printf("key(%s)\n", yytext); token_count++; }
"atan"             { printf("key(%s)\n", yytext); token_count++; }
"send"             { printf("key(%s)\n", yytext); token_count++; }
"start"            { printf("key(%s)\n", yytext); token_count++; }
"text"             { printf("key(%s)\n", yytext); token_count++; }
"accept"           { printf("key(%s)\n", yytext); token_count++; }
"reject"           { printf("key(%s)\n", yytext); token_count++; }
"end"              { printf("key(%s)\n", yytext); token_count++; }

\"[^\"]*\"         { printf("STRING(%s)\n", yytext); token_count++; }

[0-9]+\.[0-9]+     { printf("FLOAT(%s)\n", yytext); token_count++; }
[0-9]+             { printf("INT(%s)\n", yytext); token_count++; }

"@@"               { BEGIN(SCOMMENT); printf("COMMENT\n"); token_count++; }

"@{"               { BEGIN(MCOMMENT); printf("COMMENT\n"); token_count++; }

[ \t\r\n]+         { }

[A-Za-z_][A-Za-z0-9_]*  { printf("VAR(%s)\n", yytext); token_count++; }
.                  { }

<SCOMMENT>[^\n]*   { }
<SCOMMENT>\n       { BEGIN(INITIAL); }
<SCOMMENT><<EOF>>  { BEGIN(INITIAL); }

<MCOMMENT>"}@"     { BEGIN(INITIAL); }
<MCOMMENT>.        { }
<MCOMMENT>\n       { }
<MCOMMENT><<EOF>>  { BEGIN(INITIAL); }

%%

int yywrap() {
    printf("\nTotal tokens: %d\n", token_count);
    return 1;
}
