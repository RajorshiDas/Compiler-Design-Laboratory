%{
/* C declarations */
#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"

int yylex(void);
void yyerror(const char *message);

extern int yylineno;
extern char *yytext;

static int semantic_errors = 0;
static SymbolType current_decl_type = TYPE_INVALID;

static int is_numeric_type(SymbolType type);
static SymbolType make_numeric_result(SymbolType left, SymbolType right, const char *op_text);
static SymbolType make_relational_result(SymbolType left, SymbolType right, const char *op_text);
static SymbolType require_declared_identifier(const char *name);
static int declare_identifier(const char *name, SymbolType type);
static void validate_assignment(const char *name, SymbolType value_type);
static void validate_logic_expression(SymbolType type, const char *context);
%}

%error-verbose

/* Semantic value definitions */
%union {
    int intval;
    float floatval;
    char *strval;
    int type;
    int expr_type;
}

/* Token declarations */
%token LOAD SET NUM_TYPE REAL_TYPE BIGREAL_TYPE CHR_TYPE LOGIC_TYPE TEXT_TYPE READ WRITE FX CHK ELSE_TRY THEN REPEAT UNTIL DOING SKIP DECIDE WHEN OTHERWISE STOP
%token PLUS MINUS STAR SLASH ASSIGN EQ NEQ LT GT LE GE
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE
%token <strval> ID STRING
%token <intval> INT_LITERAL
%token <floatval> FLOAT_LITERAL

/* Non-terminal type declarations */
%type <type> type_specifier
%type <expr_type> condition expression term factor

%left EQ NEQ LT GT LE GE
%left PLUS MINUS
%left STAR SLASH
%right UMINUS

%start program

%%

/* Program structure */
program
    : statement_list
      {
          if (semantic_errors == 0) {
              printf("Parsing completed successfully.\n");
          } else {
              printf("Parsing completed with %d semantic error(s).\n", semantic_errors);
          }
      }
    ;

statement_list
    : /* empty */
    | statement_list statement
    ;

/* Simple statement-level error recovery */
sync_semi
    : error SEMICOLON
      {
          yyerrok;
      }
    ;

/* Top-level statements */
statement
    : declaration
    | assignment_statement
    | read_statement
    | write_statement
    | function_definition
    | chk_statement
    | repeat_statement
    | decide_statement
    | block
    | SKIP SEMICOLON
    | STOP SEMICOLON
    | sync_semi
      {
          yyerror("invalid statement skipped");
      }
    ;

/* Blocks and function definitions */
block
    : LBRACE statement_list RBRACE
    ;

function_definition
    : FX ID LPAREN parameter_list_opt RPAREN block
      {
          free($2);
      }
    ;

/* Function parameters */
parameter_list_opt
    : /* empty */
    | parameter_list
    ;

parameter_list
    : parameter
    | parameter_list COMMA parameter
    ;

parameter
    : type_specifier ID
      {
          declare_identifier($2, (SymbolType)$1);
          free($2);
      }
    ;

/* Variable declarations */
declaration_head
    : type_specifier
      {
          current_decl_type = (SymbolType)$1;
      }
    ;

declaration
    : declaration_head id_list SEMICOLON
    | LOAD declaration_head id_list SEMICOLON
    | declaration_head sync_semi
      {
          yyerror("invalid declaration");
      }
    | LOAD declaration_head sync_semi
      {
          yyerror("invalid declaration");
      }
    ;

id_list
    : id_item
    | id_list COMMA id_item
    ;

id_item
    : ID
      {
          declare_identifier($1, current_decl_type);
          free($1);
      }
    | ID ASSIGN expression
      {
          if (declare_identifier($1, current_decl_type)) {
              validate_assignment($1, (SymbolType)$3);
          }
          free($1);
      }
    ;

/* Assignment and I/O statements */
assignment_statement
    : ID ASSIGN expression SEMICOLON
      {
          validate_assignment($1, (SymbolType)$3);
          free($1);
      }
    | SET ID ASSIGN expression SEMICOLON
      {
          validate_assignment($2, (SymbolType)$4);
          free($2);
      }
    | ID ASSIGN sync_semi
      {
          yyerror("invalid assignment expression");
          free($1);
      }
    | SET ID ASSIGN sync_semi
      {
          yyerror("invalid assignment expression");
          free($2);
      }
    ;

read_statement
    : READ LPAREN ID RPAREN SEMICOLON
      {
          require_declared_identifier($3);
          free($3);
      }
    | READ LPAREN error RPAREN SEMICOLON
      {
          yyerror("invalid read statement");
          yyerrok;
      }
    ;

write_statement
    : WRITE LPAREN expression RPAREN SEMICOLON
      {
          (void)$3;
      }
    | WRITE LPAREN error RPAREN SEMICOLON
      {
          yyerror("invalid write statement");
          yyerrok;
      }
    ;

/* Control-flow statements */
chk_statement
    : CHK LPAREN condition RPAREN THEN block else_part
      {
          validate_logic_expression((SymbolType)$3, "chk");
      }
    ;

else_part
    : /* empty */
    | ELSE_TRY block
    ;

repeat_statement
    : REPEAT DOING block UNTIL LPAREN condition RPAREN SEMICOLON
      {
          validate_logic_expression((SymbolType)$6, "repeat-until");
      }
    ;

decide_statement
    : DECIDE LPAREN expression RPAREN LBRACE when_clause_list otherwise_clause_opt RBRACE
    ;

