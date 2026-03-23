#include <stdlib.h>
#include <string.h>

#include "optimize.h"

static int is_numeric_literal(const ExprNode *expr) {
    return expr != NULL &&
           (expr->kind == EXPR_INT_LITERAL || expr->kind == EXPR_FLOAT_LITERAL);
}

static double literal_as_double(const ExprNode *expr) {
    if (expr->kind == EXPR_INT_LITERAL) {
        return (double)expr->data.int_value;
    }

    return expr->data.float_value;
}

static ExprNode *make_folded_int(long long value, SymbolType type) {
    ExprNode *expr = create_int_literal_expr(value);

    if (expr != NULL) {
        expr->value_type = type;
    }

    return expr;
}

static ExprNode *make_folded_float(double value, SymbolType type) {
    ExprNode *expr = create_float_literal_expr(value);

    if (expr != NULL) {
        expr->value_type = type;
    }

    return expr;
}

static ExprNode *replace_with_new_expr(ExprNode *old_expr, ExprNode *new_expr) {
    if (new_expr == NULL) {
        return old_expr;
    }

    free_expr(old_expr);
    return new_expr;
}

static ExprNode *replace_binary_with_child(ExprNode *expr, int keep_left) {
    ExprNode *kept_child;
    ExprNode *removed_child;

    if (expr == NULL || expr->kind != EXPR_BINARY) {
        return expr;
    }

    kept_child = keep_left ? expr->data.binary.left : expr->data.binary.right;
    removed_child = keep_left ? expr->data.binary.right : expr->data.binary.left;

    if (keep_left) {
        expr->data.binary.left = NULL;
        expr->data.binary.right = NULL;
    } else {
        expr->data.binary.left = NULL;
        expr->data.binary.right = NULL;
    }

    free_expr(removed_child);
    free(expr);
    return kept_child;
}

static int is_zero_literal(const ExprNode *expr) {
    return is_numeric_literal(expr) && literal_as_double(expr) == 0.0;
}

static int is_one_literal(const ExprNode *expr) {
    return is_numeric_literal(expr) && literal_as_double(expr) == 1.0;
}

static ExprNode *optimize_expr(ExprNode *expr);

static void optimize_argument_list(ArgumentList *arguments) {
    while (arguments != NULL) {
        arguments->expr = optimize_expr(arguments->expr);
        arguments = arguments->next;
    }
}

static void optimize_expr_list(ExprList *values) {
    while (values != NULL) {
        values->expr = optimize_expr(values->expr);
        values = values->next;
    }
}

static ExprNode *fold_binary_literals(ExprNode *expr) {
    ExprNode *left = expr->data.binary.left;
    ExprNode *right = expr->data.binary.right;
    double left_value;
    double right_value;
    SymbolType result_type = expr->value_type;

    if (!is_numeric_literal(left) || !is_numeric_literal(right)) {
        return expr;
    }

    left_value = literal_as_double(left);
    right_value = literal_as_double(right);

    if (strcmp(expr->data.binary.op, "+") == 0) {
        if (result_type == TYPE_NUM) {
            return replace_with_new_expr(expr, make_folded_int((long long)(left_value + right_value), result_type));
        }
        return replace_with_new_expr(expr, make_folded_float(left_value + right_value, result_type));
    }

    if (strcmp(expr->data.binary.op, "-") == 0) {
        if (result_type == TYPE_NUM) {
            return replace_with_new_expr(expr, make_folded_int((long long)(left_value - right_value), result_type));
        }
        return replace_with_new_expr(expr, make_folded_float(left_value - right_value, result_type));
    }

    if (strcmp(expr->data.binary.op, "*") == 0) {
        if (result_type == TYPE_NUM) {
            return replace_with_new_expr(expr, make_folded_int((long long)(left_value * right_value), result_type));
        }
        return replace_with_new_expr(expr, make_folded_float(left_value * right_value, result_type));
    }

    if (strcmp(expr->data.binary.op, "/") == 0 && right_value != 0.0) {
        if (result_type == TYPE_NUM) {
            return replace_with_new_expr(expr, make_folded_int((long long)(left_value / right_value), result_type));
        }
        return replace_with_new_expr(expr, make_folded_float(left_value / right_value, result_type));
    }

    if (strcmp(expr->data.binary.op, "==") == 0) {
        return replace_with_new_expr(expr, make_folded_int(left_value == right_value, TYPE_LOGIC));
    }

    if (strcmp(expr->data.binary.op, "!=") == 0) {
        return replace_with_new_expr(expr, make_folded_int(left_value != right_value, TYPE_LOGIC));
    }

    if (strcmp(expr->data.binary.op, "<") == 0) {
        return replace_with_new_expr(expr, make_folded_int(left_value < right_value, TYPE_LOGIC));
    }

    if (strcmp(expr->data.binary.op, ">") == 0) {
        return replace_with_new_expr(expr, make_folded_int(left_value > right_value, TYPE_LOGIC));
    }

    if (strcmp(expr->data.binary.op, "<=") == 0) {
        return replace_with_new_expr(expr, make_folded_int(left_value <= right_value, TYPE_LOGIC));
    }

    if (strcmp(expr->data.binary.op, ">=") == 0) {
        return replace_with_new_expr(expr, make_folded_int(left_value >= right_value, TYPE_LOGIC));
    }

    return expr;
}

