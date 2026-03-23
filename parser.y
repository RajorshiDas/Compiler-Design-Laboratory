%code requires {
#include "ast.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

int yylex(void);
void yyerror(const char *message);

extern int yylineno;
extern char *yytext;

typedef struct FunctionSignature {
    char name[64];
    int param_count;
    SymbolType param_types[32];
    SymbolType return_type;
    struct FunctionSignature *next;
} FunctionSignature;

Program *parsed_program = NULL;

static int semantic_errors = 0;
static SymbolType current_decl_type = TYPE_INVALID;
static FunctionSignature *function_signatures = NULL;
static char *function_name_stack[64];
static SymbolType function_return_stack[64];
static int function_stack_top = 0;

static int is_numeric_type(SymbolType type);
static int is_assignment_compatible(SymbolType target_type, SymbolType value_type);
static ExprNode *make_numeric_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_relational_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_unary_minus_expr(ExprNode *operand);
static int require_declared_identifier(const char *name, SymbolType *out_type);
static int declare_identifier(const char *name, SymbolType type);
static int validate_assignment(const char *name, SymbolType value_type);
static void validate_logic_expression(SymbolType type, const char *context);
static FunctionSignature *find_function_signature(const char *name);
static SymbolType lookup_function_return_type(const char *name);
static void validate_function_call(const char *name, ExprList *arguments);
static void begin_function_definition(char *name, ParamNode *parameters);
static SymbolType finish_function_definition(ParamNode *parameters);
static void note_function_return(SymbolType type);

int get_semantic_error_count(void) {
    return semantic_errors;
}
%}

%error-verbose

%union {
    int intval;
    float floatval;
    char *strval;
    int type;
    ExprNode *expr;
    StmtNode *stmt;
    ParamNode *param;
    ExprList *arglist;
    CaseNode *caseclause;
}

%token LOAD SET NUM_TYPE REAL_TYPE BIGREAL_TYPE CHR_TYPE LOGIC_TYPE TEXT_TYPE READ WRITE FX CHK ELSE_TRY THEN REPEAT UNTIL DOING SKIP DECIDE WHEN OTHERWISE STOP RETURN
%token PLUS MINUS STAR SLASH ASSIGN EQ NEQ LT GT LE GE
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE
%token <strval> ID STRING
%token <intval> INT_LITERAL
%token <floatval> FLOAT_LITERAL

%type <type> type_specifier
%type <expr> condition expression term factor
%type <stmt> statement_list statement sync_semi declaration id_list id_item assignment_statement read_statement write_statement block chk_statement else_part repeat_statement decide_statement otherwise_clause_opt function_definition return_statement
%type <param> parameter_list_opt parameter_list parameter function_header
%type <arglist> argument_list_opt argument_list
%type <caseclause> when_clause_list when_clause

%destructor { free($$); } <strval>
%destructor { free_expr($$); } <expr>
%destructor { free_statement_list($$); } <stmt>
%destructor { free_param_list($$); } <param>
%destructor { free_expr_list($$); } <arglist>
%destructor { free_case_list($$); } <caseclause>

%left EQ NEQ LT GT LE GE
%left PLUS MINUS
%left STAR SLASH
%right UMINUS

%start program

%%

program
    : statement_list
      {
          parsed_program = create_program($1);
      }
    ;

statement_list
    : /* empty */
      {
          $$ = NULL;
      }
    | statement_list statement
      {
          $$ = append_statement($1, $2);
      }
    ;

sync_semi
    : error SEMICOLON
      {
          yyerror("recovering at statement terminator");
          yyerrok;
          $$ = NULL;
      }
    ;

statement
    : declaration
    | assignment_statement
    | read_statement
    | write_statement
    | function_definition
    | return_statement
    | chk_statement
    | repeat_statement
    | decide_statement
    | block
    | SKIP SEMICOLON
      {
          $$ = create_skip_stmt();
      }
    | STOP SEMICOLON
      {
          $$ = create_stop_stmt();
      }
    | STOP expression SEMICOLON
      {
          if (function_stack_top == 0) {
              fprintf(stderr, "Semantic error at line %d: 'stop <expr>;' is only valid inside a function.\n", yylineno);
              semantic_errors++;
          } else {
              note_function_return(($2)->value_type);
          }
          $$ = create_return_stmt($2);
      }
    | sync_semi
      {
          yyerror("invalid statement skipped");
          $$ = NULL;
      }
    ;

return_statement
    : RETURN expression SEMICOLON
      {
          if (function_stack_top == 0) {
              fprintf(stderr, "Semantic error at line %d: return is only valid inside a function.\n", yylineno);
              semantic_errors++;
          } else {
              note_function_return(($2)->value_type);
          }
          $$ = create_return_stmt($2);
      }
    ;

