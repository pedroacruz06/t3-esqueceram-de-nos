#ifndef TYPE_H
#define TYPE_H

typedef enum {
	TYPE_VOID,
	TYPE_BOOLEAN,
	TYPE_INTEGER,
	TYPE_ARRAY,
	TYPE_FUNCTION,
} type_t;

struct type {
	type_t kind;
	struct param_list *params;
	struct type *subtype;
        struct expr *expr; // for index
};

struct type *type_create(type_t kind, 
                         struct param_list *params,
                         struct type *subtype, struct expr *expr);

struct type * func_type_create(struct param_list *params,
                  struct type *subtype);

struct type * array_type_create(int value, struct type *subtype);

void type_print(struct type *t);

#endif
