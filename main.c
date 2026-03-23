#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "interpreter.h"
#include "symtab.h"

extern FILE *yyin;
extern Program *parsed_program;
int yyparse(void);
int get_semantic_error_count(void);

static void print_indent(int level) {
    int i;

    for (i = 0; i < level; ++i) {
        printf("  ");
    }
}

static void print_expression(const ExprNode *expr, int indent);

static void print_statement_list(const StmtNode *stmt, int indent) {
    while (stmt != NULL) {
        switch (stmt->kind) {
            case STMT_DECLARATION:
                print_indent(indent);
                printf("Declaration: %s (%s)\n",
                       stmt->data.declaration.name,
                       symbol_type_name(stmt->data.declaration.declared_type));
                if (stmt->data.declaration.initializer != NULL) {
                    print_indent(indent + 1);
                    printf("Initializer:\n");
                    print_expression(stmt->data.declaration.initializer, indent + 2);
                }
                break;

            case STMT_ASSIGNMENT:
                print_indent(indent);
                printf("Assignment: %s\n", stmt->data.assignment.name);
                print_expression(stmt->data.assignment.value, indent + 1);
                break;

            case STMT_READ:
                print_indent(indent);
                printf("Read: %s\n", stmt->data.read_stmt.name);
                break;

            case STMT_WRITE:
                print_indent(indent);
                printf("Write:\n");
                print_expression(stmt->data.write_stmt.value, indent + 1);
                break;

            case STMT_BLOCK:
                print_indent(indent);
                printf("Block:\n");
                print_statement_list(stmt->data.block.statements, indent + 1);
                break;

            case STMT_CHK:
                print_indent(indent);
                printf("If:\n");
                print_indent(indent + 1);
                printf("Condition:\n");
                print_expression(stmt->data.chk_stmt.condition, indent + 2);
                print_indent(indent + 1);
                printf("Then:\n");
                print_statement_list(stmt->data.chk_stmt.then_branch, indent + 2);
                if (stmt->data.chk_stmt.else_branch != NULL) {
                    print_indent(indent + 1);
                    printf("Else:\n");
                    print_statement_list(stmt->data.chk_stmt.else_branch, indent + 2);
                }
                break;

            case STMT_REPEAT:
                print_indent(indent);
                printf("Repeat:\n");
                print_indent(indent + 1);
                printf("Body:\n");
                print_statement_list(stmt->data.repeat_stmt.body, indent + 2);
                print_indent(indent + 1);
                printf("Until:\n");
                print_expression(stmt->data.repeat_stmt.condition, indent + 2);
                break;

            case STMT_DECIDE:
                print_indent(indent);
                printf("Decide\n");
                break;

            case STMT_FUNCTION_DEF:
                print_indent(indent);
                printf("Function: %s\n", stmt->data.function_def.name);
                break;

            case STMT_SKIP:
                print_indent(indent);
                printf("Skip\n");
                break;

            case STMT_STOP:
                print_indent(indent);
                printf("Stop\n");
                break;

            case STMT_RETURN:
                print_indent(indent);
                printf("Return:\n");
                print_expression(stmt->data.return_stmt.value, indent + 1);
                break;

            default:
                print_indent(indent);
                printf("Unknown statement\n");
                break;
        }

        stmt = stmt->next;
    }
}

static void print_expression(const ExprNode *expr, int indent) {
    if (expr == NULL) {
        print_indent(indent);
        printf("(null)\n");
        return;
    }

    switch (expr->kind) {
        case EXPR_INT_LITERAL:
            print_indent(indent);
            printf("IntLiteral: %lld\n", expr->data.int_value);
            break;

        case EXPR_FLOAT_LITERAL:
            print_indent(indent);
            printf("FloatLiteral: %g\n", expr->data.float_value);
            break;

        case EXPR_STRING_LITERAL:
            print_indent(indent);
            printf("StringLiteral: \"%s\"\n", expr->data.string_value);
            break;

        case EXPR_VARIABLE:
            print_indent(indent);
            printf("Variable: %s\n", expr->data.identifier);
            break;

        case EXPR_BINARY:
            print_indent(indent);
            printf("BinaryExpr: %s\n", expr->data.binary.op);
            print_expression(expr->data.binary.left, indent + 1);
            print_expression(expr->data.binary.right, indent + 1);
            break;

        case EXPR_UNARY:
            print_indent(indent);
            printf("UnaryExpr: %s\n", expr->data.unary.op);
            print_expression(expr->data.unary.operand, indent + 1);
            break;

        case EXPR_FUNCTION_CALL:
            print_indent(indent);
            printf("FunctionCall: %s\n", expr->data.call.name);
            break;

        default:
            print_indent(indent);
            printf("Unknown expression\n");
            break;
    }
}

static void print_ast(const Program *program) {
    printf("\nAST:\n");
    if (program == NULL) {
        printf("(null)\n");
        return;
    }

    print_statement_list(program->statements, 0);
}

int main(int argc, char *argv[]) {
    int parse_status;
    int runtime_errors = 0;

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            perror("Error opening input file");
            return 1;
        }
    } else {
        yyin = stdin;
    }

    printf("Starting parsing...\n");
    parse_status = yyparse();

    if (parse_status == 0 && get_semantic_error_count() == 0 && parsed_program != NULL) {
        print_ast(parsed_program);
        runtime_errors = execute_program(parsed_program);

        if (runtime_errors == 0) {
            printf("Parsing, semantic analysis, and interpretation completed successfully.\n");
        } else {
            printf("Interpretation completed with %d runtime error(s).\n", runtime_errors);
        }
    } else {
        printf("Parsing completed with %d semantic error(s).\n", get_semantic_error_count());
    }

    print_symbol_table();
    free_program(parsed_program);

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    return (parse_status == 0 && get_semantic_error_count() == 0 && runtime_errors == 0) ? 0 : 1;
}
