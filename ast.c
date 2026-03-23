#include <stdlib.h>
#include <string.h>
#include "ast.h"

static ExprNode *allocate_expr(SymbolType value_type, ExprKind kind) {
    ExprNode *expr = (ExprNode *)malloc(sizeof(ExprNode));

    if (expr == NULL) {
        return NULL;
    }

    expr->kind = kind;
    expr->value_type = value_type;
    return expr;
}

static StmtNode *allocate_stmt(StmtKind kind) {
    StmtNode *stmt = (StmtNode *)malloc(sizeof(StmtNode));

    if (stmt == NULL) {
        return NULL;
    }

    stmt->kind = kind;
    stmt->next = NULL;
    return stmt;
}

ExprNode *create_int_literal_expr(long long value) {
    ExprNode *expr = allocate_expr(TYPE_NUM, EXPR_INT_LITERAL);

    if (expr != NULL) {
        expr->data.int_value = value;
    }

    return expr;
}

ExprNode *create_float_literal_expr(double value) {
    ExprNode *expr = allocate_expr(TYPE_REAL, EXPR_FLOAT_LITERAL);

    if (expr != NULL) {
        expr->data.float_value = value;
    }

    return expr;
}

ExprNode *create_string_literal_expr(char *value) {
    ExprNode *expr = allocate_expr(TYPE_TEXT, EXPR_STRING_LITERAL);

    if (expr != NULL) {
        expr->data.string_value = value;
    }

    return expr;
}

ExprNode *create_variable_expr(char *name, SymbolType value_type) {
    ExprNode *expr = allocate_expr(value_type, EXPR_VARIABLE);

    if (expr != NULL) {
        expr->data.identifier = name;
    }

    return expr;
}

ExprNode *create_binary_expr(const char *op, ExprNode *left, ExprNode *right, SymbolType value_type) {
    ExprNode *expr = allocate_expr(value_type, EXPR_BINARY);

    if (expr != NULL) {
        strncpy(expr->data.binary.op, op, sizeof(expr->data.binary.op) - 1);
        expr->data.binary.op[sizeof(expr->data.binary.op) - 1] = '\0';
        expr->data.binary.left = left;
        expr->data.binary.right = right;
    }

    return expr;
}

ExprNode *create_unary_expr(const char *op, ExprNode *operand, SymbolType value_type) {
    ExprNode *expr = allocate_expr(value_type, EXPR_UNARY);

    if (expr != NULL) {
        strncpy(expr->data.unary.op, op, sizeof(expr->data.unary.op) - 1);
        expr->data.unary.op[sizeof(expr->data.unary.op) - 1] = '\0';
        expr->data.unary.operand = operand;
    }

    return expr;
}

ExprNode *create_function_call_expr(char *name, ExprList *arguments, SymbolType value_type) {
    ExprNode *expr = allocate_expr(value_type, EXPR_FUNCTION_CALL);

    if (expr != NULL) {
        expr->data.call.name = name;
        expr->data.call.arguments = arguments;
    }

    return expr;
}

ExprList *create_expr_list(ExprNode *expr) {
    ExprList *item = (ExprList *)malloc(sizeof(ExprList));

    if (item == NULL) {
        return NULL;
    }

    item->expr = expr;
    item->next = NULL;
    return item;
}

ExprList *append_expr_list(ExprList *list, ExprList *item) {
    ExprList *tail;

    if (item == NULL) {
        return list;
    }

    if (list == NULL) {
        return item;
    }

    tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = item;
    return list;
}

ParamNode *create_param_node(SymbolType type, char *name) {
    ParamNode *param = (ParamNode *)malloc(sizeof(ParamNode));

    if (param == NULL) {
        return NULL;
    }

    param->type = type;
    param->name = name;
    param->next = NULL;
    return param;
}

ParamNode *append_param_list(ParamNode *list, ParamNode *item) {
    ParamNode *tail;

    if (item == NULL) {
        return list;
    }

    if (list == NULL) {
        return item;
    }

    tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = item;
    return list;
}

