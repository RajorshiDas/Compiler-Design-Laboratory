#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

#include "ir.h"

static int temp_counter = 0;
static int label_counter = 0;
static char *loop_continue_labels[64];
static char *loop_break_labels[64];
static int loop_stack_top = 0;

static IRList *generate_function_definition_ir(const StmtNode *stmt);
static IRList *generate_nested_function_ir(const StmtNode *stmt);

static char *copy_text(const char *text) {
    size_t length;
    char *copy;

    if (text == NULL) {
        return NULL;
    }

    length = strlen(text);
    copy = (char *)malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    strcpy(copy, text);
    return copy;
}

static char *make_int_text(long long value) {
    char buffer[32];

    snprintf(buffer, sizeof(buffer), "%lld", value);
    return copy_text(buffer);
}

static char *make_float_text(double value) {
    char buffer[64];

    snprintf(buffer, sizeof(buffer), "%g", value);
    return copy_text(buffer);
}

static char *make_string_text(const char *value) {
    size_t length;
    char *text;

    if (value == NULL) {
        return copy_text("\"\"");
    }

    length = strlen(value);
    text = (char *)malloc(length + 3);
    if (text == NULL) {
        return NULL;
    }

    text[0] = '"';
    strcpy(text + 1, value);
    text[length + 1] = '"';
    text[length + 2] = '\0';
    return text;
}

static char *make_char_text(char value) {
    char buffer[8];

    snprintf(buffer, sizeof(buffer), "'%c'", value);
    return copy_text(buffer);
}

static char *make_bool_text(int value) {
    return copy_text(value ? "1" : "0");
}

static IROpcode opcode_from_binary_operator(const char *op) {
    if (strcmp(op, "+") == 0) {
        return IR_ADD;
    }
    if (strcmp(op, "-") == 0) {
        return IR_SUB;
    }
    if (strcmp(op, "*") == 0) {
        return IR_MUL;
    }
    if (strcmp(op, "/") == 0) {
        return IR_DIV;
    }
    if (strcmp(op, "%") == 0) {
        return IR_MOD;
    }
    if (strcmp(op, "AND") == 0) {
        return IR_AND;
    }
    if (strcmp(op, "OR") == 0) {
        return IR_OR;
    }
    if (strcmp(op, "XOR") == 0) {
        return IR_XOR;
    }
    if (strcmp(op, "<") == 0) {
        return IR_LT;
    }
    if (strcmp(op, ">") == 0) {
        return IR_GT;
    }
    if (strcmp(op, "<=") == 0) {
        return IR_LE;
    }
    if (strcmp(op, ">=") == 0) {
        return IR_GE;
    }
    if (strcmp(op, "==") == 0) {
        return IR_EQ;
    }

    return IR_NE;
}

static IRList *append_code(IRList *first, IRList *second) {
    return append_ir(first, second);
}

IRInstruction *create_ir_instruction(IROpcode op,
                                     char *result,
                                     char *arg1,
                                     char *arg2,
                                     char *label) {
    IRInstruction *instruction = (IRInstruction *)malloc(sizeof(IRInstruction));

    if (instruction == NULL) {
        return NULL;
    }

    instruction->op = op;
    instruction->result = copy_text(result);
    instruction->arg1 = copy_text(arg1);
    instruction->arg2 = copy_text(arg2);
    instruction->label = copy_text(label);
    return instruction;
}

IRList *create_ir_list(IRInstruction *instruction) {
    IRList *node = (IRList *)malloc(sizeof(IRList));

    if (node == NULL) {
        free_ir_instruction(instruction);
        return NULL;
    }

    node->instruction = instruction;
    node->next = NULL;
    return node;
}

IRList *append_ir(IRList *list, IRList *item) {
    IRList *tail;

    if (list == NULL) {
        return item;
    }

    if (item == NULL) {
        return list;
    }

    tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = item;
    return list;
}

char *new_temp(void) {
    char buffer[32];

    ++temp_counter;
    snprintf(buffer, sizeof(buffer), "t%d", temp_counter);
    return copy_text(buffer);
}

char *new_label(void) {
    char buffer[32];

    ++label_counter;
    snprintf(buffer, sizeof(buffer), "L%d", label_counter);
    return copy_text(buffer);
}

