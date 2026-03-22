#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"

extern FILE* yyin;
int yyparse(void);

int main(int argc, char* argv[]) {
    int parse_status;

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
    print_symbol_table();

    if (yyin && yyin != stdin) {
        fclose(yyin);
    }

    return parse_status == 0 ? 0 : 1;
}
