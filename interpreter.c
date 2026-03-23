#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "symtab.h"

typedef struct FunctionEntry {
    const StmtNode *definition;
    struct FunctionEntry *next;
} FunctionEntry;

static int runtime_error_count = 0;
static int stop_requested = 0;
static int return_requested = 0;
static int function_call_depth = 0;
static ExprResult return_value = { TYPE_INVALID, 0, {0} };
static FunctionEntry *function_table = NULL;

static ExprResult copy_expr_result(const ExprResult *value);
static void collect_functions(const StmtNode *node);
static const StmtNode *find_function(const char *name);
static int count_arguments(const ArgumentList *arguments);
static void free_function_table(void);
static ExprResult execute_function_call(ExprNode *node);

static void report_runtime_error(const char *message) {
    fprintf(stderr, "Runtime error: %s\n", message);
    ++runtime_error_count;
}

static char *copy_text(const char *text) {
    size_t length;
    char *copy;

    if (text == NULL) {
        text = "";
    }

    length = strlen(text);
    copy = (char *)malloc(length + 1);
    if (copy == NULL) {
        fprintf(stderr, "Runtime error: out of memory.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(copy, text);
    return copy;
}

static ExprResult make_invalid_result(void) {
    ExprResult result;

    result.type = TYPE_INVALID;
    result.has_value = 0;
    result.data.text_value = NULL;
    return result;
}

static ExprResult make_num_result(long long value) {
    ExprResult result = make_invalid_result();

    result.type = TYPE_NUM;
    result.has_value = 1;
    result.data.num_value = value;
    return result;
}

static ExprResult make_real_result(double value) {
    ExprResult result = make_invalid_result();

    result.type = TYPE_REAL;
    result.has_value = 1;
    result.data.real_value = value;
    return result;
}

static ExprResult make_bigreal_result(double value) {
    ExprResult result = make_invalid_result();

    result.type = TYPE_BIGREAL;
    result.has_value = 1;
    result.data.bigreal_value = value;
    return result;
}

static ExprResult make_logic_result(int value) {
    ExprResult result = make_invalid_result();

    result.type = TYPE_LOGIC;
    result.has_value = 1;
    result.data.logic_value = value ? 1 : 0;
    return result;
}

static ExprResult make_text_result(const char *value) {
    ExprResult result = make_invalid_result();

    result.type = TYPE_TEXT;
    result.has_value = 1;
    result.data.text_value = copy_text(value);
    return result;
}

static ExprResult copy_expr_result(const ExprResult *value) {
    ExprResult result = make_invalid_result();

    if (value == NULL || !value->has_value) {
        return result;
    }

    result.type = value->type;
    result.has_value = 1;

    switch (value->type) {
        case TYPE_NUM:
            result.data.num_value = value->data.num_value;
            break;
        case TYPE_REAL:
            result.data.real_value = value->data.real_value;
            break;
        case TYPE_BIGREAL:
            result.data.bigreal_value = value->data.bigreal_value;
            break;
        case TYPE_CHAR:
            result.data.chr_value = value->data.chr_value;
            break;
        case TYPE_LOGIC:
            result.data.logic_value = value->data.logic_value;
            break;
        case TYPE_TEXT:
            result.data.text_value = copy_text(value->data.text_value);
            break;
        default:
            result.has_value = 0;
            break;
    }

    return result;
}

static int is_numeric_type(DataType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static double expr_as_double(const ExprResult *value) {
    switch (value->type) {
        case TYPE_NUM:
            return (double)value->data.num_value;
        case TYPE_REAL:
            return value->data.real_value;
        case TYPE_BIGREAL:
            return value->data.bigreal_value;
        case TYPE_LOGIC:
            return (double)value->data.logic_value;
        case TYPE_CHAR:
            return (double)value->data.chr_value;
        default:
            return 0.0;
    }
}

static ExprResult copy_runtime_value(const RuntimeValue *value) {
    ExprResult result = make_invalid_result();

    if (value == NULL || !value->is_initialized) {
        return result;
    }

    result.type = value->type;
    result.has_value = 1;

    switch (value->type) {
        case TYPE_NUM:
            result.data.num_value = value->data.num_value;
            break;
        case TYPE_REAL:
            result.data.real_value = value->data.real_value;
            break;
        case TYPE_BIGREAL:
            result.data.bigreal_value = value->data.bigreal_value;
            break;
        case TYPE_CHAR:
            result.data.chr_value = value->data.chr_value;
            break;
        case TYPE_LOGIC:
            result.data.logic_value = value->data.logic_value;
            break;
        case TYPE_TEXT:
            result.data.text_value = copy_text(value->data.text_value);
            break;
        default:
            result.has_value = 0;
            break;
    }

    return result;
}

static int values_equal(const ExprResult *left, const ExprResult *right) {
    if (!left->has_value || !right->has_value) {
        return 0;
    }

    if (is_numeric_type(left->type) && is_numeric_type(right->type)) {
        return expr_as_double(left) == expr_as_double(right);
    }

    if (left->type == TYPE_LOGIC && right->type == TYPE_LOGIC) {
        return left->data.logic_value == right->data.logic_value;
    }

    if (left->type == TYPE_CHAR && right->type == TYPE_CHAR) {
        return left->data.chr_value == right->data.chr_value;
    }

    if (left->type == TYPE_TEXT && right->type == TYPE_TEXT) {
        return strcmp(left->data.text_value != NULL ? left->data.text_value : "",
                      right->data.text_value != NULL ? right->data.text_value : "") == 0;
    }

    return 0;
}

static int result_is_true(const ExprResult *value) {
    if (value == NULL || !value->has_value) {
        return 0;
    }

    switch (value->type) {
        case TYPE_NUM:
            return value->data.num_value != 0;
        case TYPE_REAL:
            return value->data.real_value != 0.0;
        case TYPE_BIGREAL:
            return value->data.bigreal_value != 0.0;
        case TYPE_LOGIC:
            return value->data.logic_value != 0;
        case TYPE_CHAR:
            return value->data.chr_value != '\0';
        case TYPE_TEXT:
            return value->data.text_value != NULL && value->data.text_value[0] != '\0';
        default:
            return 0;
    }
}

static ExprResult evaluate_binary_expression(ExprNode *node) {
    ExprResult left;
    ExprResult right;
    ExprResult result = make_invalid_result();
    DataType promoted_type;
    const char *op;
    double left_value;
    double right_value;

    left = evaluate_expression(node->data.binary.left);
    right = evaluate_expression(node->data.binary.right);
    op = node->data.binary.op;

    if (!left.has_value || !right.has_value) {
        free_expr_result(&left);
        free_expr_result(&right);
        return result;
    }

    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
        strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        if (!is_numeric_type(left.type) || !is_numeric_type(right.type)) {
            report_runtime_error("arithmetic operators require numeric operands.");
            free_expr_result(&left);
            free_expr_result(&right);
            return result;
        }

        promoted_type = result_type(left.type, right.type);
        if (promoted_type == TYPE_ERROR) {
            free_expr_result(&left);
            free_expr_result(&right);
            return result;
        }

        if (promoted_type == TYPE_NUM) {
            long long left_num = left.data.num_value;
            long long right_num = right.data.num_value;

            if (strcmp(op, "+") == 0) {
                result = make_num_result(left_num + right_num);
            } else if (strcmp(op, "-") == 0) {
                result = make_num_result(left_num - right_num);
            } else if (strcmp(op, "*") == 0) {
                result = make_num_result(left_num * right_num);
            } else {
                if (right_num == 0) {
                    report_runtime_error("division by zero.");
                } else {
                    result = make_num_result(left_num / right_num);
                }
            }
        } else {
            left_value = expr_as_double(&left);
            right_value = expr_as_double(&right);

            if (strcmp(op, "/") == 0 && right_value == 0.0) {
                report_runtime_error("division by zero.");
            } else if (promoted_type == TYPE_BIGREAL) {
                if (strcmp(op, "+") == 0) {
                    result = make_bigreal_result(left_value + right_value);
                } else if (strcmp(op, "-") == 0) {
                    result = make_bigreal_result(left_value - right_value);
                } else if (strcmp(op, "*") == 0) {
                    result = make_bigreal_result(left_value * right_value);
                } else {
                    result = make_bigreal_result(left_value / right_value);
                }
            } else {
                if (strcmp(op, "+") == 0) {
                    result = make_real_result(left_value + right_value);
                } else if (strcmp(op, "-") == 0) {
                    result = make_real_result(left_value - right_value);
                } else if (strcmp(op, "*") == 0) {
                    result = make_real_result(left_value * right_value);
                } else {
                    result = make_real_result(left_value / right_value);
                }
            }
        }
    } else if (strcmp(op, "<") == 0 || strcmp(op, ">") == 0 ||
               strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0) {
        if (!is_numeric_type(left.type) || !is_numeric_type(right.type)) {
            report_runtime_error("relational operators require numeric operands.");
            free_expr_result(&left);
            free_expr_result(&right);
            return result;
        }

        left_value = expr_as_double(&left);
        right_value = expr_as_double(&right);

        if (strcmp(op, "<") == 0) {
            result = make_logic_result(left_value < right_value);
        } else if (strcmp(op, ">") == 0) {
            result = make_logic_result(left_value > right_value);
        } else if (strcmp(op, "<=") == 0) {
            result = make_logic_result(left_value <= right_value);
        } else {
            result = make_logic_result(left_value >= right_value);
        }
    } else if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) {
        result = make_logic_result(values_equal(&left, &right));
        if (strcmp(op, "!=") == 0) {
            result.data.logic_value = !result.data.logic_value;
        }
    } else {
        report_runtime_error("unsupported binary operator.");
    }

    free_expr_result(&left);
    free_expr_result(&right);
    return result;
}

static int execute_statement_list(StmtNode *node);

static void collect_functions(const StmtNode *node) {
    while (node != NULL) {
        if (node->kind == STMT_FUNCTION_DEF) {
            FunctionEntry *entry = (FunctionEntry *)malloc(sizeof(FunctionEntry));

            if (entry != NULL) {
                entry->definition = node;
                entry->next = function_table;
                function_table = entry;
            }
            collect_functions(node->data.function_def.body);
        } else if (node->kind == STMT_BLOCK) {
            collect_functions(node->data.block.statements);
        } else if (node->kind == STMT_CHK) {
            collect_functions(node->data.chk_stmt.then_branch);
            collect_functions(node->data.chk_stmt.else_branch);
        } else if (node->kind == STMT_REPEAT) {
            collect_functions(node->data.repeat_stmt.body);
        } else if (node->kind == STMT_DECIDE) {
            const CaseNode *case_node = node->data.decide_stmt.cases;

            while (case_node != NULL) {
                collect_functions(case_node->body);
                case_node = case_node->next;
            }

            collect_functions(node->data.decide_stmt.otherwise_branch);
        }

        node = node->next;
    }
}

static const StmtNode *find_function(const char *name) {
    FunctionEntry *entry = function_table;

    while (entry != NULL) {
        if (strcmp(entry->definition->data.function_def.name, name) == 0) {
            return entry->definition;
        }
        entry = entry->next;
    }

    return NULL;
}

static int count_arguments(const ArgumentList *arguments) {
    int count = 0;

    while (arguments != NULL) {
        ++count;
        arguments = arguments->next;
    }

    return count;
}

static void free_function_table(void) {
    FunctionEntry *entry = function_table;

    while (entry != NULL) {
        FunctionEntry *next = entry->next;
        free(entry);
        entry = next;
    }

    function_table = NULL;
}

static ExprResult execute_function_call(ExprNode *node) {
    const StmtNode *function_node;
    const ParameterList *parameter;
    const ArgumentList *argument;
    ExprResult result = make_invalid_result();
    ExprResult saved_return_value = copy_expr_result(&return_value);
    int saved_return_requested = return_requested;
    int scope_open = 0;
    int call_started = 0;

    function_node = find_function(node->data.call.name);
    if (function_node == NULL) {
        report_runtime_error("call to undefined function.");
        free_expr_result(&saved_return_value);
        return result;
    }

    if (parameter_count(function_node->data.function_def.parameters) !=
        count_arguments(node->data.call.arguments)) {
        report_runtime_error("wrong number of arguments in function call.");
        free_expr_result(&saved_return_value);
        return result;
    }

    enter_scope();
    scope_open = 1;

    parameter = function_node->data.function_def.parameters;
    argument = node->data.call.arguments;

    while (parameter != NULL && argument != NULL) {
        ExprResult argument_value = evaluate_expression(argument->expr);

        if (!argument_value.has_value) {
            free_expr_result(&argument_value);
            goto cleanup;
        }

        if (!insert_symbol(parameter->name, parameter->type) ||
            !set_symbol_value(parameter->name, &argument_value)) {
            report_runtime_error("failed to bind function parameter.");
            free_expr_result(&argument_value);
            goto cleanup;
        }

        free_expr_result(&argument_value);
        parameter = parameter->next;
        argument = argument->next;
    }

    function_call_depth++;
    call_started = 1;
    free_expr_result(&return_value);
    return_value = make_invalid_result();
    return_requested = 0;

    execute_statement((StmtNode *)function_node->data.function_def.body);

    if (return_requested) {
        result = copy_expr_result(&return_value);
    } else {
        report_runtime_error("function did not return a value.");
    }

cleanup:
    if (call_started) {
        --function_call_depth;
    }

    if (scope_open) {
        leave_scope();
    }

    free_expr_result(&return_value);
    return_value = saved_return_value;
    return_requested = saved_return_requested;
    return result;
}

ExprResult evaluate_expression(ExprNode *node) {
    RuntimeValue value;
    ExprResult result = make_invalid_result();

    if (node == NULL) {
        report_runtime_error("cannot evaluate a null expression.");
        return result;
    }

    switch (node->kind) {
        case EXPR_INT_LITERAL:
            return make_num_result(node->data.int_value);
        case EXPR_FLOAT_LITERAL:
            return make_real_result(node->data.float_value);
        case EXPR_STRING_LITERAL:
            return make_text_result(node->data.string_value);
        case EXPR_VARIABLE:
            if (get_symbol_value(node->data.identifier, &value) == -1) {
                report_runtime_error("use of undeclared variable.");
                return result;
            }

            if (!value.is_initialized) {
                free_runtime_value(&value);
                report_runtime_error("use of uninitialized variable.");
                return result;
            }

            result = copy_runtime_value(&value);
            free_runtime_value(&value);
            return result;
        case EXPR_BINARY:
            return evaluate_binary_expression(node);
        case EXPR_UNARY:
            result = evaluate_expression(node->data.unary.operand);
            if (!result.has_value) {
                return result;
            }

            if (strcmp(node->data.unary.op, "-") == 0) {
                if (!is_numeric_type(result.type)) {
                    report_runtime_error("unary minus requires a numeric operand.");
                    free_expr_result(&result);
                    return make_invalid_result();
                }

                if (result.type == TYPE_NUM) {
                    result.data.num_value = -result.data.num_value;
                } else if (result.type == TYPE_BIGREAL) {
                    result.data.bigreal_value = -result.data.bigreal_value;
                } else {
                    result.data.real_value = -result.data.real_value;
                }
                return result;
            }

            if (strcmp(node->data.unary.op, "+") == 0) {
                if (!is_numeric_type(result.type)) {
                    report_runtime_error("unary plus requires a numeric operand.");
                    free_expr_result(&result);
                    return make_invalid_result();
                }
                return result;
            }

            if (strcmp(node->data.unary.op, "!") == 0) {
                ExprResult logic_result = make_logic_result(!result_is_true(&result));
                free_expr_result(&result);
                return logic_result;
            }

            report_runtime_error("unsupported unary operator.");
            free_expr_result(&result);
            return make_invalid_result();
        case EXPR_FUNCTION_CALL:
            return execute_function_call(node);
        default:
            report_runtime_error("unknown expression kind.");
            return result;
    }
}

static void execute_declaration(StmtNode *node) {
    ExprResult value;

    if (!insert_symbol(node->data.declaration.name, node->data.declaration.declared_type)) {
        report_runtime_error("failed to declare variable.");
        return;
    }

    if (node->data.declaration.initializer == NULL) {
        return;
    }

    value = evaluate_expression(node->data.declaration.initializer);
    if (!value.has_value) {
        free_expr_result(&value);
        return;
    }

    if (!check_assignment(node->data.declaration.name, value.type) ||
        !set_symbol_value(node->data.declaration.name, &value)) {
        report_runtime_error("invalid initializer for declaration.");
    }

    free_expr_result(&value);
}

static void execute_assignment_statement(StmtNode *node) {
    ExprResult value;

    if (!is_declared(node->data.assignment.name)) {
        report_runtime_error("assignment to undeclared variable.");
        return;
    }

    value = evaluate_expression(node->data.assignment.value);
    if (!value.has_value) {
        free_expr_result(&value);
        return;
    }

    if (!check_assignment(node->data.assignment.name, value.type) ||
        !set_symbol_value(node->data.assignment.name, &value)) {
        report_runtime_error("invalid assignment.");
    }

    free_expr_result(&value);
}

static void execute_read_statement(StmtNode *node) {
    ExprResult value = make_invalid_result();
    char text_buffer[1024];
    double real_value;
    long long num_value;
    int logic_value;
    char char_value;

    if (!is_declared(node->data.read_stmt.name)) {
        report_runtime_error("read target is not declared.");
        return;
    }

    switch (node->data.read_stmt.declared_type) {
        case TYPE_NUM:
            if (scanf("%lld", &num_value) != 1) {
                report_runtime_error("failed to read numeric input.");
                return;
            }
            value = make_num_result(num_value);
            break;

        case TYPE_REAL:
            if (scanf("%lf", &real_value) != 1) {
                report_runtime_error("failed to read real input.");
                return;
            }
            value = make_real_result(real_value);
            break;

        case TYPE_BIGREAL:
            if (scanf("%lf", &real_value) != 1) {
                report_runtime_error("failed to read bigreal input.");
                return;
            }
            value = make_bigreal_result(real_value);
            break;

        case TYPE_LOGIC:
            if (scanf("%d", &logic_value) != 1) {
                report_runtime_error("failed to read logic input.");
                return;
            }
            value = make_logic_result(logic_value);
            break;

        case TYPE_CHAR:
            if (scanf(" %c", &char_value) != 1) {
                report_runtime_error("failed to read character input.");
                return;
            }
            value.type = TYPE_CHAR;
            value.has_value = 1;
            value.data.chr_value = char_value;
            break;

        case TYPE_TEXT:
            if (scanf("%1023s", text_buffer) != 1) {
                report_runtime_error("failed to read text input.");
                return;
            }
            value = make_text_result(text_buffer);
            break;

        default:
            report_runtime_error("unsupported read target type.");
            return;
    }

    if (!check_assignment(node->data.read_stmt.name, value.type) ||
        !set_symbol_value(node->data.read_stmt.name, &value)) {
        report_runtime_error("could not store input value.");
    }

    free_expr_result(&value);
}

static void execute_write_statement(StmtNode *node) {
    ExprResult value = evaluate_expression(node->data.write_stmt.value);

    if (!value.has_value) {
        free_expr_result(&value);
        return;
    }

    print_expr_result(&value);
    printf("\n");
    free_expr_result(&value);
}

static void execute_if_statement(StmtNode *node) {
    ExprResult condition = evaluate_expression(node->data.chk_stmt.condition);
    int condition_value;

    if (!condition.has_value) {
        free_expr_result(&condition);
        return;
    }

    condition_value = result_is_true(&condition);
    free_expr_result(&condition);

    if (condition_value) {
        execute_statement_list(node->data.chk_stmt.then_branch);
    } else if (node->data.chk_stmt.else_branch != NULL) {
        execute_statement_list(node->data.chk_stmt.else_branch);
    }
}

static void execute_repeat_statement(StmtNode *node) {
    ExprResult condition;

    do {
        execute_statement_list(node->data.repeat_stmt.body);
        if (stop_requested) {
            return;
        }

        condition = evaluate_expression(node->data.repeat_stmt.condition);
        if (!condition.has_value) {
            free_expr_result(&condition);
            return;
        }

        if (result_is_true(&condition)) {
            free_expr_result(&condition);
            break;
        }

        free_expr_result(&condition);
    } while (!stop_requested);
}

static void execute_block_statement(StmtNode *node) {
    enter_scope();
    execute_statement_list(node->data.block.statements);
    leave_scope();
}

static void execute_decide_statement(StmtNode *node) {
    ExprResult selector;
    CaseNode *case_node;

    selector = evaluate_expression(node->data.decide_stmt.selector);
    if (!selector.has_value) {
        free_expr_result(&selector);
        return;
    }

    case_node = node->data.decide_stmt.cases;
    while (case_node != NULL) {
        ExprResult case_value = evaluate_expression(case_node->condition);

        if (case_value.has_value && result_is_true(&case_value)) {
            free_expr_result(&case_value);
            free_expr_result(&selector);
            execute_statement_list(case_node->body);
            return;
        }

        free_expr_result(&case_value);
        case_node = case_node->next;
    }

    free_expr_result(&selector);

    if (node->data.decide_stmt.otherwise_branch != NULL) {
        execute_statement_list(node->data.decide_stmt.otherwise_branch);
    }
}

static int execute_statement_list(StmtNode *node) {
    int errors_before = runtime_error_count;

    while (node != NULL && !stop_requested && !return_requested) {
        switch (node->kind) {
            case STMT_DECLARATION:
                execute_declaration(node);
                break;
            case STMT_ASSIGNMENT:
                execute_assignment_statement(node);
                break;
            case STMT_READ:
                execute_read_statement(node);
                break;
            case STMT_WRITE:
                execute_write_statement(node);
                break;
            case STMT_BLOCK:
                execute_block_statement(node);
                break;
            case STMT_CHK:
                execute_if_statement(node);
                break;
            case STMT_REPEAT:
                execute_repeat_statement(node);
                break;
            case STMT_DECIDE:
                execute_decide_statement(node);
                break;
            case STMT_SKIP:
            case STMT_FUNCTION_DEF:
                break;
            case STMT_STOP:
                stop_requested = 1;
                break;
            case STMT_RETURN: {
                ExprResult value;

                if (function_call_depth == 0) {
                    report_runtime_error("return statement used outside a function.");
                    break;
                }

                value = evaluate_expression(node->data.return_stmt.value);
                if (!value.has_value) {
                    free_expr_result(&value);
                    break;
                }

                free_expr_result(&return_value);
                return_value = value;
                return_requested = 1;
                break;
            }
            default:
                report_runtime_error("unknown statement kind.");
                break;
        }

        node = node->next;
    }

    return runtime_error_count - errors_before;
}

int execute_statement(StmtNode *node) {
    return execute_statement_list(node);
}

int interpret_program(const Program *program) {
    runtime_error_count = 0;
    stop_requested = 0;
    return_requested = 0;
    function_call_depth = 0;
    clear_symbol_table();
    free_function_table();
    free_expr_result(&return_value);
    return_value = make_invalid_result();

    if (program == NULL) {
        report_runtime_error("program root is null.");
        return runtime_error_count;
    }

    collect_functions(program->statements);
    execute_statement_list(program->statements);
    free_function_table();
    free_expr_result(&return_value);
    return_value = make_invalid_result();
    return runtime_error_count;
}
