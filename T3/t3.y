/* t3.y */

%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s, ...);
int yylex();
%}



/* definicoes de tokens */

%token <num> NUM
%token ARRAYT
%token BOOLEANT
%token FALSET
%token TRUET
%token IFT
%token ELSET
%token WHILET
%token FUNCTIONT
%token INTEGERT
%token VOIDT
%token PRINTT
%token RETURNT
%token <str> ID
%token EQT
%token GTET
%token LTET
%token NEQT

%token COMMA
%token COLON
%token SEMICOLON
%token EQUALS
%token GT
%token LT
%token NOT
%token LBRACKET
%token RBRACKET
%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE

%token PLUS
%token MINUS
%token TIMES
%token DIV

%token ERROR

%union {
    int num;
    char* str;
}

%nonassoc EQT GTET LTET NEQT GT LT

%left PLUS MINUS
%left TIMES DIV
%right NOT UMINUS

%start program

%%
program
: var_list func_list    /* variáveis e depois funções */
;

var_list
: var_list var_decl
| 
;

var_decl
: ID COLON var_type SEMICOLON
;

var_type
: INTEGERT var_assignment
| BOOLEANT var_assignment
| ARRAYT LBRACKET NUM RBRACKET array_type array_assignment
;

var_assignment
: EQUALS expr
|
;

array_type
: INTEGERT
| BOOLEANT
;

array_assignment
: EQUALS LBRACE arr_list RBRACE
|
;

arr_list
: arr_elem COMMA arr_list
| arr_elem
;

arr_elem
: NUM
| FALSET
| TRUET
;

func_list
: func_list func_decl
| func_decl
;

func_decl
: ID COLON FUNCTIONT func_type LPAREN param_list RPAREN EQUALS block
| ID COLON FUNCTIONT func_type LPAREN RPAREN EQUALS block
;

func_type
: INTEGERT
| BOOLEANT
| VOIDT
;

param_list
: param COMMA param_list
| param
;

param
: ID COLON param_type
;

param_type
: INTEGERT
| BOOLEANT
| ARRAYT LBRACKET RBRACKET array_type
;

block
: LBRACE var_list stmt_list RBRACE
;

stmt_list
: stmt_list stmt
| stmt
;

stmt
: ID EQUALS expr SEMICOLON
| ID LBRACKET expr RBRACKET EQUALS expr SEMICOLON
| RETURNT expr SEMICOLON
| RETURNT SEMICOLON
| PRINTT LPAREN expr_list RPAREN SEMICOLON
| ID LPAREN arg_list RPAREN SEMICOLON
| ID LPAREN RPAREN SEMICOLON
| IFT LPAREN expr RPAREN body %prec IFT
| IFT LPAREN expr RPAREN body ELSET body
| WHILET LPAREN expr RPAREN block
;

body
: cond_block
| stmt
;

cond_block
: LBRACE stmt_list RBRACE
;

expr_list
: expr_list COMMA expr
| expr
;

arg_list
: arg_list COMMA expr
| expr
;

expr
: ID LPAREN RPAREN
| ID LPAREN arg_list RPAREN
| expr PLUS  expr
| expr MINUS expr
| expr TIMES expr
| expr DIV   expr
| expr EQT   expr
| expr NEQT  expr
| expr GT    expr
| expr LT    expr
| expr GTET  expr
| expr LTET  expr
| NOT   expr
| MINUS expr  %prec UMINUS
| LPAREN expr RPAREN
| term
;

term
: NUM
| TRUET
| FALSET
| ID
| ID LBRACKET expr RBRACKET
;

%%
