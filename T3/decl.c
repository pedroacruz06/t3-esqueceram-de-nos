/* decl.c
 * Adaptação de partes do código do livro de Compiladores
 * de Douglas Thain para a disciplina MATA61-UFBA
 * Christina von Flach (github: christinaflach)
 * 2023
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "decl.h"

struct decl * decl_create(char *name, 
       struct type *type,
       struct expr *expr,
       struct stmt *code,
       struct decl *next)
{
    struct decl *d = malloc(sizeof(*d));
    if (d) {
        d->name = name;
        d->type = type;
        d->expr = expr;
        d->code = code;
        d->next = next;
    }
    else {
        fprintf(stderr,"Fatal error: not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return d;
}

struct decl *insert_decl(struct decl *head,
                         struct decl *elem) 
{
    struct decl *p = head;
    struct decl *i = elem;
    while (p->next) {
        p = p->next;
    }
    p->next = i;
    return head;
}

struct decl * var_decl_create(char *name, 
    struct type *type, struct expr *init)
{
    struct decl *vd = decl_create(name, type, init, 0, 0);
    return vd;
}

struct decl * func_decl_create(char *name, 
    struct type *type, 
    struct stmt *body)
{
    struct decl *fd = decl_create(name,type,0,body,0);
    return fd;
}


