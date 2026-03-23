#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast.h"

void generate_c_code(Program *program, FILE *out);
void generate_program_c(Program *program, FILE *out);
void generate_statement_c(StmtNode *stmt, FILE *out, int indent_level);
void generate_expression_c(ExprNode *expr, FILE *out);

#endif
