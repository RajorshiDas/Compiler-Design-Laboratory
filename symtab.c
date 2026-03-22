#include <stdio.h>
#include <string.h>
#include "symtab.h"

#define MAX_SYMBOLS 256
#define MAX_NAME_LENGTH 64

typedef struct SymbolEntry {
    char name[MAX_NAME_LENGTH];
    DataType type;
} SymbolEntry;

static SymbolEntry symbol_table[MAX_SYMBOLS];
static int symbol_count = 0;

static int find_symbol(const char *name) {
    int i;

    for (i = 0; i < symbol_count; ++i) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

static int is_numeric_type(DataType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static int can_implicitly_convert(DataType from, DataType to) {
    return (from == TYPE_NUM && to == TYPE_REAL) ||
           (from == TYPE_NUM && to == TYPE_BIGREAL) ||
           (from == TYPE_REAL && to == TYPE_BIGREAL);
}

const char *symbol_type_name(SymbolType type) {
    switch (type) {
        case TYPE_NUM:
            return "num";
        case TYPE_REAL:
            return "real";
        case TYPE_BIGREAL:
            return "bigreal";
        case TYPE_CHAR:
            return "chr";
        case TYPE_LOGIC:
            return "logic";
        case TYPE_TEXT:
            return "text";
        default:
            return "error";
    }
}

int insert_symbol(const char *name, DataType type) {
    if (find_symbol(name) != -1) {
        fprintf(stderr, "Semantic error: variable '%s' is already declared.\n", name);
        return 0;
    }

    if (symbol_count >= MAX_SYMBOLS) {
        fprintf(stderr, "Semantic error: symbol table is full. Could not insert '%s'.\n", name);
        return 0;
    }

    strncpy(symbol_table[symbol_count].name, name, MAX_NAME_LENGTH - 1);
    symbol_table[symbol_count].name[MAX_NAME_LENGTH - 1] = '\0';
    symbol_table[symbol_count].type = type;
    ++symbol_count;
    return 1;
}

int is_declared(const char *name) {
    return find_symbol(name) != -1;
}

DataType get_type(const char *name) {
    int index = find_symbol(name);

    if (index == -1) {
        fprintf(stderr, "Semantic error: variable '%s' is not declared.\n", name);
        return TYPE_ERROR;
    }

    return symbol_table[index].type;
}

DataType result_type(DataType a, DataType b) {
    if (a == TYPE_ERROR || b == TYPE_ERROR) {
        return TYPE_ERROR;
    }

    if (!is_numeric_type(a) || !is_numeric_type(b)) {
        fprintf(stderr,
                "Semantic error: invalid arithmetic between %s and %s.\n",
                symbol_type_name(a),
                symbol_type_name(b));
        return TYPE_ERROR;
    }

    if (a == TYPE_BIGREAL || b == TYPE_BIGREAL) {
        return TYPE_BIGREAL;
    }

    if (a == TYPE_REAL || b == TYPE_REAL) {
        return TYPE_REAL;
    }

    return TYPE_NUM;
}

int check_assignment(const char *name, DataType expr_type) {
    DataType variable_type;

    variable_type = get_type(name);
    if (variable_type == TYPE_ERROR || expr_type == TYPE_ERROR) {
        return 0;
    }

    if (variable_type == expr_type) {
        return 1;
    }

    if (can_implicitly_convert(expr_type, variable_type)) {
        fprintf(stderr,
                "Semantic note: implicit conversion from %s to %s for '%s'.\n",
                symbol_type_name(expr_type),
                symbol_type_name(variable_type),
                name);
        return 1;
    }

    fprintf(stderr,
            "Semantic error: cannot assign %s to %s variable '%s'.\n",
            symbol_type_name(expr_type),
            symbol_type_name(variable_type),
            name);
    return 0;
}

void print_symbol_table(void) {
    int i;

    printf("\nSymbol Table:\n");
    printf("%-20s %-10s\n", "Identifier", "Type");
    printf("-------------------- ----------\n");

    for (i = 0; i < symbol_count; ++i) {
        printf("%-20s %-10s\n",
               symbol_table[i].name,
               symbol_type_name(symbol_table[i].type));
    }
}

void clear_symbol_table(void) {
    symbol_count = 0;
}
