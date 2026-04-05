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
static SymbolType function_declared_return_stack[64];
static int function_stack_top = 0;

static int is_numeric_type(SymbolType type);
static int is_assignment_compatible(SymbolType target_type, SymbolType value_type);
static ExprNode *make_numeric_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_relational_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_logic_expr(const char *op_text, ExprNode *left, ExprNode *right);
static ExprNode *make_unary_minus_expr(ExprNode *operand);
static ExprNode *make_not_expr(ExprNode *operand);
static ExprNode *make_abs_expr(ExprNode *operand);
static int require_declared_identifier(const char *name, SymbolType *out_type);
static int declare_identifier(const char *name, SymbolType type);
static int validate_assignment(const char *name, SymbolType value_type);
static void validate_logic_expression(SymbolType type, const char *context);
static FunctionSignature *find_function_signature(const char *name);
static void register_function_signature(const char *name, ParamNode *parameters, SymbolType return_type);
static SymbolType infer_function_call_type(const char *name, ExprList *arguments);
static void begin_function_definition(char *name, ParamNode *parameters, SymbolType declared_return_type);
static SymbolType finish_function_definition(ParamNode *parameters);
static void note_function_return(SymbolType type);
static SymbolType builtin_unary_return_type(const char *name, ExprList *arguments);

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

%token <strval> INCLUDE_DIRECTIVE ID STRING CHAR_LITERAL
%token <intval> INT_LITERAL
%token <floatval> FLOAT_LITERAL
%token START FX SEND EMPTY
%token NUM_TYPE REAL_TYPE BIGREAL_TYPE CHR_TYPE LOGIC_TYPE TEXT_TYPE
%token READ WRITE CHK ELSE_TRY THEN END REPEAT UNTIL DOING SKIP STOP DECIDE WHEN OTHERWISE
%token TRUE_LITERAL FALSE_LITERAL
%token AND OR NOT XOR
%token PLUS MINUS STAR SLASH MOD
%token ASSIGN EQ NEQ LT GT LE GE
%token ARROW FAT_ARROW PIPE
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE

%type <type> type_specifier return_type
%type <expr> expression logic_or logic_xor logic_and equality relational additive multiplicative unary primary
%type <stmt> statement_list statement declaration id_list id_item assignment_statement read_statement write_statement block
%type <stmt> chk_statement chk_suffix repeat_statement until_statement doing_statement decide_statement
%type <stmt> otherwise_clause_opt function_definition send_statement case_action
%type <param> parameter_list_opt parameter_list parameter function_header
%type <arglist> write_argument_list argument_list_opt argument_list
%type <caseclause> when_clause_list when_clause

%destructor { free($$); } <strval>
%destructor { free_expr($$); } <expr>
%destructor { free_statement_list($$); } <stmt>
%destructor { free_param_list($$); } <param>
%destructor { free_expr_list($$); } <arglist>
%destructor { free_case_list($$); } <caseclause>

%start program

%%

program
    : include_list start_definition
    ;

include_list
    : /* empty */
    | include_list INCLUDE_DIRECTIVE
      {
          free($2);
      }
    ;

start_definition
    : START LPAREN RPAREN ARROW EMPTY start_semicolon_opt block
      {
          StmtNode *body = NULL;

          if ($7 != NULL && $7->kind == STMT_BLOCK) {
              body = $7->data.block.statements;
              $7->data.block.statements = NULL;
              free_statement_list($7);
          }

          parsed_program = create_program(body);
      }
    ;

start_semicolon_opt
    : /* empty */
    | SEMICOLON
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

statement
    : declaration
    | assignment_statement
    | read_statement
    | write_statement
    | function_definition
    | send_statement
    | chk_statement
    | repeat_statement
    | until_statement
    | doing_statement
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
    : FX ID LPAREN parameter_list_opt RPAREN ARROW return_type
      {
          begin_function_definition($2, $4, (SymbolType)$7);
          $$ = $4;
      }
    ;

