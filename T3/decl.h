#ifndef DECL_H
#define DECL_H

#include "param_list.h"
#include "type.h"
#include "expr.h"

struct decl {
	char *name;
	struct type *type;
	struct expr *expr;
	struct stmt *code;
	struct decl *next;
};

struct decl * decl_create(char *name, 
   struct type *type, 
   struct expr *value, 
   struct stmt *code, 
   struct decl *next);

struct decl * insert_decl(struct decl *head,
                         struct decl *elem);

struct decl * var_decl_create(char *name, 
   struct type *type, struct expr *init);

struct decl * func_decl_create(char *name,
    struct type *type,
    struct stmt *body);

#endif