static void push_loop_labels(char *continue_label, char *break_label) {
    if (loop_stack_top >= 64) {
        return;
    }

    loop_continue_labels[loop_stack_top] = continue_label;
    loop_break_labels[loop_stack_top] = break_label;
    ++loop_stack_top;
}

static void pop_loop_labels(void) {
    if (loop_stack_top > 0) {
        --loop_stack_top;
    }
}

static char *current_loop_continue_label(void) {
    if (loop_stack_top <= 0) {
        return NULL;
    }

    return loop_continue_labels[loop_stack_top - 1];
}

static char *current_loop_break_label(void) {
    if (loop_stack_top <= 0) {
        return NULL;
    }

    return loop_break_labels[loop_stack_top - 1];
}

static IRList *generate_function_definition_ir(const StmtNode *stmt) {
    IRList *code = NULL;

    if (stmt == NULL || stmt->kind != STMT_FUNCTION_DEF) {
        return NULL;
    }

    code = append_code(
        code,
        create_ir_list(create_ir_instruction(IR_FUNCTION_BEGIN,
                                             NULL,
                                             NULL,
                                             NULL,
                                             stmt->data.function_def.name)));
    code = append_code(code, generate_statement_ir(stmt->data.function_def.body));
    code = append_code(
        code,
        create_ir_list(create_ir_instruction(IR_FUNCTION_END,
                                             NULL,
                                             NULL,
                                             NULL,
                                             stmt->data.function_def.name)));
    return code;
}

static IRList *generate_nested_function_ir(const StmtNode *stmt) {
    IRList *code = NULL;

    while (stmt != NULL) {
        switch (stmt->kind) {
            case STMT_FUNCTION_DEF:
                code = append_code(code, generate_function_definition_ir(stmt));
                code = append_code(code, generate_nested_function_ir(stmt->data.function_def.body));
                break;

            case STMT_BLOCK:
                code = append_code(code, generate_nested_function_ir(stmt->data.block.statements));
                break;

            case STMT_CHK:
                code = append_code(code, generate_nested_function_ir(stmt->data.chk_stmt.then_branch));
                code = append_code(code, generate_nested_function_ir(stmt->data.chk_stmt.else_branch));
                break;

            case STMT_REPEAT:
                code = append_code(code, generate_nested_function_ir(stmt->data.repeat_stmt.body));
                break;

            case STMT_UNTIL:
                code = append_code(code, generate_nested_function_ir(stmt->data.until_stmt.body));
                break;

            case STMT_DOING:
                code = append_code(code, generate_nested_function_ir(stmt->data.doing_stmt.body));
                break;

            case STMT_DECIDE: {
                const CaseNode *case_node = stmt->data.decide_stmt.cases;

                while (case_node != NULL) {
                    code = append_code(code, generate_nested_function_ir(case_node->body));
                    case_node = case_node->next;
                }

                code = append_code(code, generate_nested_function_ir(stmt->data.decide_stmt.otherwise_branch));
                break;
            }

            default:
                break;
        }

        stmt = stmt->next;
    }

    return code;
}

