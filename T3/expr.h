#ifndef EXPR_H
#define EXPR_H

typedef enum {
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
        EXPR_LT,
        EXPR_GT,
        EXPR_LTEQ,
        EXPR_GTEQ,
        EXPR_EQ,
        EXPR_NEQ,
	EXPR_BOOLEAN_LITERAL,
        EXPR_INTEGER_LITERAL,
	EXPR_NAME,
	EXPR_VAR,
	EXPR_VAR_ARRAY,
	EXPR_ARG,
	EXPR_CALL,
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	char *name;
	int integer_value;
};

struct expr * expression_create(expr_t kind, 
                                struct expr *left, 
                                struct expr *right, 
                                char *name, int value);

struct expr * expr_create(expr_t kind, 
                          struct expr *left, struct expr *right);

struct expr * expr_create_integer(int c);
struct expr * expr_create_boolean(int c);
struct expr * expr_create_name(char *name);
struct expr * expr_create_var(char *name);
struct expr * expr_create_var_array(char *name, struct expr *index);
struct expr * expr_create_call(char *name, struct expr *expr);
struct expr * expr_create_arg(struct expr *, struct expr *);

void expr_print(struct expr *e);

#endif