block_open
    : LBRACE
      {
          enter_scope();
      }
    ;

block
    : block_open statement_list RBRACE
      {
          leave_scope();
          $$ = create_block_stmt($2);
      }
    ;

function_header
    : FX ID LPAREN parameter_list_opt RPAREN
      {
          begin_function_definition($2, $4);
          $$ = $4;
      }
    ;

function_definition
    : function_header block
      {
          char *function_name = function_name_stack[function_stack_top - 1];
          SymbolType return_type = finish_function_definition($1);
          $$ = create_function_def_stmt(function_name, $1, $2, return_type);
      }
    ;

parameter_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | parameter_list
      {
          $$ = $1;
      }
    ;

parameter_list
    : parameter
      {
          $$ = $1;
      }
    | parameter_list COMMA parameter
      {
          $$ = append_parameter_list($1, $3);
      }
    ;

parameter
    : type_specifier ID
      {
          $$ = create_parameter_node((SymbolType)$1, $2);
      }
    ;

declaration_head
    : type_specifier
      {
          current_decl_type = (SymbolType)$1;
      }
    ;

declaration
    : declaration_head id_list SEMICOLON
      {
          $$ = $2;
      }
    | LOAD declaration_head id_list SEMICOLON
      {
          $$ = $3;
      }
    | declaration_head sync_semi
      {
          yyerror("invalid declaration");
          $$ = NULL;
      }
    | LOAD declaration_head sync_semi
      {
          yyerror("invalid declaration");
          $$ = NULL;
      }
    ;

id_list
    : id_item
      {
          $$ = $1;
      }
    | id_list COMMA id_item
      {
          $$ = append_statement($1, $3);
      }
    ;

id_item
    : ID
      {
          declare_identifier($1, current_decl_type);
          $$ = create_declaration_stmt(current_decl_type, $1, NULL);
      }
    | ID ASSIGN expression
      {
          if (declare_identifier($1, current_decl_type)) {
              validate_assignment($1, ($3)->value_type);
          }
          $$ = create_declaration_stmt(current_decl_type, $1, $3);
      }
    ;

assignment_statement
    : ID ASSIGN expression SEMICOLON
      {
          validate_assignment($1, ($3)->value_type);
          $$ = create_assignment_stmt($1, $3);
      }
    | SET ID ASSIGN expression SEMICOLON
      {
          validate_assignment($2, ($4)->value_type);
          $$ = create_assignment_stmt($2, $4);
      }
    | ID ASSIGN sync_semi
      {
          yyerror("invalid assignment expression");
          free($1);
          $$ = NULL;
      }
    | SET ID ASSIGN sync_semi
      {
          yyerror("invalid assignment expression");
          free($2);
          $$ = NULL;
      }
    ;

read_statement
    : READ LPAREN ID RPAREN SEMICOLON
      {
          SymbolType type;

          require_declared_identifier($3, &type);
          $$ = create_read_stmt($3, type);
      }
    | READ LPAREN error RPAREN SEMICOLON
      {
          yyerror("invalid read statement");
          yyerrok;
          $$ = NULL;
      }
    ;

write_statement
    : WRITE LPAREN expression RPAREN SEMICOLON
      {
          $$ = create_write_stmt($3);
      }
    | WRITE LPAREN error RPAREN SEMICOLON
      {
          yyerror("invalid write statement");
          yyerrok;
          $$ = NULL;
      }
    ;

chk_statement
    : CHK LPAREN condition RPAREN THEN block else_part
      {
          validate_logic_expression(($3)->value_type, "chk");
          $$ = create_chk_stmt($3, $6, $7);
      }
    ;

else_part
    : /* empty */
      {
          $$ = NULL;
      }
    | ELSE_TRY block
      {
          $$ = $2;
      }
    ;

repeat_statement
    : REPEAT DOING block UNTIL LPAREN condition RPAREN SEMICOLON
      {
          validate_logic_expression(($6)->value_type, "repeat-until");
          $$ = create_repeat_stmt($3, $6);
      }
    ;

decide_statement
    : DECIDE LPAREN expression RPAREN LBRACE when_clause_list otherwise_clause_opt RBRACE
      {
          $$ = create_decide_stmt($3, $6, $7);
      }
    ;

when_clause_list
    : when_clause
      {
          $$ = $1;
      }
    | when_clause_list when_clause
      {
          $$ = append_case_list($1, $2);
      }
    ;

when_clause
    : WHEN condition THEN block
      {
          validate_logic_expression(($2)->value_type, "when");
          $$ = create_case_node($2, $4);
      }
    ;

