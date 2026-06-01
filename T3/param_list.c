/* param_list.c
 * Adaptação de partes do código do livro de Compiladores
 * de Douglas Thain para a disciplina MATA61-UFBA
 * Christina von Flach (github: christinaflach)
 * 2023
 */ 

#include <stdlib.h>
#include <stdio.h> 
#include "param_list.h"

struct param_list * param_create(char *name, 
    struct type *type)
{
    struct param_list *pl = malloc(sizeof(*pl));
    if (pl) {
        pl->name = name;
        pl->type = type;
        pl->next = 0;
    }
    else {
        fprintf(stderr,"Fatal error: not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return pl;
}

struct param_list *insert_param(struct param_list *head,
   struct param_list *elem) 
{
    struct param_list *p = head;
    struct param_list *i = elem;
    while (p->next) {
        p = p->next;
    }
    p->next = i;
    return head;
}


