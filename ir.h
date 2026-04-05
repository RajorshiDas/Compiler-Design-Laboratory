#ifndef IR_H
#define IR_H

#include "ast.h"

typedef enum IROpcode {
    IR_FUNCTION_BEGIN,
    IR_FUNCTION_END,
    IR_LABEL,
    IR_GOTO,
    IR_IF_FALSE_GOTO,
    IR_ASSIGN,
    IR_ADD,
    IR_SUB,
    IR_MUL,
    IR_DIV,
    IR_MOD,
    IR_AND,
    IR_OR,
    IR_XOR,
    IR_LT,
    IR_GT,
    IR_LE,
    IR_GE,
    IR_EQ,
    IR_NE,
    IR_READ,
    IR_WRITE,
    IR_PARAM,
    IR_CALL,
    IR_RETURN
} IROpcode;

typedef struct IRInstruction IRInstruction;
typedef struct IRList IRList;

struct IRInstruction {
    IROpcode op;
    char *result;
    char *arg1;
    char *arg2;
    char *label;
};

struct IRList {
    IRInstruction *instruction;
    IRList *next;
};

IRInstruction *create_ir_instruction(IROpcode op,
                                     char *result,
                                     char *arg1,
                                     char *arg2,
                                     char *label);
IRList *create_ir_list(IRInstruction *instruction);
IRList *append_ir(IRList *list, IRList *item);

IRList *generate_ir(Program *root);
IRList *generate_program_ir(Program *program);
IRList *generate_statement_ir(StmtNode *stmt);
char *generate_expression_ir(ExprNode *expr, IRList **code);

char *new_temp(void);
char *new_label(void);

void print_ir(const IRList *list);
void free_ir_instruction(IRInstruction *instruction);
void free_ir_list(IRList *list);

#endif
