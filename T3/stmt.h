#ifndef STMT_H
#define STMT_H

typedef enum {
        STMT_ASSIGN,
	STMT_DECL,
	STMT_EXPR,
	STMT_IF,
	STMT_IF_ELSE,
	STMT_WHILE,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt * stmt_create(stmt_t kind, 
                          struct decl *decl, 
                          struct expr *init_expr, 
                          struct expr *expr, struct expr *next_expr, 
                          struct stmt *body, 
                          struct stmt *else_body, 
                          struct stmt *next);

struct stmt *insert_stmt(struct stmt *head,
                         struct stmt *elem);

struct stmt * block_stmt_create(struct decl *localdecl,
                struct stmt *body);

struct stmt * assign_stmt_create(struct expr *var,
                struct expr *expr);

struct stmt * if_stmt_create(struct expr *expr,
                        struct stmt *body);

struct stmt * if_else_stmt_create(struct expr *expr,
                             struct stmt *body,
                             struct stmt *else_body);

struct stmt * while_stmt_create(struct expr *expr,
                           struct stmt *body);

struct stmt * return_stmt_create(struct expr *expr);

struct stmt * print_stmt_create(struct expr *expr);

struct stmt * func_stmt_create(struct expr *expr);

#endif
