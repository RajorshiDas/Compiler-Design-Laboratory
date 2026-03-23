#ifndef AST_H
#define AST_H

#include "symtab.h"

typedef enum ExprKind {
    EXPR_INT_LITERAL,
    EXPR_FLOAT_LITERAL,
    EXPR_STRING_LITERAL,
    EXPR_VARIABLE,
    EXPR_BINARY,
    EXPR_UNARY,
    EXPR_FUNCTION_CALL
} ExprKind;

typedef enum StmtKind {
    STMT_DECLARATION,
    STMT_ASSIGNMENT,
    STMT_READ,
    STMT_WRITE,
    STMT_BLOCK,
    STMT_CHK,
    STMT_REPEAT,
    STMT_DECIDE,
    STMT_FUNCTION_DEF,
    STMT_SKIP,
    STMT_STOP,
    STMT_RETURN
} StmtKind;

typedef struct ExprNode ExprNode;
typedef struct ExprList ExprList;
typedef struct ParamNode ParamNode;
typedef struct CaseNode CaseNode;
typedef struct StmtNode StmtNode;
typedef struct Program Program;

struct ExprList {
    ExprNode *expr;
    ExprList *next;
};

struct ParamNode {
    SymbolType type;
    char *name;
    ParamNode *next;
};

struct CaseNode {
    ExprNode *condition;
    StmtNode *body;
    CaseNode *next;
};

struct ExprNode {
    ExprKind kind;
    SymbolType value_type;
    union {
        long long int_value;
        double float_value;
        char *string_value;
        char *identifier;
        struct {
            char op[3];
            ExprNode *left;
            ExprNode *right;
        } binary;
        struct {
            char op[3];
            ExprNode *operand;
        } unary;
        struct {
            char *name;
            ExprList *arguments;
        } call;
    } data;
};

struct StmtNode {
    StmtKind kind;
    StmtNode *next;
    union {
        struct {
            SymbolType declared_type;
            char *name;
            ExprNode *initializer;
        } declaration;
        struct {
            char *name;
            ExprNode *value;
        } assignment;
        struct {
            char *name;
        } read_stmt;
        struct {
            ExprNode *value;
        } write_stmt;
        struct {
            StmtNode *statements;
        } block;
        struct {
            ExprNode *condition;
            StmtNode *then_branch;
            StmtNode *else_branch;
        } chk_stmt;
        struct {
            StmtNode *body;
            ExprNode *condition;
        } repeat_stmt;
        struct {
            ExprNode *selector;
            CaseNode *cases;
            StmtNode *otherwise_branch;
        } decide_stmt;
        struct {
            char *name;
            ParamNode *parameters;
            StmtNode *body;
            SymbolType return_type;
        } function_def;
        struct {
            ExprNode *value;
        } return_stmt;
    } data;
};

struct Program {
    StmtNode *statements;
};

ExprNode *create_int_literal_expr(long long value);
ExprNode *create_float_literal_expr(double value);
ExprNode *create_string_literal_expr(char *value);
ExprNode *create_variable_expr(char *name, SymbolType value_type);
ExprNode *create_binary_expr(const char *op, ExprNode *left, ExprNode *right, SymbolType value_type);
ExprNode *create_unary_expr(const char *op, ExprNode *operand, SymbolType value_type);
ExprNode *create_function_call_expr(char *name, ExprList *arguments, SymbolType value_type);

ExprList *create_expr_list(ExprNode *expr);
ExprList *append_expr_list(ExprList *list, ExprList *item);

ParamNode *create_param_node(SymbolType type, char *name);
ParamNode *append_param_list(ParamNode *list, ParamNode *item);
int param_count(const ParamNode *params);

CaseNode *create_case_node(ExprNode *condition, StmtNode *body);
CaseNode *append_case_list(CaseNode *list, CaseNode *item);

StmtNode *create_declaration_stmt(SymbolType declared_type, char *name, ExprNode *initializer);
StmtNode *create_assignment_stmt(char *name, ExprNode *value);
StmtNode *create_read_stmt(char *name);
StmtNode *create_write_stmt(ExprNode *value);
StmtNode *create_block_stmt(StmtNode *statements);
StmtNode *create_chk_stmt(ExprNode *condition, StmtNode *then_branch, StmtNode *else_branch);
StmtNode *create_repeat_stmt(StmtNode *body, ExprNode *condition);
StmtNode *create_decide_stmt(ExprNode *selector, CaseNode *cases, StmtNode *otherwise_branch);
StmtNode *create_function_def_stmt(char *name, ParamNode *parameters, StmtNode *body, SymbolType return_type);
StmtNode *create_skip_stmt(void);
StmtNode *create_stop_stmt(void);
StmtNode *create_return_stmt(ExprNode *value);
StmtNode *append_statement(StmtNode *list, StmtNode *item);

Program *create_program(StmtNode *statements);

void free_expr(ExprNode *expr);
void free_expr_list(ExprList *list);
void free_param_list(ParamNode *params);
void free_case_list(CaseNode *cases);
void free_statement_list(StmtNode *stmt);
void free_program(Program *program);

#endif
