#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"

typedef Program ASTNode;

int interpret_program(const Program *program);
static inline int execute_program(ASTNode *root) {
    return interpret_program((const Program *)root);
}

int execute_statement(StmtNode *node);
ExprResult evaluate_expression(ExprNode *node);

#endif