char *generate_expression_ir(ExprNode *expr, IRList **code) {
    char *left_value;
    char *right_value;
    char *result;

    if (expr == NULL) {
        return NULL;
    }

    switch (expr->kind) {
        case EXPR_INT_LITERAL:
            return make_int_text(expr->data.int_value);

        case EXPR_FLOAT_LITERAL:
            return make_float_text(expr->data.float_value);

        case EXPR_STRING_LITERAL:
            return make_string_text(expr->data.string_value);

        case EXPR_CHAR_LITERAL:
            return make_char_text(expr->data.char_value);

        case EXPR_BOOL_LITERAL:
            return make_bool_text(expr->data.bool_value);

        case EXPR_VARIABLE:
            return copy_text(expr->data.identifier);

        case EXPR_BINARY:
            left_value = generate_expression_ir(expr->data.binary.left, code);
            right_value = generate_expression_ir(expr->data.binary.right, code);
            result = new_temp();

            *code = append_code(
                *code,
                create_ir_list(create_ir_instruction(opcode_from_binary_operator(expr->data.binary.op),
                                                     result,
                                                     left_value,
                                                     right_value,
                                                     NULL)));

            free(left_value);
            free(right_value);
            return result;

        case EXPR_UNARY:
            if (strcmp(expr->data.unary.op, "-") == 0) {
                char *operand = generate_expression_ir(expr->data.unary.operand, code);

                result = new_temp();
                *code = append_code(
                    *code,
                    create_ir_list(create_ir_instruction(IR_SUB,
                                                         result,
                                                         "0",
                                                         operand,
                                                         NULL)));
                free(operand);
                return result;
            }

            if (strcmp(expr->data.unary.op, "+") == 0) {
                return generate_expression_ir(expr->data.unary.operand, code);
            }

            if (strcmp(expr->data.unary.op, "!") == 0) {
                char *operand = generate_expression_ir(expr->data.unary.operand, code);

                result = new_temp();
                *code = append_code(
                    *code,
                    create_ir_list(create_ir_instruction(IR_EQ,
                                                         result,
                                                         operand,
                                                         "0",
                                                         NULL)));
                free(operand);
                return result;
            }

            if (strcmp(expr->data.unary.op, "ABS") == 0) {
                ArgumentList *args = create_argument_list(expr->data.unary.operand);
                ExprNode fake_call;

                memset(&fake_call, 0, sizeof(fake_call));
                fake_call.kind = EXPR_FUNCTION_CALL;
                fake_call.value_type = expr->value_type;
                fake_call.data.call.name = "abs";
                fake_call.data.call.arguments = args;
                result = generate_expression_ir(&fake_call, code);
                free(args);
                return result;
            }

            return generate_expression_ir(expr->data.unary.operand, code);

        case EXPR_FUNCTION_CALL: {
            ArgumentList *argument = expr->data.call.arguments;
            int argument_count = 0;

            while (argument != NULL) {
                char *value = generate_expression_ir(argument->expr, code);

                *code = append_code(
                    *code,
                    create_ir_list(create_ir_instruction(IR_PARAM, NULL, value, NULL, NULL)));
                free(value);
                ++argument_count;
                argument = argument->next;
            }

            result = new_temp();
            {
                char count_text[16];

                snprintf(count_text, sizeof(count_text), "%d", argument_count);
                *code = append_code(
                    *code,
                    create_ir_list(create_ir_instruction(IR_CALL,
                                                         result,
                                                         expr->data.call.name,
                                                         count_text,
                                                         NULL)));
            }
            return result;
        }

        default:
            return NULL;
    }
}