otherwise_clause_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | OTHERWISE THEN block
      {
          $$ = $3;
      }
    ;

condition
    : expression
      {
          $$ = $1;
      }
    | expression EQ expression
      {
          $$ = make_relational_expr("==", $1, $3);
      }
    | expression NEQ expression
      {
          $$ = make_relational_expr("!=", $1, $3);
      }
    | expression LT expression
      {
          $$ = make_relational_expr("<", $1, $3);
      }
    | expression GT expression
      {
          $$ = make_relational_expr(">", $1, $3);
      }
    | expression LE expression
      {
          $$ = make_relational_expr("<=", $1, $3);
      }
    | expression GE expression
      {
          $$ = make_relational_expr(">=", $1, $3);
      }
    ;

expression
    : expression PLUS term
      {
          $$ = make_numeric_expr("+", $1, $3);
      }
    | expression MINUS term
      {
          $$ = make_numeric_expr("-", $1, $3);
      }
    | term
      {
          $$ = $1;
      }
    ;

term
    : term STAR factor
      {
          $$ = make_numeric_expr("*", $1, $3);
      }
    | term SLASH factor
      {
          $$ = make_numeric_expr("/", $1, $3);
      }
    | factor
      {
          $$ = $1;
      }
    ;

argument_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | argument_list
      {
          $$ = $1;
      }
    ;

argument_list
    : expression
      {
          $$ = create_argument_list($1);
      }
    | argument_list COMMA expression
      {
          $$ = append_argument_list($1, create_argument_list($3));
      }
    ;

factor
    : ID
      {
          SymbolType type;

          require_declared_identifier($1, &type);
          $$ = create_variable_expr($1, type);
      }
    | ID LPAREN argument_list_opt RPAREN
      {
          validate_function_call($1, $3);
          $$ = create_function_call_expr($1, $3, lookup_function_return_type($1));
      }
    | INT_LITERAL
      {
          $$ = create_int_literal_expr($1);
      }
    | FLOAT_LITERAL
      {
          $$ = create_float_literal_expr((double)$1);
      }
    | STRING
      {
          char *decoded = decode_string_literal($1);
          free($1);
          $$ = create_string_literal_expr(decoded);
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
      }
    | MINUS factor %prec UMINUS
      {
          $$ = make_unary_minus_expr($2);
      }
    ;

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

