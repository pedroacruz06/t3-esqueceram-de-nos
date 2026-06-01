#ifndef PARAM_LIST_H
#define PARAM_LIST_H

struct param_list {
	char *name;
	struct type *type;
	struct param_list *next;
};

struct param_list * param_create(char *name, 
    struct type *type);

struct param_list *insert_param(struct param_list *head,
                         struct param_list *elem);

void param_list_print(struct param_list *a);

#endif