when_clause_list
    : when_clause
    | when_clause_list when_clause
    ;

when_clause
    : WHEN condition THEN block
      {
          validate_logic_expression((SymbolType)$2, "when");
      }
    ;

otherwise_clause_opt
    : /* empty */
    | OTHERWISE THEN block
    ;

/* Expressions and type inference */
condition
    : expression
      {
          $$ = $1;
      }
    | expression EQ expression
      {
          $$ = make_relational_result((SymbolType)$1, (SymbolType)$3, "==");
      }
    | expression NEQ expression
      {
          $$ = make_relational_result((SymbolType)$1, (SymbolType)$3, "!=");
      }
    | expression LT expression
      {
          $$ = make_relational_result((SymbolType)$1, (SymbolType)$3, "<");
      }
    | expression GT expression
      {
          $$ = make_relational_result((SymbolType)$1, (SymbolType)$3, ">");
      }
    | expression LE expression
      {
          $$ = make_relational_result((SymbolType)$1, (SymbolType)$3, "<=");
      }
    | expression GE expression
      {
          $$ = make_relational_result((SymbolType)$1, (SymbolType)$3, ">=");
      }
    ;

expression
    : expression PLUS term
      {
          $$ = make_numeric_result((SymbolType)$1, (SymbolType)$3, "+");
      }
    | expression MINUS term
      {
          $$ = make_numeric_result((SymbolType)$1, (SymbolType)$3, "-");
      }
    | term
      {
          $$ = $1;
      }
    ;

term
    : term STAR factor
      {
          $$ = make_numeric_result((SymbolType)$1, (SymbolType)$3, "*");
      }
    | term SLASH factor
      {
          $$ = make_numeric_result((SymbolType)$1, (SymbolType)$3, "/");
      }
    | factor
      {
          $$ = $1;
      }
    ;

factor
    : ID
      {
          $$ = require_declared_identifier($1);
          free($1);
      }
    | INT_LITERAL
      {
          $$ = TYPE_NUM;
      }
    | FLOAT_LITERAL
      {
          $$ = TYPE_REAL;
      }
    | STRING
      {
          $$ = TYPE_TEXT;
          free($1);
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
      }
    | MINUS factor %prec UMINUS
      {
          if (!is_numeric_type((SymbolType)$2)) {
              fprintf(stderr, "Semantic error at line %d: unary '-' requires a numeric operand.\n", yylineno);
              semantic_errors++;
              $$ = TYPE_INVALID;
          } else {
              $$ = $2;
          }
      }
    ;

/* Type names */
type_specifier
    : NUM_TYPE
      {
          $$ = TYPE_NUM;
      }
    | REAL_TYPE
      {
          $$ = TYPE_REAL;
      }
    | BIGREAL_TYPE
      {
          $$ = TYPE_BIGREAL;
      }
    | CHR_TYPE
      {
          $$ = TYPE_CHR;
      }
    | LOGIC_TYPE
      {
          $$ = TYPE_LOGIC;
      }
    | TEXT_TYPE
      {
          $$ = TYPE_TEXT;
      }
    ;

%%

/* Helper functions */
static int is_numeric_type(SymbolType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static SymbolType make_numeric_result(SymbolType left, SymbolType right, const char *op_text) {
    SymbolType combined_type;

    (void)op_text;

    if (left == TYPE_INVALID || right == TYPE_INVALID) {
        return TYPE_INVALID;
    }

    combined_type = result_type(left, right);
    if (combined_type == TYPE_INVALID) {
        semantic_errors++;
    }

    return combined_type;
}

static SymbolType make_relational_result(SymbolType left, SymbolType right, const char *op_text) {
    if (left == TYPE_INVALID || right == TYPE_INVALID) {
        return TYPE_INVALID;
    }

    if ((is_numeric_type(left) && is_numeric_type(right)) || left == right) {
        return TYPE_LOGIC;
    }

    fprintf(stderr,
            "Semantic error at line %d: operator '%s' cannot compare %s with %s.\n",
            yylineno,
            op_text,
            symbol_type_name(left),
            symbol_type_name(right));
    semantic_errors++;
    return TYPE_INVALID;
}

static SymbolType require_declared_identifier(const char *name) {
    SymbolType type = get_type(name);

    if (type == TYPE_INVALID) {
        semantic_errors++;
    }

    return type;
}

static int declare_identifier(const char *name, SymbolType type) {
    if (!insert_symbol(name, type)) {
        semantic_errors++;
        return 0;
    }

    return 1;
}

static void validate_assignment(const char *name, SymbolType value_type) {
    if (value_type == TYPE_INVALID) {
        return;
    }

    if (!check_assignment(name, value_type)) {
        semantic_errors++;
    }
}

static void validate_logic_expression(SymbolType type, const char *context) {
    if (type == TYPE_INVALID) {
        return;
    }

    if (type != TYPE_LOGIC) {
        fprintf(stderr,
                "Semantic error at line %d: %s requires a logic expression, but found %s.\n",
                yylineno,
                context,
                symbol_type_name(type));
        semantic_errors++;
    }
}

void yyerror(const char *message) {
    if (yytext != NULL && yytext[0] != '\0') {
        fprintf(stderr,
                "Syntax error at line %d near '%s': %s\n",
                yylineno,
                yytext,
                message);
    } else {
        fprintf(stderr,
                "Syntax error at line %d: %s\n",
                yylineno,
                message);
    }
}
