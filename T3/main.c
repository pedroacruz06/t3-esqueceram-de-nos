/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include "decl.h"
#include "lbn.h"

extern struct decl *parser_result;
extern int yylineno;
extern struct decl* yyparse();

int main(int argc, char **argv) {

    extern FILE *yyin;
    extern FILE *yyout;

    if (argc > 2) {
        if(!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr,"Erro na abertura do arquivo de entrada %s\n",argv[1]);
            return (1);
        }
        if(!(yyout = fopen(argv[2], "w"))) {
            fprintf(stderr,"Erro na criacao do arquivo de saida %s\n",argv[2]);
            return (1);
        }
    }
    else {
        fprintf(stderr,"Erro no número de argumentos passados para o analisador\n");
        return (1);
    }

    if (!yyparse())
       print_AST(parser_result);
    else
       fprintf(yyout,"syntax error\n");

    fclose(yyout);
}

