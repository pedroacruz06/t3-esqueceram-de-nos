/* type.c
 * Adaptação de partes do código do livro de Compiladores
 * de Douglas Thain para a disciplina MATA61-UFBA
 * Christina von Flach (github: christinaflach)
 * 2023
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "expr.h"

struct type * type_create(type_t kind,
                  struct param_list *params,
                  struct type *subtype,
                  struct expr *expr)
{
    struct type *t = malloc(sizeof(*t));
    if (t) {
        t->kind = kind;
        t->params = params;
        t->subtype = subtype;
        t->expr = expr;
    }
    else {
        fprintf(stderr,"Fatal error: not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return t;
}

// func_type_create is defined here.
// However, functions are not implemented as first class citizens.

struct type * func_type_create(struct param_list *params,
                  struct type *subtype)
{
    struct type *ft = type_create(TYPE_FUNCTION,params,subtype,0);
    return ft;

}

struct type * array_type_create(int index, struct type *subtype)
{
    struct expr *e  = expr_create_integer(index); 
    struct type *at = type_create(TYPE_ARRAY,0,subtype,e);
    return at;

}