int param_count(const ParamNode *params) {
    int count = 0;

    while (params != NULL) {
        ++count;
        params = params->next;
    }

    return count;
}

CaseNode *create_case_node(ExprNode *condition, StmtNode *body) {
    CaseNode *node = (CaseNode *)malloc(sizeof(CaseNode));

    if (node == NULL) {
        return NULL;
    }

    node->condition = condition;
    node->body = body;
    node->next = NULL;
    return node;
}

CaseNode *append_case_list(CaseNode *list, CaseNode *item) {
    CaseNode *tail;

    if (item == NULL) {
        return list;
    }

    if (list == NULL) {
        return item;
    }

    tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = item;
    return list;
}

StmtNode *create_declaration_stmt(SymbolType declared_type, char *name, ExprNode *initializer) {
    StmtNode *stmt = allocate_stmt(STMT_DECLARATION);

    if (stmt != NULL) {
        stmt->data.declaration.declared_type = declared_type;
        stmt->data.declaration.name = name;
        stmt->data.declaration.initializer = initializer;
    }

    return stmt;
}

StmtNode *create_assignment_stmt(char *name, ExprNode *value) {
    StmtNode *stmt = allocate_stmt(STMT_ASSIGNMENT);

    if (stmt != NULL) {
        stmt->data.assignment.name = name;
        stmt->data.assignment.value = value;
    }

    return stmt;
}

StmtNode *create_read_stmt(char *name) {
    StmtNode *stmt = allocate_stmt(STMT_READ);

    if (stmt != NULL) {
        stmt->data.read_stmt.name = name;
    }

    return stmt;
}

StmtNode *create_write_stmt(ExprNode *value) {
    StmtNode *stmt = allocate_stmt(STMT_WRITE);

    if (stmt != NULL) {
        stmt->data.write_stmt.value = value;
    }

    return stmt;
}

StmtNode *create_block_stmt(StmtNode *statements) {
    StmtNode *stmt = allocate_stmt(STMT_BLOCK);

    if (stmt != NULL) {
        stmt->data.block.statements = statements;
    }

    return stmt;
}

StmtNode *create_chk_stmt(ExprNode *condition, StmtNode *then_branch, StmtNode *else_branch) {
    StmtNode *stmt = allocate_stmt(STMT_CHK);

    if (stmt != NULL) {
        stmt->data.chk_stmt.condition = condition;
        stmt->data.chk_stmt.then_branch = then_branch;
        stmt->data.chk_stmt.else_branch = else_branch;
    }

    return stmt;
}

StmtNode *create_repeat_stmt(StmtNode *body, ExprNode *condition) {
    StmtNode *stmt = allocate_stmt(STMT_REPEAT);

    if (stmt != NULL) {
        stmt->data.repeat_stmt.body = body;
        stmt->data.repeat_stmt.condition = condition;
    }

    return stmt;
}

StmtNode *create_decide_stmt(ExprNode *selector, CaseNode *cases, StmtNode *otherwise_branch) {
    StmtNode *stmt = allocate_stmt(STMT_DECIDE);

    if (stmt != NULL) {
        stmt->data.decide_stmt.selector = selector;
        stmt->data.decide_stmt.cases = cases;
        stmt->data.decide_stmt.otherwise_branch = otherwise_branch;
    }

    return stmt;
}

StmtNode *create_function_def_stmt(char *name, ParamNode *parameters, StmtNode *body, SymbolType return_type) {
    StmtNode *stmt = allocate_stmt(STMT_FUNCTION_DEF);

    if (stmt != NULL) {
        stmt->data.function_def.name = name;
        stmt->data.function_def.parameters = parameters;
        stmt->data.function_def.body = body;
        stmt->data.function_def.return_type = return_type;
    }

    return stmt;
}

StmtNode *create_skip_stmt(void) {
    return allocate_stmt(STMT_SKIP);
}

