#ifndef LIST_H
#define LIST_H


#include "stdbool.h"


#include "node.h"


typedef struct
{
	int size;
	node *head;
	node *tail;
} list;

list *new_list(void);
void clear_list(list *l);
void free_list(list *l);

bool remove_head(list *l);
bool remove_tail(list *l);
bool remove_index(list *l, int index);

bool add_head(list *l, node *n);
bool add_tail(list *l, node *n);
bool add_index(list *l, node *n, int index);

node *get_node(list *l, int index);

void print_list(list *l);

#endif
