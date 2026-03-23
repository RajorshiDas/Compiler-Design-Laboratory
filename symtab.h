#ifndef SYMTAB_H
#define SYMTAB_H

typedef enum DataType {
    TYPE_UNKNOWN = 0,
    TYPE_NUM,
    TYPE_REAL,
    TYPE_BIGREAL,
    TYPE_CHAR,
    TYPE_LOGIC,
    TYPE_TEXT,
    TYPE_EMPTY,
    TYPE_ERROR
} DataType;

typedef DataType SymbolType;

#define TYPE_CHR TYPE_CHAR
#define TYPE_INVALID TYPE_ERROR

typedef union ValueData {
    long long num_value;
    double real_value;
    double bigreal_value;
    int logic_value;
    char chr_value;
    char *text_value;
} ValueData;

typedef struct RuntimeValue {
    DataType type;
    int is_initialized;
    ValueData data;
} RuntimeValue;

typedef struct ExprResult {
    DataType type;
    int has_value;
    ValueData data;
} ExprResult;

void enter_scope(void);
void exit_scope(void);
void leave_scope(void);

int insert_symbol(const char *name, DataType type);
int is_declared(const char *name);
DataType get_type(const char *name);
DataType result_type(DataType left, DataType right);
int check_assignment(const char *name, DataType expr_type);
int set_int_value(const char *name, long long value);
int set_float_value(const char *name, double value);
int set_string_value(const char *name, const char *value);
int get_int_value(const char *name, long long *out_value);
int get_float_value(const char *name, double *out_value);
int get_string_value(const char *name, const char **out_value);
int get_symbol_value(const char *name, RuntimeValue *out_value);
int set_symbol_value(const char *name, const ExprResult *expr_value);
void free_runtime_value(RuntimeValue *value);
void free_expr_result(ExprResult *expr);
char *decode_string_literal(const char *lexeme);
char decode_char_literal(const char *lexeme);
void print_expr_result(const ExprResult *expr);
void print_symbol_table(void);

const char *symbol_type_name(SymbolType type);
void clear_symbol_table(void);

#endif