static int is_numeric_type(SymbolType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static int is_assignment_compatible(SymbolType target_type, SymbolType value_type) {
    if (value_type == TYPE_UNKNOWN) {
        return 1;
    }

    if (target_type == value_type) {
        return 1;
    }

    return (value_type == TYPE_NUM && target_type == TYPE_REAL) ||
           (value_type == TYPE_NUM && target_type == TYPE_BIGREAL) ||
           (value_type == TYPE_REAL && target_type == TYPE_BIGREAL);
}

static ExprNode *make_numeric_expr(const char *op_text, ExprNode *left, ExprNode *right) {
    SymbolType result_type_value;

    if (left->value_type == TYPE_INVALID || right->value_type == TYPE_INVALID) {
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    result_type_value = result_type(left->value_type, right->value_type);
    if (result_type_value == TYPE_INVALID) {
        semantic_errors++;
    }

    return create_binary_expr(op_text, left, right, result_type_value);
}

static ExprNode *make_relational_expr(const char *op_text, ExprNode *left, ExprNode *right) {
    SymbolType left_type = left->value_type;
    SymbolType right_type = right->value_type;

    if (left_type == TYPE_INVALID || right_type == TYPE_INVALID) {
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    if (left_type != TYPE_UNKNOWN && right_type != TYPE_UNKNOWN &&
        !((is_numeric_type(left_type) && is_numeric_type(right_type)) || left_type == right_type)) {
        fprintf(stderr,
                "Semantic error at line %d: operator '%s' cannot compare %s with %s.\n",
                yylineno,
                op_text,
                symbol_type_name(left_type),
                symbol_type_name(right_type));
        semantic_errors++;
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    return create_binary_expr(op_text, left, right, TYPE_LOGIC);
}

static ExprNode *make_unary_minus_expr(ExprNode *operand) {
    if (operand->value_type != TYPE_UNKNOWN &&
        operand->value_type != TYPE_INVALID &&
        !is_numeric_type(operand->value_type)) {
        fprintf(stderr, "Semantic error at line %d: unary '-' requires a numeric operand.\n", yylineno);
        semantic_errors++;
        return create_unary_expr("-", operand, TYPE_INVALID);
    }

    return create_unary_expr("-", operand, operand->value_type);
}

static int require_declared_identifier(const char *name, SymbolType *out_type) {
    SymbolType type = get_type(name);

    if (type == TYPE_INVALID) {
        semantic_errors++;
        if (out_type != NULL) {
            *out_type = TYPE_INVALID;
        }
        return 0;
    }

    if (out_type != NULL) {
        *out_type = type;
    }

    return 1;
}

static int declare_identifier(const char *name, SymbolType type) {
    if (!insert_symbol(name, type)) {
        semantic_errors++;
        return 0;
    }

    return 1;
}

static int validate_assignment(const char *name, SymbolType value_type) {
    if (value_type == TYPE_INVALID) {
        return 0;
    }

    if (!check_assignment(name, value_type)) {
        semantic_errors++;
        return 0;
    }

    return 1;
}

static void validate_logic_expression(SymbolType type, const char *context) {
    if (type == TYPE_INVALID || type == TYPE_UNKNOWN) {
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

static FunctionSignature *find_function_signature(const char *name) {
    FunctionSignature *current = function_signatures;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

static SymbolType lookup_function_return_type(const char *name) {
    FunctionSignature *signature = find_function_signature(name);

    if (signature == NULL) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' is not defined.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
    }

    return signature->return_type;
}

static void validate_function_call(const char *name, ExprList *arguments) {
    FunctionSignature *signature = find_function_signature(name);
    ExprList *current_argument = arguments;
    int index = 0;

    if (signature == NULL) {
        return;
    }

    while (current_argument != NULL && index < signature->param_count) {
        if (!is_assignment_compatible(signature->param_types[index], current_argument->expr->value_type)) {
            fprintf(stderr,
                    "Semantic error at line %d: argument %d of function '%s' expects %s but found %s.\n",
                    yylineno,
                    index + 1,
                    name,
                    symbol_type_name(signature->param_types[index]),
                    symbol_type_name(current_argument->expr->value_type));
            semantic_errors++;
        }
        current_argument = current_argument->next;
        ++index;
    }

    if (current_argument != NULL || index != signature->param_count) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' called with the wrong number of arguments.\n",
                yylineno,
                name);
        semantic_errors++;
    }
}

static void begin_function_definition(char *name, ParamNode *parameters) {
    ParamNode *current = parameters;

    if (function_stack_top >= 64) {
        fprintf(stderr, "Semantic error: function nesting limit exceeded.\n");
        semantic_errors++;
        return;
    }

    function_name_stack[function_stack_top] = name;
    function_return_stack[function_stack_top] = TYPE_UNKNOWN;
    ++function_stack_top;

    enter_scope();
    while (current != NULL) {
        declare_identifier(current->name, current->type);
        current = current->next;
    }
}

static SymbolType finish_function_definition(ParamNode *parameters) {
    FunctionSignature *signature;
    ParamNode *current;
    int index = 0;
    SymbolType return_type;

    leave_scope();

    if (function_stack_top == 0) {
        return TYPE_UNKNOWN;
    }

    return_type = function_return_stack[function_stack_top - 1];
    signature = find_function_signature(function_name_stack[function_stack_top - 1]);
    if (signature != NULL) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' is already defined.\n",
                yylineno,
                function_name_stack[function_stack_top - 1]);
        semantic_errors++;
    } else {
        signature = (FunctionSignature *)malloc(sizeof(FunctionSignature));
        if (signature != NULL) {
            strncpy(signature->name, function_name_stack[function_stack_top - 1], sizeof(signature->name) - 1);
            signature->name[sizeof(signature->name) - 1] = '\0';
            signature->param_count = 0;
            current = parameters;
            while (current != NULL && index < 32) {
                signature->param_types[index++] = current->type;
                current = current->next;
            }
            signature->param_count = index;
            signature->return_type = return_type;
            signature->next = function_signatures;
            function_signatures = signature;
        }
    }

    --function_stack_top;
    return return_type;
}

static void note_function_return(SymbolType type) {
    SymbolType *current_type;

    if (function_stack_top == 0) {
        return;
    }

    current_type = &function_return_stack[function_stack_top - 1];
    if (*current_type == TYPE_UNKNOWN) {
        *current_type = type;
        return;
    }

    if (*current_type == type) {
        return;
    }

    if (is_numeric_type(*current_type) && is_numeric_type(type)) {
        *current_type = result_type(*current_type, type);
        return;
    }

    fprintf(stderr,
            "Semantic error at line %d: inconsistent return types inside function '%s'.\n",
            yylineno,
            function_name_stack[function_stack_top - 1]);
    semantic_errors++;
}

void yyerror(const char *message) {
    const char *near_text = yytext;

    if (near_text == NULL || near_text[0] == '\0') {
        near_text = "end of input";
    }

    fprintf(stderr,
            "Syntax error at line %d near '%s': %s\n",
            yylineno,
            near_text,
            message);
}
