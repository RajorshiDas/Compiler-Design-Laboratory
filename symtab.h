#ifndef SYMTAB_H
#define SYMTAB_H

typedef enum DataType {
    TYPE_NUM = 1,
    TYPE_REAL,
    TYPE_BIGREAL,
    TYPE_CHAR,
    TYPE_LOGIC,
    TYPE_TEXT,
    TYPE_ERROR
} DataType;

typedef DataType SymbolType;

#define TYPE_CHR TYPE_CHAR
#define TYPE_INVALID TYPE_ERROR

int insert_symbol(const char *name, DataType type);
int is_declared(const char *name);
DataType get_type(const char *name);
DataType result_type(DataType left, DataType right);
int check_assignment(const char *name, DataType expr_type);
void print_symbol_table(void);

const char *symbol_type_name(SymbolType type);
void clear_symbol_table(void);

#endif