StmtNode *create_stop_stmt(void) {
    return allocate_stmt(STMT_STOP);
}

StmtNode *create_return_stmt(ExprNode *value) {
    StmtNode *stmt = allocate_stmt(STMT_RETURN);

    if (stmt != NULL) {
        stmt->data.return_stmt.value = value;
    }

    return stmt;
}

StmtNode *append_statement(StmtNode *list, StmtNode *item) {
    StmtNode *tail;

    if (item == NULL) {
        return list;
    }

    if (list == NULL) {
        return item;
    }

    tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = item;
    return list;
}

Program *create_program(StmtNode *statements) {
    Program *program = (Program *)malloc(sizeof(Program));

    if (program == NULL) {
        return NULL;
    }

    program->statements = statements;
    return program;
}

void free_expr(ExprNode *expr) {
    if (expr == NULL) {
        return;
    }

    switch (expr->kind) {
        case EXPR_STRING_LITERAL:
            free(expr->data.string_value);
            break;
        case EXPR_VARIABLE:
            free(expr->data.identifier);
            break;
        case EXPR_BINARY:
            free_expr(expr->data.binary.left);
            free_expr(expr->data.binary.right);
            break;
        case EXPR_UNARY:
            free_expr(expr->data.unary.operand);
            break;
        case EXPR_FUNCTION_CALL:
            free(expr->data.call.name);
            free_expr_list(expr->data.call.arguments);
            break;
        default:
            break;
    }

    free(expr);
}

void free_expr_list(ExprList *list) {
    ExprList *next;

    while (list != NULL) {
        next = list->next;
        free_expr(list->expr);
        free(list);
        list = next;
    }
}

void free_param_list(ParamNode *params) {
    ParamNode *next;

    while (params != NULL) {
        next = params->next;
        free(params->name);
        free(params);
        params = next;
    }
}

void free_case_list(CaseNode *cases) {
    CaseNode *next;

    while (cases != NULL) {
        next = cases->next;
        free_expr(cases->condition);
        free_statement_list(cases->body);
        free(cases);
        cases = next;
    }
}

void free_statement_list(StmtNode *stmt) {
    StmtNode *next;

    while (stmt != NULL) {
        next = stmt->next;

        switch (stmt->kind) {
            case STMT_DECLARATION:
                free(stmt->data.declaration.name);
                free_expr(stmt->data.declaration.initializer);
                break;
            case STMT_ASSIGNMENT:
                free(stmt->data.assignment.name);
                free_expr(stmt->data.assignment.value);
                break;
            case STMT_READ:
                free(stmt->data.read_stmt.name);
                break;
            case STMT_WRITE:
                free_expr(stmt->data.write_stmt.value);
                break;
            case STMT_BLOCK:
                free_statement_list(stmt->data.block.statements);
                break;
            case STMT_CHK:
                free_expr(stmt->data.chk_stmt.condition);
                free_statement_list(stmt->data.chk_stmt.then_branch);
                free_statement_list(stmt->data.chk_stmt.else_branch);
                break;
            case STMT_REPEAT:
                free_statement_list(stmt->data.repeat_stmt.body);
                free_expr(stmt->data.repeat_stmt.condition);
                break;
            case STMT_DECIDE:
                free_expr(stmt->data.decide_stmt.selector);
                free_case_list(stmt->data.decide_stmt.cases);
                free_statement_list(stmt->data.decide_stmt.otherwise_branch);
                break;
            case STMT_FUNCTION_DEF:
                free(stmt->data.function_def.name);
                free_param_list(stmt->data.function_def.parameters);
                free_statement_list(stmt->data.function_def.body);
                break;
            case STMT_RETURN:
                free_expr(stmt->data.return_stmt.value);
                break;
            default:
                break;
        }

        free(stmt);
        stmt = next;
    }
}

void free_program(Program *program) {
    if (program == NULL) {
        return;
    }

    free_statement_list(program->statements);
    free(program);
}
