/* expr.c
 * Adaptação de partes do código do livro de Compiladores
 * de Douglas Thain para a disciplina MATA61-UFBA
 * Christina von Flach (github: christinaflach)
 * 2026
 */ 

#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

struct expr * expression_create(expr_t kind, 
              struct expr *left, struct expr *right, 
              char *name, int value)
{
    struct expr *e = malloc(sizeof(*e));
    if (e) {
        e->kind = kind;
        e->left = left;
        e->right = right;
        e->name = name;
        e->integer_value = value;
    }
    else {
        fprintf(stderr,"Fatal error: not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return e;
}

struct expr * expr_create(expr_t kind,
                          struct expr *left, struct expr *right)
{
    struct expr *e = expression_create(kind,left,right,0,0);
    return e;
}


struct expr * expr_create_integer(int i)
{
    struct expr *ei =
        expression_create(EXPR_INTEGER_LITERAL,0,0,0,i);
    return ei;
}

struct expr * expr_create_boolean(int b)
{
    struct expr *eb =
        expression_create(EXPR_BOOLEAN_LITERAL,0,0,0,b);
    return eb;
}

struct expr * expr_create_name(char *name)
{
    struct expr *en = expression_create(EXPR_NAME,0,0,name,0);
    return en;
}

struct expr * expr_create_var(char *n)
{
    struct expr *name= expr_create_name(n);
    struct expr *ev = expr_create(EXPR_VAR,name,0);
    return ev;
}

struct expr * expr_create_var_array(char *n, struct expr *index)
{
    struct expr *name= expr_create_name(n);
    struct expr *eva = expr_create(EXPR_VAR_ARRAY,name,index);
    return eva;
}

struct expr * expr_create_call(char *name, struct expr *expr)
{
    struct expr *n = expr_create_name(name);
    struct expr *ec = expr_create(EXPR_CALL, n, expr);
    return ec;
}

struct expr * expr_create_arg(struct expr *argl, struct expr *next)
{
    struct expr *arg = expr_create(EXPR_ARG,argl,next);
    return arg;
}

