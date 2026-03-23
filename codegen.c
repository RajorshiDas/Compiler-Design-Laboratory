#include <stdio.h>
#include "codegen.h"
static void print_indent(FILE *out, int indent_level) {
    int i;

    for (i = 0; i < indent_level; ++i) {
        fputs("    ", out);
    }
}

static const char *c_type_name(SymbolType type) {
    switch (type) {
        case TYPE_NUM:
            return "long long";
        case TYPE_REAL:
            return "double";
        case TYPE_BIGREAL:
            return "double";
        case TYPE_CHAR:
            return "char";
        case TYPE_LOGIC:
            return "int";
        case TYPE_TEXT:
            return "char *";
        default:
            return "int";
    }
}

static const char *printf_format(SymbolType type) {
    switch (type) {
        case TYPE_NUM:
            return "%lld\\n";
        case TYPE_REAL:
        case TYPE_BIGREAL:
            return "%g\\n";
        case TYPE_CHAR:
            return "%c\\n";
        case TYPE_TEXT:
            return "%s\\n";
        case TYPE_LOGIC:
            return "%d\\n";
        default:
            return "%d\\n";
    }
}

static const char *scanf_format(SymbolType type) {
    switch (type) {
        case TYPE_NUM:
            return "%lld";
        case TYPE_REAL:
        case TYPE_BIGREAL:
            return "%lf";
        case TYPE_CHAR:
            return " %c";
        case TYPE_TEXT:
            return "%s";
        case TYPE_LOGIC:
            return "%d";
        default:
            return "%d";
    }
}

static void generate_write_c(ExprNode *expr, FILE *out, int indent_level) {
    SymbolType type = TYPE_NUM;

    if (expr != NULL) {
        type = expr->value_type;
    }

    print_indent(out, indent_level);
    fprintf(out, "printf(\"%s\", ", printf_format(type));
    generate_expression_c(expr, out);
    fprintf(out, ");\n");
}

static void generate_read_c(const char *name, SymbolType type, FILE *out, int indent_level) {
    print_indent(out, indent_level);
    if (type == TYPE_TEXT) {
        fprintf(out, "scanf(\"%s\", %s);\n", scanf_format(type), name);
    } else {
        fprintf(out, "scanf(\"%s\", &%s);\n", scanf_format(type), name);
    }
}

static void generate_statement_node_c(StmtNode *stmt, FILE *out, int indent_level);

static void generate_decide_c(StmtNode *stmt, FILE *out, int indent_level) {
    CaseNode *case_node = stmt->data.decide_stmt.cases;
    int first = 1;

    while (case_node != NULL) {
        print_indent(out, indent_level);
        fprintf(out, "%sif (", first ? "" : "else ");
        generate_expression_c(case_node->condition, out);
        fputs(")\n", out);

        if (case_node->body != NULL && case_node->body->kind == STMT_BLOCK) {
            generate_statement_node_c(case_node->body, out, indent_level);
        } else {
            print_indent(out, indent_level);
            fputs("{\n", out);
            generate_statement_c(case_node->body, out, indent_level + 1);
            print_indent(out, indent_level);
            fputs("}\n", out);
        }

        first = 0;
        case_node = case_node->next;
    }

    if (stmt->data.decide_stmt.otherwise_branch != NULL) {
        print_indent(out, indent_level);
        fputs("else\n", out);

        if (stmt->data.decide_stmt.otherwise_branch->kind == STMT_BLOCK) {
            generate_statement_node_c(stmt->data.decide_stmt.otherwise_branch, out, indent_level);
        } else {
            print_indent(out, indent_level);
            fputs("{\n", out);
            generate_statement_c(stmt->data.decide_stmt.otherwise_branch, out, indent_level + 1);
            print_indent(out, indent_level);
            fputs("}\n", out);
        }
    }
}

void generate_expression_c(ExprNode *expr, FILE *out) {
    if (expr == NULL) {
        fputs("0", out);
        return;
    }

    switch (expr->kind) {
        case EXPR_INT_LITERAL:
            fprintf(out, "%lld", expr->data.int_value);
            break;

        case EXPR_FLOAT_LITERAL:
            fprintf(out, "%g", expr->data.float_value);
            break;

        case EXPR_STRING_LITERAL:
            fprintf(out, "\"%s\"", expr->data.string_value != NULL ? expr->data.string_value : "");
            break;

        case EXPR_VARIABLE:
            fprintf(out, "%s", expr->data.identifier);
            break;

        case EXPR_BINARY:
            fputs("(", out);
            generate_expression_c(expr->data.binary.left, out);
            fprintf(out, " %s ", expr->data.binary.op);
            generate_expression_c(expr->data.binary.right, out);
            fputs(")", out);
            break;

        case EXPR_UNARY:
            fprintf(out, "(%s", expr->data.unary.op);
            generate_expression_c(expr->data.unary.operand, out);
            fputs(")", out);
            break;

        case EXPR_FUNCTION_CALL: {
            ArgumentList *argument = expr->data.call.arguments;
            int first = 1;

            fprintf(out, "%s(", expr->data.call.name);
            while (argument != NULL) {
                if (!first) {
                    fputs(", ", out);
                }
                generate_expression_c(argument->expr, out);
                first = 0;
                argument = argument->next;
            }
            fputs(")", out);
            break;
        }

        default:
            fputs("0", out);
            break;
    }
}

