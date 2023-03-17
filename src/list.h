#ifndef LIST_H
#define LIST_H

#include "stdbool.h"


typedef struct _node_ {
	char *val;
	struct _node_ *next;
} node;


typedef struct _list_ {
	node *tete;
} list;



void free_list(list* l);



void add_tete(list* l, char *c);


#endif


