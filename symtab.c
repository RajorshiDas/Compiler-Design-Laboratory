#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define MAX_SYMBOLS 512
#define MAX_NAME_LENGTH 64

typedef struct SymbolEntry {
    char name[MAX_NAME_LENGTH];
    DataType type;
    int scope_level;
    RuntimeValue value;
} SymbolEntry;

static SymbolEntry symbol_table[MAX_SYMBOLS];
static int symbol_count = 0;
static int current_scope_level = 0;

static char *duplicate_text(const char *source) {
    size_t length;
    char *copy;

    if (source == NULL) {
        source = "";
    }

    length = strlen(source);
    copy = (char *)malloc(length + 1);
    if (copy == NULL) {
        fprintf(stderr, "Runtime error: out of memory while copying text.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(copy, source);
    return copy;
}

static void clear_value_data(DataType type, ValueData *data, int is_initialized) {
    if (is_initialized && type == TYPE_TEXT && data->text_value != NULL) {
        free(data->text_value);
        data->text_value = NULL;
    }
}

static void initialize_runtime_value(RuntimeValue *value, DataType type) {
    if (value == NULL) {
        return;
    }

    value->type = type;
    value->is_initialized = 0;
    value->data.text_value = NULL;
}

static void set_default_runtime_value(RuntimeValue *value) {
    if (value == NULL) {
        return;
    }

    clear_value_data(value->type, &value->data, value->is_initialized);
    value->is_initialized = 1;

    switch (value->type) {
        case TYPE_NUM:
            value->data.num_value = 0;
            break;
        case TYPE_REAL:
            value->data.real_value = 0.0;
            break;
        case TYPE_BIGREAL:
            value->data.bigreal_value = 0.0;
            break;
        case TYPE_CHAR:
            value->data.chr_value = '\0';
            break;
        case TYPE_LOGIC:
            value->data.logic_value = 0;
            break;
        case TYPE_TEXT:
            value->data.text_value = duplicate_text("");
            break;
        default:
            value->is_initialized = 0;
            value->data.text_value = NULL;
            break;
    }
}

static void copy_value_data(ValueData *destination, const ValueData *source, DataType type) {
    switch (type) {
        case TYPE_NUM:
            destination->num_value = source->num_value;
            break;
        case TYPE_REAL:
            destination->real_value = source->real_value;
            break;
        case TYPE_BIGREAL:
            destination->bigreal_value = source->bigreal_value;
            break;
        case TYPE_CHAR:
            destination->chr_value = source->chr_value;
            break;
        case TYPE_LOGIC:
            destination->logic_value = source->logic_value;
            break;
        case TYPE_TEXT:
            destination->text_value = duplicate_text(source->text_value);
            break;
        default:
            destination->text_value = NULL;
            break;
    }
}

static int is_numeric_type(DataType type) {
    return type == TYPE_NUM || type == TYPE_REAL || type == TYPE_BIGREAL;
}

static int can_implicitly_convert(DataType from, DataType to) {
    return (from == TYPE_NUM && to == TYPE_REAL) ||
           (from == TYPE_NUM && to == TYPE_BIGREAL) ||
           (from == TYPE_REAL && to == TYPE_BIGREAL);
}

static int find_symbol_in_current_scope(const char *name) {
    int i;

    for (i = symbol_count - 1; i >= 0; --i) {
        if (symbol_table[i].scope_level < current_scope_level) {
            break;
        }

        if (strcmp(symbol_table[i].name, name) == 0 &&
            symbol_table[i].scope_level == current_scope_level) {
            return i;
        }
    }

    return -1;
}

static int find_visible_symbol(const char *name) {
    int i;

    for (i = symbol_count - 1; i >= 0; --i) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

static int build_runtime_value(DataType target_type, const ExprResult *expr_value, RuntimeValue *out_value) {
    initialize_runtime_value(out_value, target_type);

    if (expr_value == NULL || !expr_value->has_value) {
        return 0;
    }

    out_value->is_initialized = 1;

    switch (target_type) {
        case TYPE_NUM:
            if (expr_value->type != TYPE_NUM) {
                return 0;
            }
            out_value->data.num_value = expr_value->data.num_value;
            return 1;

        case TYPE_REAL:
            if (expr_value->type == TYPE_NUM) {
                out_value->data.real_value = (double)expr_value->data.num_value;
                return 1;
            }
            if (expr_value->type == TYPE_REAL) {
                out_value->data.real_value = expr_value->data.real_value;
                return 1;
            }
            return 0;

        case TYPE_BIGREAL:
            if (expr_value->type == TYPE_NUM) {
                out_value->data.bigreal_value = (double)expr_value->data.num_value;
                return 1;
            }
            if (expr_value->type == TYPE_REAL) {
                out_value->data.bigreal_value = expr_value->data.real_value;
                return 1;
            }
            if (expr_value->type == TYPE_BIGREAL) {
                out_value->data.bigreal_value = expr_value->data.bigreal_value;
                return 1;
            }
            return 0;

        case TYPE_CHAR:
            if (expr_value->type != TYPE_CHAR) {
                return 0;
            }
            out_value->data.chr_value = expr_value->data.chr_value;
            return 1;

        case TYPE_LOGIC:
            if (expr_value->type != TYPE_LOGIC) {
                return 0;
            }
            out_value->data.logic_value = expr_value->data.logic_value;
            return 1;

        case TYPE_TEXT:
            if (expr_value->type != TYPE_TEXT) {
                return 0;
            }
            out_value->data.text_value = duplicate_text(expr_value->data.text_value);
            return 1;

        default:
            out_value->is_initialized = 0;
            return 0;
    }
}

static void print_value_data(DataType type, const ValueData *data) {
    switch (type) {
        case TYPE_NUM:
            printf("%lld", data->num_value);
            break;
        case TYPE_REAL:
            printf("%g", data->real_value);
            break;
        case TYPE_BIGREAL:
            printf("%g", data->bigreal_value);
            break;
        case TYPE_CHAR:
            printf("%c", data->chr_value);
            break;
        case TYPE_LOGIC:
            printf("%s", data->logic_value ? "true" : "false");
            break;
        case TYPE_TEXT:
            printf("%s", data->text_value != NULL ? data->text_value : "");
            break;
        case TYPE_UNKNOWN:
            printf("<unknown>");
            break;
        default:
            printf("<invalid>");
            break;
    }
}

void enter_scope(void) {
    ++current_scope_level;
}

void exit_scope(void) {
    while (symbol_count > 0 && symbol_table[symbol_count - 1].scope_level == current_scope_level) {
        free_runtime_value(&symbol_table[symbol_count - 1].value);
        --symbol_count;
    }

    if (current_scope_level > 0) {
        --current_scope_level;
    }
}

void leave_scope(void) {
    exit_scope();
}

const char *symbol_type_name(SymbolType type) {
    switch (type) {
        case TYPE_UNKNOWN:
            return "unknown";
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
    if (find_symbol_in_current_scope(name) != -1) {
        fprintf(stderr, "Semantic error: variable '%s' is already declared in this scope.\n", name);
        return 0;
    }

    if (symbol_count >= MAX_SYMBOLS) {
        fprintf(stderr, "Semantic error: symbol table is full. Could not insert '%s'.\n", name);
        return 0;
    }

    strncpy(symbol_table[symbol_count].name, name, MAX_NAME_LENGTH - 1);
    symbol_table[symbol_count].name[MAX_NAME_LENGTH - 1] = '\0';
    symbol_table[symbol_count].type = type;
    symbol_table[symbol_count].scope_level = current_scope_level;
    initialize_runtime_value(&symbol_table[symbol_count].value, type);
    set_default_runtime_value(&symbol_table[symbol_count].value);
    ++symbol_count;
    return 1;
}

int is_declared(const char *name) {
    return find_visible_symbol(name) != -1;
}

DataType get_type(const char *name) {
    int index = find_visible_symbol(name);

    if (index == -1) {
        fprintf(stderr, "Semantic error: variable '%s' is not declared.\n", name);
        return TYPE_ERROR;
    }

    return symbol_table[index].type;
}

DataType result_type(DataType left, DataType right) {
    if (left == TYPE_UNKNOWN || right == TYPE_UNKNOWN) {
        return TYPE_UNKNOWN;
    }

    if (left == TYPE_ERROR || right == TYPE_ERROR) {
        return TYPE_ERROR;
    }

    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        fprintf(stderr,
                "Semantic error: invalid arithmetic between %s and %s.\n",
                symbol_type_name(left),
                symbol_type_name(right));
        return TYPE_ERROR;
    }

    if (left == TYPE_BIGREAL || right == TYPE_BIGREAL) {
        return TYPE_BIGREAL;
    }

    if (left == TYPE_REAL || right == TYPE_REAL) {
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

    if (expr_type == TYPE_UNKNOWN) {
        return 1;
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

int set_int_value(const char *name, long long value) {
    ExprResult expr_value;

    expr_value.type = TYPE_NUM;
    expr_value.has_value = 1;
    expr_value.data.num_value = value;

    if (!check_assignment(name, expr_value.type)) {
        return 0;
    }

    return set_symbol_value(name, &expr_value);
}

int set_float_value(const char *name, double value) {
    ExprResult expr_value;

    expr_value.type = TYPE_REAL;
    expr_value.has_value = 1;
    expr_value.data.real_value = value;

    if (!check_assignment(name, expr_value.type)) {
        return 0;
    }

    return set_symbol_value(name, &expr_value);
}

int set_string_value(const char *name, const char *value) {
    ExprResult expr_value;

    expr_value.type = TYPE_TEXT;
    expr_value.has_value = 1;
    expr_value.data.text_value = (char *)value;

    if (!check_assignment(name, expr_value.type)) {
        return 0;
    }

    return set_symbol_value(name, &expr_value);
}

int get_int_value(const char *name, long long *out_value) {
    int index = find_visible_symbol(name);

    if (index == -1) {
        fprintf(stderr, "Semantic error: variable '%s' is not declared.\n", name);
        return 0;
    }

    if (!symbol_table[index].value.is_initialized) {
        return 0;
    }

    switch (symbol_table[index].value.type) {
        case TYPE_NUM:
            if (out_value != NULL) {
                *out_value = symbol_table[index].value.data.num_value;
            }
            return 1;
        case TYPE_REAL:
            if (out_value != NULL) {
                *out_value = (long long)symbol_table[index].value.data.real_value;
            }
            return 1;
        case TYPE_BIGREAL:
            if (out_value != NULL) {
                *out_value = (long long)symbol_table[index].value.data.bigreal_value;
            }
            return 1;
        default:
            return 0;
    }
}

int get_float_value(const char *name, double *out_value) {
    int index = find_visible_symbol(name);

    if (index == -1) {
        fprintf(stderr, "Semantic error: variable '%s' is not declared.\n", name);
        return 0;
    }

    if (!symbol_table[index].value.is_initialized) {
        return 0;
    }

    switch (symbol_table[index].value.type) {
        case TYPE_NUM:
            if (out_value != NULL) {
                *out_value = (double)symbol_table[index].value.data.num_value;
            }
            return 1;
        case TYPE_REAL:
            if (out_value != NULL) {
                *out_value = symbol_table[index].value.data.real_value;
            }
            return 1;
        case TYPE_BIGREAL:
            if (out_value != NULL) {
                *out_value = symbol_table[index].value.data.bigreal_value;
            }
            return 1;
        default:
            return 0;
    }
}

int get_string_value(const char *name, const char **out_value) {
    int index = find_visible_symbol(name);

    if (index == -1) {
        fprintf(stderr, "Semantic error: variable '%s' is not declared.\n", name);
        return 0;
    }

    if (!symbol_table[index].value.is_initialized) {
        return 0;
    }

    if (symbol_table[index].value.type != TYPE_TEXT) {
        return 0;
    }

    if (out_value != NULL) {
        *out_value = symbol_table[index].value.data.text_value;
    }

    return 1;
}

int get_symbol_value(const char *name, RuntimeValue *out_value) {
    int index = find_visible_symbol(name);

    if (index == -1) {
        return -1;
    }

    if (out_value != NULL) {
        initialize_runtime_value(out_value, symbol_table[index].type);
        if (symbol_table[index].value.is_initialized) {
            out_value->is_initialized = 1;
            copy_value_data(&out_value->data,
                            &symbol_table[index].value.data,
                            symbol_table[index].type);
        }
    }

    return symbol_table[index].value.is_initialized ? 1 : 0;
}

int set_symbol_value(const char *name, const ExprResult *expr_value) {
    int index = find_visible_symbol(name);
    RuntimeValue converted_value;

    if (index == -1) {
        return 0;
    }

    if (!build_runtime_value(symbol_table[index].type, expr_value, &converted_value)) {
        return 0;
    }

    free_runtime_value(&symbol_table[index].value);
    symbol_table[index].value = converted_value;
    return 1;
}

void free_runtime_value(RuntimeValue *value) {
    if (value == NULL) {
        return;
    }

    clear_value_data(value->type, &value->data, value->is_initialized);
    value->is_initialized = 0;
}

void free_expr_result(ExprResult *expr) {
    if (expr == NULL) {
        return;
    }

    clear_value_data(expr->type, &expr->data, expr->has_value);
    expr->type = TYPE_INVALID;
    expr->has_value = 0;
}

char *decode_string_literal(const char *lexeme) {
    size_t length;
    char *decoded;
    size_t read_index;
    size_t write_index;

    if (lexeme == NULL) {
        return duplicate_text("");
    }

    length = strlen(lexeme);
    decoded = (char *)malloc(length + 1);
    if (decoded == NULL) {
        fprintf(stderr, "Runtime error: out of memory while decoding a string literal.\n");
        exit(EXIT_FAILURE);
    }

    write_index = 0;
    for (read_index = 1; read_index + 1 < length; ++read_index) {
        if (lexeme[read_index] == '\\' && read_index + 1 < length - 1) {
            ++read_index;
            switch (lexeme[read_index]) {
                case 'n':
                    decoded[write_index++] = '\n';
                    break;
                case 't':
                    decoded[write_index++] = '\t';
                    break;
                case 'r':
                    decoded[write_index++] = '\r';
                    break;
                case '\\':
                    decoded[write_index++] = '\\';
                    break;
                case '"':
                    decoded[write_index++] = '"';
                    break;
                default:
                    decoded[write_index++] = lexeme[read_index];
                    break;
            }
        } else {
            decoded[write_index++] = lexeme[read_index];
        }
    }

    decoded[write_index] = '\0';
    return decoded;
}

void print_expr_result(const ExprResult *expr) {
    if (expr == NULL || !expr->has_value) {
        printf("<uninitialized>");
        return;
    }

    print_value_data(expr->type, &expr->data);
}

void print_symbol_table(void) {
    int i;

    printf("\nSymbol Table:\n");
    printf("%-20s %-10s %-20s %-6s\n", "Identifier", "Type", "Value", "Scope");
    printf("-------------------- ---------- -------------------- ------\n");

    for (i = 0; i < symbol_count; ++i) {
        printf("%-20s %-10s ",
               symbol_table[i].name,
               symbol_type_name(symbol_table[i].type));
        if (symbol_table[i].value.is_initialized) {
            print_value_data(symbol_table[i].type, &symbol_table[i].value.data);
        } else {
            printf("(uninitialized)");
        }
        printf(" %-6d\n", symbol_table[i].scope_level);
    }
}

void clear_symbol_table(void) {
    while (symbol_count > 0) {
        free_runtime_value(&symbol_table[symbol_count - 1].value);
        --symbol_count;
    }

    current_scope_level = 0;
}