static ExprNode *simplify_algebraic_identity(ExprNode *expr) {
    ExprNode *left = expr->data.binary.left;
    ExprNode *right = expr->data.binary.right;
    const char *op = expr->data.binary.op;

    if (strcmp(op, "+") == 0) {
        if (is_zero_literal(right)) {
            return replace_binary_with_child(expr, 1);
        }
        if (is_zero_literal(left)) {
            return replace_binary_with_child(expr, 0);
        }
    }

    if (strcmp(op, "-") == 0 && is_zero_literal(right)) {
        return replace_binary_with_child(expr, 1);
    }

    if (strcmp(op, "*") == 0) {
        if (is_one_literal(right)) {
            return replace_binary_with_child(expr, 1);
        }
        if (is_one_literal(left)) {
            return replace_binary_with_child(expr, 0);
        }
        if (is_zero_literal(left) || is_zero_literal(right)) {
            return replace_with_new_expr(expr, make_folded_int(0, expr->value_type));
        }
    }

    if (strcmp(op, "/") == 0 && is_one_literal(right)) {
        return replace_binary_with_child(expr, 1);
    }

    return expr;
}

static ExprNode *optimize_expr(ExprNode *expr) {
    if (expr == NULL) {
        return NULL;
    }

    switch (expr->kind) {
        case EXPR_BINARY:
            expr->data.binary.left = optimize_expr(expr->data.binary.left);
            expr->data.binary.right = optimize_expr(expr->data.binary.right);
            expr = fold_binary_literals(expr);
            if (expr != NULL && expr->kind == EXPR_BINARY) {
                expr = simplify_algebraic_identity(expr);
            }
            return expr;

        case EXPR_UNARY:
            expr->data.unary.operand = optimize_expr(expr->data.unary.operand);
            if (strcmp(expr->data.unary.op, "-") == 0 &&
                is_numeric_literal(expr->data.unary.operand)) {
                if (expr->data.unary.operand->kind == EXPR_INT_LITERAL) {
                    return replace_with_new_expr(
                        expr,
                        make_folded_int(-expr->data.unary.operand->data.int_value, expr->value_type));
                }

                return replace_with_new_expr(
                    expr,
                    make_folded_float(-expr->data.unary.operand->data.float_value, expr->value_type));
            }
            return expr;

        case EXPR_FUNCTION_CALL:
            optimize_argument_list(expr->data.call.arguments);
            return expr;

        default:
            return expr;
    }
}

static void optimize_case_list(CaseNode *cases);

static void optimize_statement_list(StmtNode *stmt) {
    while (stmt != NULL) {
        switch (stmt->kind) {
            case STMT_DECLARATION:
                stmt->data.declaration.initializer = optimize_expr(stmt->data.declaration.initializer);
                break;

            case STMT_ASSIGNMENT:
                stmt->data.assignment.value = optimize_expr(stmt->data.assignment.value);
                break;

            case STMT_WRITE:
                optimize_expr_list(stmt->data.write_stmt.values);
                break;

            case STMT_BLOCK:
                optimize_statement_list(stmt->data.block.statements);
                break;

            case STMT_CHK:
                stmt->data.chk_stmt.condition = optimize_expr(stmt->data.chk_stmt.condition);
                optimize_statement_list(stmt->data.chk_stmt.then_branch);
                optimize_statement_list(stmt->data.chk_stmt.else_branch);
                break;

            case STMT_REPEAT:
                optimize_statement_list(stmt->data.repeat_stmt.body);
                stmt->data.repeat_stmt.condition = optimize_expr(stmt->data.repeat_stmt.condition);
                stmt->data.repeat_stmt.update = optimize_expr(stmt->data.repeat_stmt.update);
                break;

            case STMT_UNTIL:
                stmt->data.until_stmt.condition = optimize_expr(stmt->data.until_stmt.condition);
                optimize_statement_list(stmt->data.until_stmt.body);
                break;

            case STMT_DOING:
                optimize_statement_list(stmt->data.doing_stmt.body);
                stmt->data.doing_stmt.condition = optimize_expr(stmt->data.doing_stmt.condition);
                break;

            case STMT_DECIDE:
                stmt->data.decide_stmt.selector = optimize_expr(stmt->data.decide_stmt.selector);
                optimize_case_list(stmt->data.decide_stmt.cases);
                optimize_statement_list(stmt->data.decide_stmt.otherwise_branch);
                break;

            case STMT_FUNCTION_DEF:
                optimize_statement_list(stmt->data.function_def.body);
                break;

            case STMT_RETURN:
                stmt->data.return_stmt.value = optimize_expr(stmt->data.return_stmt.value);
                break;

            default:
                break;
        }

        stmt = stmt->next;
    }
}

static void optimize_case_list(CaseNode *cases) {
    while (cases != NULL) {
        cases->condition = optimize_expr(cases->condition);
        optimize_statement_list(cases->body);
        cases = cases->next;
    }
}

void optimize_program(Program *program) {
    if (program == NULL) {
        return;
    }

    optimize_statement_list(program->statements);
}