IRList *generate_statement_ir(StmtNode *stmt) {
    IRList *code = NULL;

    while (stmt != NULL) {
        switch (stmt->kind) {
            case STMT_DECLARATION:
                if (stmt->data.declaration.initializer != NULL) {
                    char *value = generate_expression_ir(stmt->data.declaration.initializer, &code);

                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_ASSIGN,
                                                             stmt->data.declaration.name,
                                                             value,
                                                             NULL,
                                                             NULL)));
                    free(value);
                }
                break;

            case STMT_ASSIGNMENT: {
                char *value = generate_expression_ir(stmt->data.assignment.value, &code);

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_ASSIGN,
                                                         stmt->data.assignment.name,
                                                         value,
                                                         NULL,
                                                         NULL)));
                free(value);
                break;
            }

            case STMT_READ:
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_READ,
                                                         stmt->data.read_stmt.name,
                                                         NULL,
                                                         NULL,
                                                         NULL)));
                break;

            case STMT_WRITE: {
                ExprList *value = stmt->data.write_stmt.values;

                while (value != NULL) {
                    char *text = generate_expression_ir(value->expr, &code);

                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_WRITE,
                                                             NULL,
                                                             text,
                                                             NULL,
                                                             NULL)));
                    free(text);
                    value = value->next;
                }
                break;
            }

            case STMT_BLOCK:
                code = append_code(code, generate_statement_ir(stmt->data.block.statements));
                break;

            case STMT_CHK: {
                char *condition_value;
                char *false_label = new_label();
                char *end_label = new_label();

                condition_value = generate_expression_ir(stmt->data.chk_stmt.condition, &code);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_IF_FALSE_GOTO,
                                                         NULL,
                                                         condition_value,
                                                         NULL,
                                                         false_label)));
                free(condition_value);

                code = append_code(code, generate_statement_ir(stmt->data.chk_stmt.then_branch));

                if (stmt->data.chk_stmt.else_branch != NULL) {
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_GOTO,
                                                             NULL,
                                                             NULL,
                                                             NULL,
                                                             end_label)));
                }

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         false_label)));

                if (stmt->data.chk_stmt.else_branch != NULL) {
                    code = append_code(code, generate_statement_ir(stmt->data.chk_stmt.else_branch));
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_LABEL,
                                                             NULL,
                                                             NULL,
                                                             NULL,
                                                             end_label)));
                }

                free(false_label);
                free(end_label);
                break;
            }

            case STMT_REPEAT: {
                char *condition_label = new_label();
                char *update_label = new_label();
                char *end_label = new_label();
                char *condition_value;
                char *update_value;

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         condition_label)));
                condition_value = generate_expression_ir(stmt->data.repeat_stmt.condition, &code);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_IF_FALSE_GOTO,
                                                         NULL,
                                                         condition_value,
                                                         NULL,
                                                         end_label)));
                free(condition_value);

                push_loop_labels(update_label, end_label);
                code = append_code(code, generate_statement_ir(stmt->data.repeat_stmt.body));
                pop_loop_labels();

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         update_label)));
                update_value = generate_expression_ir(stmt->data.repeat_stmt.update, &code);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_ASSIGN,
                                                         stmt->data.repeat_stmt.iterator,
                                                         update_value,
                                                         NULL,
                                                         NULL)));
                free(update_value);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_GOTO,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         condition_label)));
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         end_label)));

                free(condition_label);
                free(update_label);
                free(end_label);
                break;
            }

            case STMT_UNTIL: {
                char *condition_label = new_label();
                char *body_label = new_label();
                char *end_label = new_label();
                char *condition_value;

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         condition_label)));
                condition_value = generate_expression_ir(stmt->data.until_stmt.condition, &code);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_IF_FALSE_GOTO,
                                                         NULL,
                                                         condition_value,
                                                         NULL,
                                                         body_label)));
                free(condition_value);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_GOTO,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         end_label)));
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         body_label)));

                push_loop_labels(condition_label, end_label);
                code = append_code(code, generate_statement_ir(stmt->data.until_stmt.body));
                pop_loop_labels();

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_GOTO,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         condition_label)));
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         end_label)));

                free(condition_label);
                free(body_label);
                free(end_label);
                break;
            }

            case STMT_DOING: {
                char *body_label = new_label();
                char *condition_label = new_label();
                char *end_label = new_label();
                char *condition_value;

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         body_label)));

                push_loop_labels(condition_label, end_label);
                code = append_code(code, generate_statement_ir(stmt->data.doing_stmt.body));
                pop_loop_labels();

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         condition_label)));
                condition_value = generate_expression_ir(stmt->data.doing_stmt.condition, &code);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_IF_FALSE_GOTO,
                                                         NULL,
                                                         condition_value,
                                                         NULL,
                                                         body_label)));
                free(condition_value);
                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         end_label)));

                free(body_label);
                free(condition_label);
                free(end_label);
                break;
            }

            case STMT_FUNCTION_DEF:
                break;

            case STMT_SKIP: {
                char *continue_label = current_loop_continue_label();

                if (continue_label != NULL) {
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_GOTO,
                                                             NULL,
                                                             NULL,
                                                             NULL,
                                                             continue_label)));
                }
                break;
            }

            case STMT_STOP: {
                char *break_label = current_loop_break_label();

                if (break_label != NULL) {
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_GOTO,
                                                             NULL,
                                                             NULL,
                                                             NULL,
                                                             break_label)));
                }
                break;
            }

            case STMT_DECIDE: {
                CaseNode *case_node = stmt->data.decide_stmt.cases;
                char *end_label = new_label();
                char *selector_value = generate_expression_ir(stmt->data.decide_stmt.selector, &code);

                while (case_node != NULL) {
                    char *next_label = new_label();
                    char *case_value = generate_expression_ir(case_node->condition, &code);
                    char *condition_temp = new_temp();

                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_EQ,
                                                             condition_temp,
                                                             selector_value,
                                                             case_value,
                                                             NULL)));
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_IF_FALSE_GOTO,
                                                             NULL,
                                                             condition_temp,
                                                             NULL,
                                                             next_label)));
                    free(case_value);
                    free(condition_temp);

                    code = append_code(code, generate_statement_ir(case_node->body));
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_GOTO,
                                                             NULL,
                                                             NULL,
                                                             NULL,
                                                             end_label)));
                    code = append_code(
                        code,
                        create_ir_list(create_ir_instruction(IR_LABEL,
                                                             NULL,
                                                             NULL,
                                                             NULL,
                                                             next_label)));
                    free(next_label);
                    case_node = case_node->next;
                }

                if (stmt->data.decide_stmt.otherwise_branch != NULL) {
                    code = append_code(code, generate_statement_ir(stmt->data.decide_stmt.otherwise_branch));
                }

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_LABEL,
                                                         NULL,
                                                         NULL,
                                                         NULL,
                                                         end_label)));
                free(selector_value);
                free(end_label);
                break;
            }

            case STMT_RETURN: {
                char *value = generate_expression_ir(stmt->data.return_stmt.value, &code);

                code = append_code(
                    code,
                    create_ir_list(create_ir_instruction(IR_RETURN,
                                                         NULL,
                                                         value,
                                                         NULL,
                                                         NULL)));
                free(value);
                break;
            }

            default:
                break;
        }

        stmt = stmt->next;
    }

    return code;
}