static void generate_statement_node_c(StmtNode *stmt, FILE *out, int indent_level) {
    if (stmt == NULL) {
        return;
    }

    switch (stmt->kind) {
        case STMT_DECLARATION:
            print_indent(out, indent_level);
            fprintf(out, "%s %s", c_type_name(stmt->data.declaration.declared_type),
                    stmt->data.declaration.name);
            if (stmt->data.declaration.initializer != NULL) {
                fputs(" = ", out);
                generate_expression_c(stmt->data.declaration.initializer, out);
            }
            fputs(";\n", out);
            break;

        case STMT_ASSIGNMENT:
            print_indent(out, indent_level);
            fprintf(out, "%s = ", stmt->data.assignment.name);
            generate_expression_c(stmt->data.assignment.value, out);
            fputs(";\n", out);
            break;

        case STMT_READ:
            generate_read_c(stmt->data.read_stmt.name, stmt->data.read_stmt.declared_type, out, indent_level);
            break;

        case STMT_WRITE:
            generate_write_c(stmt->data.write_stmt.value, out, indent_level);
            break;

        case STMT_BLOCK:
            print_indent(out, indent_level);
            fputs("{\n", out);
            generate_statement_c(stmt->data.block.statements, out, indent_level + 1);
            print_indent(out, indent_level);
            fputs("}\n", out);
            break;

        case STMT_CHK:
            print_indent(out, indent_level);
            fputs("if (", out);
            generate_expression_c(stmt->data.chk_stmt.condition, out);
            fputs(")\n", out);

            if (stmt->data.chk_stmt.then_branch != NULL &&
                stmt->data.chk_stmt.then_branch->kind == STMT_BLOCK) {
                generate_statement_node_c(stmt->data.chk_stmt.then_branch, out, indent_level);
            } else {
                print_indent(out, indent_level);
                fputs("{\n", out);
                generate_statement_c(stmt->data.chk_stmt.then_branch, out, indent_level + 1);
                print_indent(out, indent_level);
                fputs("}\n", out);
            }

            if (stmt->data.chk_stmt.else_branch != NULL) {
                print_indent(out, indent_level);
                fputs("else\n", out);

                if (stmt->data.chk_stmt.else_branch->kind == STMT_BLOCK) {
                    generate_statement_node_c(stmt->data.chk_stmt.else_branch, out, indent_level);
                } else {
                    print_indent(out, indent_level);
                    fputs("{\n", out);
                    generate_statement_c(stmt->data.chk_stmt.else_branch, out, indent_level + 1);
                    print_indent(out, indent_level);
                    fputs("}\n", out);
                }
            }
            break;

        case STMT_REPEAT:
            print_indent(out, indent_level);
            fputs("do\n", out);

            if (stmt->data.repeat_stmt.body != NULL &&
                stmt->data.repeat_stmt.body->kind == STMT_BLOCK) {
                generate_statement_node_c(stmt->data.repeat_stmt.body, out, indent_level);
            } else {
                print_indent(out, indent_level);
                fputs("{\n", out);
                generate_statement_c(stmt->data.repeat_stmt.body, out, indent_level + 1);
                print_indent(out, indent_level);
                fputs("}\n", out);
            }

            print_indent(out, indent_level);
            fputs("while (!(", out);
            generate_expression_c(stmt->data.repeat_stmt.condition, out);
            fputs("));\n", out);
            break;

        case STMT_FUNCTION_DEF: {
            ParameterList *parameter = stmt->data.function_def.parameters;
            int first = 1;

            print_indent(out, indent_level);
            fprintf(out, "%s %s(", c_type_name(stmt->data.function_def.return_type),
                    stmt->data.function_def.name);
            while (parameter != NULL) {
                if (!first) {
                    fputs(", ", out);
                }
                fprintf(out, "%s %s", c_type_name(parameter->type), parameter->name);
                first = 0;
                parameter = parameter->next;
            }
            fputs(")\n", out);

            if (stmt->data.function_def.body != NULL &&
                stmt->data.function_def.body->kind == STMT_BLOCK) {
                generate_statement_node_c(stmt->data.function_def.body, out, indent_level);
            } else {
                print_indent(out, indent_level);
                fputs("{\n", out);
                generate_statement_c(stmt->data.function_def.body, out, indent_level + 1);
                print_indent(out, indent_level);
                fputs("}\n", out);
            }
            break;
        }

        case STMT_RETURN:
            print_indent(out, indent_level);
            fputs("return ", out);
            generate_expression_c(stmt->data.return_stmt.value, out);
            fputs(";\n", out);
            break;

        case STMT_SKIP:
            print_indent(out, indent_level);
            fputs(";\n", out);
            break;

        case STMT_STOP:
            print_indent(out, indent_level);
            fputs("return 0;\n", out);
            break;

        case STMT_DECIDE:
            generate_decide_c(stmt, out, indent_level);
            break;

        default:
            break;
    }
}

void generate_statement_c(StmtNode *stmt, FILE *out, int indent_level) {
    while (stmt != NULL) {
        generate_statement_node_c(stmt, out, indent_level);
        stmt = stmt->next;
    }
}

void generate_program_c(Program *program, FILE *out) {
    StmtNode *stmt;

    if (program == NULL || out == NULL) {
        return;
    }

    fputs("#include <stdio.h>\n", out);
    fputs("\n", out);

    stmt = program->statements;
    while (stmt != NULL) {
        if (stmt->kind == STMT_FUNCTION_DEF) {
            generate_statement_node_c(stmt, out, 0);
            fputs("\n", out);
        }
        stmt = stmt->next;
    }

    fputs("int main(void)\n", out);
    fputs("{\n", out);

    stmt = program->statements;
    while (stmt != NULL) {
        if (stmt->kind != STMT_FUNCTION_DEF) {
            generate_statement_node_c(stmt, out, 1);
        }
        stmt = stmt->next;
    }

    print_indent(out, 1);
    fputs("return 0;\n", out);
    fputs("}\n", out);
}

void generate_c_code(Program *program, FILE *out) {
    generate_program_c(program, out);
}
