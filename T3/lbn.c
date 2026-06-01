/* lbn.c
 * Christina von Flach (github: christinaflach)
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lbn.h"

extern FILE * yyout; 

/* print in LBN */

void print_name(char *name) {
    fprintf(yyout,"[%s]", name);
}

void print_type(struct type *type) {
  struct type *t = type;
  if (t) {
    switch(t->kind) {
        case TYPE_VOID: {
            fprintf(yyout,"[void]");
            break;
        }
        case TYPE_INTEGER: {
            fprintf(yyout,"[integer]");
            break;
        }
	case TYPE_BOOLEAN: {
            fprintf(yyout,"[boolean]");
            break;
        }
        case TYPE_FUNCTION: {
            if (t->subtype)
                print_type(t->subtype);
            break;
        }
        case TYPE_ARRAY: {
            if (t->subtype)
               print_type(t->subtype);
            break;
        }
        default: break;
     }
   }
}

void print_params(struct param_list *pl){
    struct param_list *p = pl;
    while (p) {
        fprintf(yyout,"\n[param ");
        fprintf(yyout,"[%s]",p->name);
        print_type(p->type);
        fprintf(yyout,"]");
        p = p->next;
    }
}

void print_var(struct decl *var) {
     fprintf(yyout,"\n[var-declaration ");
     print_name(var->name);
     print_type(var->type);
     if (var->expr!=0)
	print_expr(var->expr);
     fprintf(yyout,"]");
}

void print_func(struct decl *func) {
    fprintf(yyout,"\n[func-declaration \n");
    print_type(func->type);
    fprintf(yyout,"\n");
    print_name(func->name);
    fprintf(yyout,"\n[params");
    struct type *t = func->type;
    if (t->params)
        print_params(t->params);
    fprintf(yyout,"]");
    if (func->code)
       print_stmt(func->code);
    fprintf(yyout,"]");
}

void print_array(struct decl *func) {
    fprintf(yyout,"\n[array-declaration \n]");
}

void print_decl(struct decl *decl) {
  while (decl) {
    struct type *t = decl->type;
    switch(t->kind) {
        case TYPE_VOID: {
            fprintf(yyout,"[void]");
            break;
        }
	case TYPE_INTEGER: {
	    print_var(decl);
            break;
        }
	case TYPE_BOOLEAN: {
            print_var(decl);
            break;
        }
        case TYPE_FUNCTION: {
            print_func(decl);
            break;
        }
        case TYPE_ARRAY: {
            print_array(decl);
            break;
        }
        default: {
            fprintf(yyout,"tipo desconhecido\n");
            break;
        }
     }
     decl = decl->next;
   }
}

void print_stmt(struct stmt *s) {
  while (s) {
    switch(s->kind) {
        case STMT_ASSIGN: {
            print_bexpr("=", s->init_expr, s->expr);
            break;
        }
        case STMT_EXPR: {
            fprintf(yyout,"\n[call ");
            fprintf(yyout,"\n");
            struct expr *e = s->expr;
            print_expr(e->left);
            fprintf(yyout,"\n[args ");
            if (e->right)
               print_expr(e->right);
            else
               fprintf(yyout,"[]");
            fprintf(yyout,"]\n");
            fprintf(yyout,"]");
            break;
        }

        case STMT_IF_ELSE: {
            fprintf(yyout,"\n[selection-stmt ");
            print_expr(s->expr);
            print_stmt(s->body);
            if (s->else_body)
                print_stmt(s->else_body);
            fprintf(yyout,"]");
            break;
        }
        case STMT_WHILE: {
            fprintf(yyout,"\n[iteration-stmt ");
            print_expr(s->expr);
            print_stmt(s->body);
            fprintf(yyout,"]");
            break;
        }
        case STMT_PRINT: {
	    fprintf(yyout,"\n[print-stmt ");
	  //  fprintf(yyout,"\n[args ");
            if (s->expr)
                print_expr(s->expr);
	  //  fprintf(yyout,"]");
            fprintf(yyout,"]");
            break;
        }
        case STMT_RETURN: {
            fprintf(yyout,"\n[return-stmt ");
            if (s->expr)
                print_expr(s->expr);
            else
                fprintf(yyout,"[;]\n");
            fprintf(yyout,"]");
            break;
        }
        case STMT_BLOCK: {
            fprintf(yyout,"\n[block ");
            if (s->decl)
                print_decl(s->decl);
            if (s->body)
                print_stmt(s->body);
            fprintf(yyout,"]");
            break;
        }
        default: break;
     }
     s = s->next;
  }
}

void print_bexpr(char *c, struct expr *l, struct expr *r) {
    fprintf(yyout,"\n[%s ",c);
    print_expr(l);
    if (r) print_expr(r);
    fprintf(yyout,"]");
}

void print_expr(struct expr *e) {
    if (e) {
    switch(e->kind) {
        case EXPR_ADD: {
            print_bexpr("+", e->left, e->right);
            break;
        }
        case EXPR_SUB:
        {
            print_bexpr("-", e->left, e->right);
            break;
        }
        case EXPR_MUL: {
            print_bexpr("*", e->left, e->right);
            break;
        }
        case EXPR_DIV:
        {
            print_bexpr("/", e->left, e->right);
            break;
        }
        case EXPR_NAME: {
            fprintf(yyout,"[%s]", e->name);
            break;
        }
        case EXPR_VAR: {
            fprintf(yyout,"\n[var ");
            print_expr(e->left);
            fprintf(yyout,"]");
            break;
        }
        case EXPR_VAR_ARRAY: {
            fprintf(yyout,"\n[var-array ");
            print_expr(e->left);
            if (e->right)
               print_expr(e->right);
            fprintf(yyout,"]");
            break;
        }
        case EXPR_INTEGER_LITERAL: {
            fprintf(yyout,"[");
            int i = e->integer_value;
            fprintf(yyout,"%d", i);
            fprintf(yyout,"]");
            break;
        }
        case EXPR_BOOLEAN_LITERAL: {
            fprintf(yyout,"[");
            int i = e->integer_value;
	    if (i == 1) 
               fprintf(yyout,"true");
	    else
	       fprintf(yyout,"false");
            fprintf(yyout,"]");
            break;
        }
        case EXPR_EQ:
        {
            print_bexpr("==", e->left, e->right);
            break;
        }
        case EXPR_NEQ:
        {
            print_bexpr("!=", e->left, e->right);
            break;
        }
        case EXPR_LT:
        {
            print_bexpr("<", e->left, e->right);
            break;
        }
        case EXPR_GT:
        {
            print_bexpr(">", e->left, e->right);
            break;
        }
        case EXPR_LTEQ:
        {
            print_bexpr("<=", e->left, e->right);
            break;
	}
        case EXPR_GTEQ:
        {
            print_bexpr(">=", e->left, e->right);
            break;
        }
        case EXPR_CALL: {
            fprintf(yyout,"\n[call ");
            fprintf(yyout,"\n");
            print_expr(e->left);
            fprintf(yyout,"\n[args ");
            if (e->right)
               print_expr(e->right);
            else
               fprintf(yyout,"[]");
            fprintf(yyout,"]\n");
            fprintf(yyout,"]");
            break;
        }
        case EXPR_ARG:  {
            print_expr(e->right);
            print_expr(e->left);
            break;
        }
        default: {
            fprintf(yyout,"internal error:\n");
        }
    }
  }
}


void print_AST(struct decl *program) {
    fprintf(yyout,"[program ");
    print_decl(program);
    fprintf(yyout,"\n]\n");
}