IRList *generate_program_ir(Program *program) {
    IRList *code = NULL;

    if (program == NULL) {
        return NULL;
    }

    temp_counter = 0;
    label_counter = 0;
    loop_stack_top = 0;

    code = append_code(code, generate_nested_function_ir(program->statements));
    code = append_code(
        code,
        create_ir_list(create_ir_instruction(IR_FUNCTION_BEGIN,
                                             NULL,
                                             NULL,
                                             NULL,
                                             "start")));
    code = append_code(code, generate_statement_ir(program->statements));
    code = append_code(
        code,
        create_ir_list(create_ir_instruction(IR_FUNCTION_END,
                                             NULL,
                                             NULL,
                                             NULL,
                                             "start")));
    return code;
}

IRList *generate_ir(Program *root) {
    return generate_program_ir(root);
}

void print_ir(const IRList *list) {
    while (list != NULL) {
        const IRInstruction *instruction = list->instruction;

        if (instruction == NULL) {
            list = list->next;
            continue;
        }

        switch (instruction->op) {
            case IR_FUNCTION_BEGIN:
                printf("\nfunction %s:\n", instruction->label);
                break;

            case IR_FUNCTION_END:
                printf("end function %s\n", instruction->label);
                break;

            case IR_LABEL:
                printf("%s:\n", instruction->label);
                break;

            case IR_GOTO:
                printf("goto %s\n", instruction->label);
                break;

            case IR_IF_FALSE_GOTO:
                printf("ifFalse %s goto %s\n", instruction->arg1, instruction->label);
                break;

            case IR_ASSIGN:
                printf("%s = %s\n", instruction->result, instruction->arg1);
                break;

            case IR_ADD:
                printf("%s = %s + %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_SUB:
                printf("%s = %s - %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_MUL:
                printf("%s = %s * %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_DIV:
                printf("%s = %s / %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_MOD:
                printf("%s = %s %% %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_AND:
                printf("%s = %s AND %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_OR:
                printf("%s = %s OR %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_XOR:
                printf("%s = %s XOR %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_LT:
                printf("%s = %s < %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_GT:
                printf("%s = %s > %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_LE:
                printf("%s = %s <= %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_GE:
                printf("%s = %s >= %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_EQ:
                printf("%s = %s == %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_NE:
                printf("%s = %s != %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_READ:
                printf("read %s\n", instruction->result);
                break;

            case IR_WRITE:
                printf("write %s\n", instruction->arg1);
                break;

            case IR_PARAM:
                printf("param %s\n", instruction->arg1);
                break;

            case IR_CALL:
                printf("%s = call %s, %s\n", instruction->result, instruction->arg1, instruction->arg2);
                break;

            case IR_RETURN:
                printf("return %s\n", instruction->arg1);
                break;
        }

        list = list->next;
    }
}

void free_ir_instruction(IRInstruction *instruction) {
    if (instruction == NULL) {
        return;
    }

    free(instruction->result);
    free(instruction->arg1);
    free(instruction->arg2);
    free(instruction->label);
    free(instruction);
}

void free_ir_list(IRList *list) {
    IRList *next;

    while (list != NULL) {
        next = list->next;
        free_ir_instruction(list->instruction);
        free(list);
        list = next;
    }
}