function_definition
    : function_header block
      {
          char *function_name = function_name_stack[function_stack_top - 1];
          SymbolType return_type_value = finish_function_definition($1);

          $$ = create_function_def_stmt(function_name, $1, $2, return_type_value);
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
    ;

read_statement
    : READ LPAREN ID RPAREN SEMICOLON
      {
          SymbolType type;

          require_declared_identifier($3, &type);
          $$ = create_read_stmt($3, type);
      }
    ;

write_statement
    : WRITE LPAREN write_argument_list RPAREN SEMICOLON
      {
          $$ = create_write_stmt($3);
      }
    ;

write_argument_list
    : expression
      {
          $$ = create_expr_list($1);
      }
    | write_argument_list COMMA expression
      {
          $$ = append_expr_list($1, create_expr_list($3));
      }
    ;

send_statement
    : SEND expression SEMICOLON
      {
          if (function_stack_top > 0) {
              note_function_return(($2)->value_type);
          }
          $$ = create_return_stmt($2);
      }
    ;

chk_statement
    : CHK LPAREN expression RPAREN statement_list END CHK chk_suffix
      {
          validate_logic_expression(($3)->value_type, "chk");
          $$ = create_chk_stmt($3, $5, $8);
      }
    ;

chk_suffix
    : /* empty */
      {
          $$ = NULL;
      }
    | THEN statement_list END THEN
      {
          $$ = $2;
      }
    | ELSE_TRY LPAREN expression RPAREN statement_list END ELSE_TRY chk_suffix
      {
          validate_logic_expression(($3)->value_type, "else_try");
          $$ = create_chk_stmt($3, $5, $8);
      }
    ;

repeat_statement
    : REPEAT LPAREN ID COMMA expression COMMA expression RPAREN block
      {
          SymbolType type;

          require_declared_identifier($3, &type);
          validate_logic_expression(($5)->value_type, "repeat");
          validate_assignment($3, ($7)->value_type);
          $$ = create_repeat_stmt($3, $5, $7, $9);
      }
    ;

until_statement
    : UNTIL LPAREN expression RPAREN block
      {
          validate_logic_expression(($3)->value_type, "until");
          $$ = create_until_stmt($3, $5);
      }
    ;

doing_statement
    : DOING block UNTIL LPAREN expression RPAREN SEMICOLON
      {
          validate_logic_expression(($5)->value_type, "doing-until");
          $$ = create_doing_stmt($2, $5);
      }
    ;

decide_statement
    : DECIDE expression LBRACE when_clause_list otherwise_clause_opt RBRACE
      {
          $$ = create_decide_stmt($2, $4, $5);
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
    : WHEN LPAREN expression RPAREN FAT_ARROW case_action
      {
          $$ = create_case_node($3, $6);
      }
    ;

otherwise_clause_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | OTHERWISE FAT_ARROW case_action
      {
          $$ = $3;
      }
    ;

case_action
    : statement
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

expression
    : logic_or
      {
          $$ = $1;
      }
    ;

logic_or
    : logic_or OR logic_xor
      {
          $$ = make_logic_expr("OR", $1, $3);
      }
    | logic_xor
      {
          $$ = $1;
      }
    ;

logic_xor
    : logic_xor XOR logic_and
      {
          $$ = make_logic_expr("XOR", $1, $3);
      }
    | logic_and
      {
          $$ = $1;
      }
    ;

logic_and
    : logic_and AND equality
      {
          $$ = make_logic_expr("AND", $1, $3);
      }
    | equality
      {
          $$ = $1;
      }
    ;

equality
    : equality EQ relational
      {
          $$ = make_relational_expr("==", $1, $3);
      }
    | equality NEQ relational
      {
          $$ = make_relational_expr("!=", $1, $3);
      }
    | relational
      {
          $$ = $1;
      }
    ;

relational
    : relational LT additive
      {
          $$ = make_relational_expr("<", $1, $3);
      }
    | relational GT additive
      {
          $$ = make_relational_expr(">", $1, $3);
      }
    | relational LE additive
      {
          $$ = make_relational_expr("<=", $1, $3);
      }
    | relational GE additive
      {
          $$ = make_relational_expr(">=", $1, $3);
      }
    | additive
      {
          $$ = $1;
      }
    ;

additive
    : additive PLUS multiplicative
      {
          $$ = make_numeric_expr("+", $1, $3);
      }
    | additive MINUS multiplicative
      {
          $$ = make_numeric_expr("-", $1, $3);
      }
    | multiplicative
      {
          $$ = $1;
      }
    ;

multiplicative
    : multiplicative STAR unary
      {
          $$ = make_numeric_expr("*", $1, $3);
      }
    | multiplicative SLASH unary
      {
          $$ = make_numeric_expr("/", $1, $3);
      }
    | multiplicative MOD unary
      {
          $$ = make_numeric_expr("%", $1, $3);
      }
    | unary
      {
          $$ = $1;
      }
    ;

unary
    : NOT unary
      {
          $$ = make_not_expr($2);
      }
    | PLUS unary
      {
          $$ = $2;
      }
    | MINUS unary
      {
          $$ = make_unary_minus_expr($2);
      }
    | PIPE expression PIPE
      {
          $$ = make_abs_expr($2);
      }
    | primary
      {
          $$ = $1;
      }
    ;

primary
    : ID
      {
          SymbolType type;

          require_declared_identifier($1, &type);
          $$ = create_variable_expr($1, type);
      }
    | ID LPAREN argument_list_opt RPAREN
      {
          SymbolType return_type_value = infer_function_call_type($1, $3);

          $$ = create_function_call_expr($1, $3, return_type_value);
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
    | CHAR_LITERAL
      {
          char value = decode_char_literal($1);
          free($1);
          $$ = create_char_literal_expr(value);
      }
    | TRUE_LITERAL
      {
          $$ = create_bool_literal_expr(1);
      }
    | FALSE_LITERAL
      {
          $$ = create_bool_literal_expr(0);
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
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

return_type
    : type_specifier
      {
          $$ = $1;
      }
    | EMPTY
      {
          $$ = TYPE_EMPTY;
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

    if (strcmp(op_text, "%") == 0) {
        if (left->value_type != TYPE_NUM || right->value_type != TYPE_NUM) {
            fprintf(stderr, "Semantic error at line %d: modulus requires num operands.\n", yylineno);
            semantic_errors++;
            return create_binary_expr(op_text, left, right, TYPE_INVALID);
        }

        return create_binary_expr(op_text, left, right, TYPE_NUM);
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

static ExprNode *make_logic_expr(const char *op_text, ExprNode *left, ExprNode *right) {
    SymbolType result_type_value = TYPE_LOGIC;

    if (left->value_type == TYPE_INVALID || right->value_type == TYPE_INVALID) {
        return create_binary_expr(op_text, left, right, TYPE_INVALID);
    }

    if (strcmp(op_text, "XOR") == 0) {
        if (left->value_type == TYPE_LOGIC && right->value_type == TYPE_LOGIC) {
            result_type_value = TYPE_LOGIC;
        } else if (left->value_type == TYPE_NUM && right->value_type == TYPE_NUM) {
            result_type_value = TYPE_NUM;
        } else {
            fprintf(stderr,
                    "Semantic error at line %d: XOR requires either two logic operands or two num operands.\n",
                    yylineno);
            semantic_errors++;
            result_type_value = TYPE_INVALID;
        }
    } else if (left->value_type != TYPE_LOGIC || right->value_type != TYPE_LOGIC) {
        fprintf(stderr,
                "Semantic error at line %d: operator '%s' requires logic operands.\n",
                yylineno,
                op_text);
        semantic_errors++;
        result_type_value = TYPE_INVALID;
    }

    return create_binary_expr(op_text, left, right, result_type_value);
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

static ExprNode *make_not_expr(ExprNode *operand) {
    if (operand->value_type != TYPE_UNKNOWN &&
        operand->value_type != TYPE_INVALID &&
        operand->value_type != TYPE_LOGIC) {
        fprintf(stderr, "Semantic error at line %d: NOT requires a logic operand.\n", yylineno);
        semantic_errors++;
        return create_unary_expr("!", operand, TYPE_INVALID);
    }

    return create_unary_expr("!", operand, TYPE_LOGIC);
}

static ExprNode *make_abs_expr(ExprNode *operand) {
    if (operand->value_type != TYPE_UNKNOWN &&
        operand->value_type != TYPE_INVALID &&
        !is_numeric_type(operand->value_type)) {
        fprintf(stderr, "Semantic error at line %d: absolute value requires a numeric operand.\n", yylineno);
        semantic_errors++;
        return create_unary_expr("ABS", operand, TYPE_INVALID);
    }

    return create_unary_expr("ABS", operand, operand->value_type);
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

static void register_function_signature(const char *name, ParamNode *parameters, SymbolType return_type) {
    FunctionSignature *signature;
    ParamNode *current = parameters;
    int index = 0;

    if (find_function_signature(name) != NULL) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' is already defined.\n",
                yylineno,
                name);
        semantic_errors++;
        return;
    }

    signature = (FunctionSignature *)malloc(sizeof(FunctionSignature));
    if (signature == NULL) {
        fprintf(stderr,
                "Semantic error at line %d: out of memory while recording function '%s'.\n",
                yylineno,
                name);
        semantic_errors++;
        return;
    }

    strncpy(signature->name, name, sizeof(signature->name) - 1);
    signature->name[sizeof(signature->name) - 1] = '\0';
    while (current != NULL && index < 32) {
        signature->param_types[index++] = current->type;
        current = current->next;
    }
    signature->param_count = index;
    signature->return_type = return_type;
    signature->next = function_signatures;
    function_signatures = signature;
}

static SymbolType builtin_unary_return_type(const char *name, ExprList *arguments) {
    if (arguments == NULL || arguments->next != NULL) {
        fprintf(stderr,
                "Semantic error at line %d: builtin '%s' expects one argument.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
    }

    if (!is_numeric_type(arguments->expr->value_type)) {
        fprintf(stderr,
                "Semantic error at line %d: builtin '%s' requires a numeric argument.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
    }

    return arguments->expr->value_type;
}

static SymbolType infer_function_call_type(const char *name, ExprList *arguments) {
    FunctionSignature *signature = find_function_signature(name);
    ExprList *current_argument = arguments;
    int index = 0;

    if (strcmp(name, "power") == 0) {
        if (arguments == NULL || arguments->next == NULL || arguments->next->next != NULL) {
            fprintf(stderr,
                    "Semantic error at line %d: builtin 'power' expects two arguments.\n",
                    yylineno);
            semantic_errors++;
            return TYPE_INVALID;
        }

        if (!is_numeric_type(arguments->expr->value_type) ||
            !is_numeric_type(arguments->next->expr->value_type)) {
            fprintf(stderr,
                    "Semantic error at line %d: builtin 'power' requires numeric arguments.\n",
                    yylineno);
            semantic_errors++;
            return TYPE_INVALID;
        }

        return result_type(arguments->expr->value_type, arguments->next->expr->value_type);
    }

    if (strcmp(name, "squart") == 0 || strcmp(name, "upper") == 0 ||
        strcmp(name, "lower") == 0 || strcmp(name, "log") == 0 ||
        strcmp(name, "sin") == 0 || strcmp(name, "cos") == 0 ||
        strcmp(name, "tan") == 0 || strcmp(name, "asin") == 0 ||
        strcmp(name, "acos") == 0 || strcmp(name, "atan") == 0) {
        return builtin_unary_return_type(name, arguments);
    }

    if (signature == NULL) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' is not defined.\n",
                yylineno,
                name);
        semantic_errors++;
        return TYPE_INVALID;
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

    return signature->return_type;
}

static void begin_function_definition(char *name, ParamNode *parameters, SymbolType declared_return_type) {
    ParamNode *current = parameters;

    if (function_stack_top >= 64) {
        fprintf(stderr, "Semantic error: function nesting limit exceeded.\n");
        semantic_errors++;
        return;
    }

    function_name_stack[function_stack_top] = name;
    function_return_stack[function_stack_top] = TYPE_UNKNOWN;
    function_declared_return_stack[function_stack_top] = declared_return_type;
    ++function_stack_top;

    /* Register the signature before parsing the body so self-calls work. */
    register_function_signature(name, parameters, declared_return_type);

    enter_scope();
    while (current != NULL) {
        declare_identifier(current->name, current->type);
        current = current->next;
    }
}

static SymbolType finish_function_definition(ParamNode *parameters) {
    SymbolType observed_return_type;
    SymbolType declared_return_type;

    (void)parameters;

    leave_scope();

    if (function_stack_top == 0) {
        return TYPE_UNKNOWN;
    }

    observed_return_type = function_return_stack[function_stack_top - 1];
    declared_return_type = function_declared_return_stack[function_stack_top - 1];

    if (declared_return_type == TYPE_EMPTY) {
        if (observed_return_type != TYPE_UNKNOWN) {
            fprintf(stderr,
                    "Semantic error at line %d: function '%s' is declared empty but sends a value.\n",
                    yylineno,
                    function_name_stack[function_stack_top - 1]);
            semantic_errors++;
        }
    } else if (observed_return_type == TYPE_UNKNOWN) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' must send a %s value.\n",
                yylineno,
                function_name_stack[function_stack_top - 1],
                symbol_type_name(declared_return_type));
        semantic_errors++;
    } else if (!is_assignment_compatible(declared_return_type, observed_return_type)) {
        fprintf(stderr,
                "Semantic error at line %d: function '%s' sends %s but is declared as %s.\n",
                yylineno,
                function_name_stack[function_stack_top - 1],
                symbol_type_name(observed_return_type),
                symbol_type_name(declared_return_type));
        semantic_errors++;
    }

    --function_stack_top;
    return declared_return_type;
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
            "Semantic error at line %d: inconsistent send types inside function '%s'.\n",
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
