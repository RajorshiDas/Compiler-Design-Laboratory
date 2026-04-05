#include <stdio.h>
#include <string.h>

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
        case TYPE_BIGREAL:
            return "double";
        case TYPE_CHAR:
            return "char";
        case TYPE_LOGIC:
            return "int";
        case TYPE_TEXT:
            return "char *";
        case TYPE_EMPTY:
            return "void";
        default:
            return "int";
    }
}

static const char *printf_format(SymbolType type) {
    switch (type) {
        case TYPE_NUM:
            return "%lld";
        case TYPE_REAL:
        case TYPE_BIGREAL:
            return "%g";
        case TYPE_CHAR:
            return "%c";
        case TYPE_TEXT:
            return "%s";
        case TYPE_LOGIC:
            return "%d";
        default:
            return "%d";
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

static const char *c_function_name(const char *name) {
    if (strcmp(name, "power") == 0) {
        return "pow";
    }
    if (strcmp(name, "squart") == 0) {
        return "sqrt";
    }
    if (strcmp(name, "upper") == 0) {
        return "floor";
    }
    if (strcmp(name, "lower") == 0) {
        return "ceil";
    }
    return name;
}

static void emit_function_signature(const StmtNode *stmt, FILE *out) {
    ParameterList *parameter;
    int first;

    if (stmt == NULL || stmt->kind != STMT_FUNCTION_DEF) {
        return;
    }

    parameter = stmt->data.function_def.parameters;
    first = 1;

    fprintf(out, "%s %s(",
            c_type_name(stmt->data.function_def.return_type),
            stmt->data.function_def.name);
    while (parameter != NULL) {
        if (!first) {
            fputs(", ", out);
        }
        fprintf(out, "%s %s", c_type_name(parameter->type), parameter->name);
        first = 0;
        parameter = parameter->next;
    }
    fputs(")", out);
}

static void emit_function_prototypes(const StmtNode *stmt, FILE *out) {
    while (stmt != NULL) {
        if (stmt->kind == STMT_FUNCTION_DEF) {
            emit_function_signature(stmt, out);
            fputs(";\n", out);
            emit_function_prototypes(stmt->data.function_def.body, out);
        } else if (stmt->kind == STMT_BLOCK) {
            emit_function_prototypes(stmt->data.block.statements, out);
        } else if (stmt->kind == STMT_CHK) {
            emit_function_prototypes(stmt->data.chk_stmt.then_branch, out);
            emit_function_prototypes(stmt->data.chk_stmt.else_branch, out);
        } else if (stmt->kind == STMT_REPEAT) {
            emit_function_prototypes(stmt->data.repeat_stmt.body, out);
        } else if (stmt->kind == STMT_UNTIL) {
            emit_function_prototypes(stmt->data.until_stmt.body, out);
        } else if (stmt->kind == STMT_DOING) {
            emit_function_prototypes(stmt->data.doing_stmt.body, out);
        } else if (stmt->kind == STMT_DECIDE) {
            CaseNode *case_node = stmt->data.decide_stmt.cases;

            while (case_node != NULL) {
                emit_function_prototypes(case_node->body, out);
                case_node = case_node->next;
            }

            emit_function_prototypes(stmt->data.decide_stmt.otherwise_branch, out);
        }

        stmt = stmt->next;
    }
}

static void generate_statement_node_c(StmtNode *stmt, FILE *out, int indent_level);

static void generate_write_c(ExprList *values, FILE *out, int indent_level) {
    while (values != NULL) {
        SymbolType type = TYPE_NUM;

        if (values->expr != NULL) {
            type = values->expr->value_type;
        }

        print_indent(out, indent_level);
        fprintf(out, "printf(\"%s\", ", printf_format(type));
        generate_expression_c(values->expr, out);
        fputs(");\n", out);
        values = values->next;
    }

    print_indent(out, indent_level);
    fputs("printf(\"\\n\");\n", out);
}

static void generate_read_c(const char *name, SymbolType type, FILE *out, int indent_level) {
    print_indent(out, indent_level);
    if (type == TYPE_TEXT) {
        fprintf(out, "scanf(\"%s\", %s);\n", scanf_format(type), name);
    } else {
        fprintf(out, "scanf(\"%s\", &%s);\n", scanf_format(type), name);
    }
}

static void emit_statement_body(StmtNode *stmt, FILE *out, int indent_level) {
    if (stmt != NULL && stmt->kind == STMT_BLOCK) {
        generate_statement_node_c(stmt, out, indent_level);
        return;
    }

    print_indent(out, indent_level);
    fputs("{\n", out);
    generate_statement_c(stmt, out, indent_level + 1);
    print_indent(out, indent_level);
    fputs("}\n", out);
}

static void generate_decide_c(StmtNode *stmt, FILE *out, int indent_level) {
    CaseNode *case_node = stmt->data.decide_stmt.cases;
    int first = 1;

    while (case_node != NULL) {
        print_indent(out, indent_level);
        fprintf(out, "%sif (", first ? "" : "else ");
        generate_expression_c(stmt->data.decide_stmt.selector, out);
        fputs(" == ", out);
        generate_expression_c(case_node->condition, out);
        fputs(")\n", out);
        emit_statement_body(case_node->body, out, indent_level);
        first = 0;
        case_node = case_node->next;
    }

    if (stmt->data.decide_stmt.otherwise_branch != NULL) {
        print_indent(out, indent_level);
        fputs("else\n", out);
        emit_statement_body(stmt->data.decide_stmt.otherwise_branch, out, indent_level);
    }
}

void generate_expression_c(ExprNode *expr, FILE *out) {
    ArgumentList *argument;
    int first;

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

        case EXPR_CHAR_LITERAL:
            fprintf(out, "'%c'", expr->data.char_value);
            break;

        case EXPR_BOOL_LITERAL:
            fprintf(out, "%d", expr->data.bool_value ? 1 : 0);
            break;

        case EXPR_VARIABLE:
            fprintf(out, "%s", expr->data.identifier);
            break;

        case EXPR_BINARY:
            fputs("(", out);
            generate_expression_c(expr->data.binary.left, out);
            if (strcmp(expr->data.binary.op, "AND") == 0) {
                fputs(" && ", out);
            } else if (strcmp(expr->data.binary.op, "OR") == 0) {
                fputs(" || ", out);
            } else if (strcmp(expr->data.binary.op, "XOR") == 0) {
                fputs(" ^ ", out);
            } else {
                fprintf(out, " %s ", expr->data.binary.op);
            }
            generate_expression_c(expr->data.binary.right, out);
            fputs(")", out);
            break;

        case EXPR_UNARY:
            if (strcmp(expr->data.unary.op, "ABS") == 0) {
                fputs("(((", out);
                generate_expression_c(expr->data.unary.operand, out);
                fputs(") < 0) ? -(", out);
                generate_expression_c(expr->data.unary.operand, out);
                fputs(") : (", out);
                generate_expression_c(expr->data.unary.operand, out);
                fputs("))", out);
            } else {
                fputs("(", out);
                fprintf(out, "%s", expr->data.unary.op);
                generate_expression_c(expr->data.unary.operand, out);
                fputs(")", out);
            }
            break;

        case EXPR_FUNCTION_CALL:
            argument = expr->data.call.arguments;
            first = 1;

            fprintf(out, "%s(", c_function_name(expr->data.call.name));
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
            generate_write_c(stmt->data.write_stmt.values, out, indent_level);
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
            emit_statement_body(stmt->data.chk_stmt.then_branch, out, indent_level);
            if (stmt->data.chk_stmt.else_branch != NULL) {
                print_indent(out, indent_level);
                fputs("else\n", out);
                emit_statement_body(stmt->data.chk_stmt.else_branch, out, indent_level);
            }
            break;

        case STMT_REPEAT:
            print_indent(out, indent_level);
            fprintf(out, "for (; ");
            generate_expression_c(stmt->data.repeat_stmt.condition, out);
            fprintf(out, "; %s = ", stmt->data.repeat_stmt.iterator);
            generate_expression_c(stmt->data.repeat_stmt.update, out);
            fputs(")\n", out);
            emit_statement_body(stmt->data.repeat_stmt.body, out, indent_level);
            break;

        case STMT_UNTIL:
            print_indent(out, indent_level);
            fputs("while (!(", out);
            generate_expression_c(stmt->data.until_stmt.condition, out);
            fputs("))\n", out);
            emit_statement_body(stmt->data.until_stmt.body, out, indent_level);
            break;

        case STMT_DOING:
            print_indent(out, indent_level);
            fputs("do\n", out);
            emit_statement_body(stmt->data.doing_stmt.body, out, indent_level);
            print_indent(out, indent_level);
            fputs("while (!(", out);
            generate_expression_c(stmt->data.doing_stmt.condition, out);
            fputs("));\n", out);
            break;

        case STMT_DECIDE:
            generate_decide_c(stmt, out, indent_level);
            break;

        case STMT_FUNCTION_DEF:
            print_indent(out, indent_level);
            emit_function_signature(stmt, out);
            fputs("\n", out);
            emit_statement_body(stmt->data.function_def.body, out, indent_level);
            break;

        case STMT_SKIP:
            print_indent(out, indent_level);
            fputs("continue;\n", out);
            break;

        case STMT_STOP:
            print_indent(out, indent_level);
            fputs("break;\n", out);
            break;

        case STMT_RETURN:
            print_indent(out, indent_level);
            fputs("return ", out);
            generate_expression_c(stmt->data.return_stmt.value, out);
            fputs(";\n", out);
            break;

        default:
            break;
    }
}

void generate_statement_c(StmtNode *stmt, FILE *out, int indent_level) {
    while (stmt != NULL) {
        if (stmt->kind != STMT_FUNCTION_DEF) {
            generate_statement_node_c(stmt, out, indent_level);
        }
        stmt = stmt->next;
    }
}

static void emit_function_definitions(const StmtNode *stmt, FILE *out) {
    while (stmt != NULL) {
        if (stmt->kind == STMT_FUNCTION_DEF) {
            generate_statement_node_c((StmtNode *)stmt, out, 0);
            fputs("\n", out);
            emit_function_definitions(stmt->data.function_def.body, out);
        } else if (stmt->kind == STMT_BLOCK) {
            emit_function_definitions(stmt->data.block.statements, out);
        } else if (stmt->kind == STMT_CHK) {
            emit_function_definitions(stmt->data.chk_stmt.then_branch, out);
            emit_function_definitions(stmt->data.chk_stmt.else_branch, out);
        } else if (stmt->kind == STMT_REPEAT) {
            emit_function_definitions(stmt->data.repeat_stmt.body, out);
        } else if (stmt->kind == STMT_UNTIL) {
            emit_function_definitions(stmt->data.until_stmt.body, out);
        } else if (stmt->kind == STMT_DOING) {
            emit_function_definitions(stmt->data.doing_stmt.body, out);
        } else if (stmt->kind == STMT_DECIDE) {
            CaseNode *case_node = stmt->data.decide_stmt.cases;

            while (case_node != NULL) {
                emit_function_definitions(case_node->body, out);
                case_node = case_node->next;
            }

            emit_function_definitions(stmt->data.decide_stmt.otherwise_branch, out);
        }

        stmt = stmt->next;
    }
}

void generate_program_c(Program *program, FILE *out) {
    if (program == NULL || out == NULL) {
        return;
    }

    fputs("#include <stdio.h>\n", out);
    fputs("#include <math.h>\n\n", out);

    emit_function_prototypes(program->statements, out);
    fputs("\n", out);
    emit_function_definitions(program->statements, out);

    fputs("int main(void)\n", out);
    fputs("{\n", out);
    generate_statement_c(program->statements, out, 1);
    print_indent(out, 1);
    fputs("return 0;\n", out);
    fputs("}\n", out);
}

void generate_c_code(Program *program, FILE *out) {
    generate_program_c(program, out);
}




