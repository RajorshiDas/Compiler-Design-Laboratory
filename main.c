#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;
int yylex(void);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        yyin = stdin;
        printf("Reading from terminal. End with Ctrl+Z then Enter (Windows).\n");
    } else {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Error opening input file");
            return 1;
        }
    }

    yylex();

    if (yyin && yyin != stdin) {
        fclose(yyin);
    }
    return 0;
}
