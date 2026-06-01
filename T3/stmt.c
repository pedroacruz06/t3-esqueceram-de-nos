/* stmt.c
 * Adaptação de partes do código do livro de Compiladores
 * de Douglas Thain para a disciplina MATA61-UFBA
 * Christina von Flach (github: christinaflach)
 * 2023
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "stmt.h"

struct stmt * stmt_create(stmt_t kind,
    struct decl *decl, struct expr *init_expr,
    struct expr *expr, struct expr *next_expr,
    struct stmt *body, struct stmt *else_body,
    struct stmt *next)
{
    struct stmt *s = malloc(sizeof(*s));
    if (s) {
        s->kind = kind;
        s->decl = decl;
        s->init_expr = init_expr;
        s->expr = expr;
        s->next_expr = next_expr;
        s->body = body;
        s->else_body = else_body;
        s->next = next;
    }
    else {
        fprintf(stderr,"Fatal error: not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return s;
}

struct stmt *insert_stmt(struct stmt *head,
                         struct stmt *elem) {
    struct stmt *p = head;
    struct stmt *i = elem;
    while (p->next) {
        p = p->next;
    }
    p->next = i;
    return head;
}

struct stmt * assign_stmt_create(struct expr *init_var,
                struct expr *expr)
{
    struct stmt *as = stmt_create(STMT_ASSIGN,0,init_var,expr,0,0,0,0);
    return as; 
}

struct stmt * block_stmt_create(struct decl *localdecl,
                struct stmt *body)
{
    struct stmt *bs =
        stmt_create(STMT_BLOCK,localdecl,0,0,0,body,0,0);
    return bs;
}

struct stmt * if_stmt_create(struct expr *expr,
                        struct stmt *body)
{
    struct stmt *ifs =
        stmt_create(STMT_IF_ELSE,0,0,expr,0,body,0,0);
    return ifs;
}

struct stmt * if_else_stmt_create(struct expr *expr,
                             struct stmt *body,
                             struct stmt *else_body)
{
    struct stmt *ifs =
        stmt_create(STMT_IF_ELSE,0,0,expr,0,body,else_body,0);
    return ifs;
}

struct stmt * while_stmt_create(struct expr *expr,
                           struct stmt *body)
{
    struct stmt *ws =
        stmt_create(STMT_WHILE,0,0,expr,0,body,0,0);
    return ws;
}

struct stmt * print_stmt_create(struct expr *expr) {
    struct stmt *ps =
        stmt_create(STMT_PRINT,0,0,expr,0,0,0,0);
    return ps;
}

struct stmt * func_stmt_create(struct expr *expr) {
    struct stmt *fs =
        stmt_create(STMT_EXPR,0,0,expr,0,0,0,0);
    return fs;
}

struct stmt * return_stmt_create(struct expr *expr) {
    struct stmt *rs =
        stmt_create(STMT_RETURN,0,0,expr,0,0,0,0);
    return rs;
}

