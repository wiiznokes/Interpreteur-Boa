#include <stdio.h>
#include <stdlib.h>

#include "list.h"




void free_list(list* l) {
    while(l->tete != NULL){
        node *tmp = l->tete;
        l->tete = l->tete->next;
        free(tmp);
    }
}


void add_tete(list* l, char *c) {
    if (l == NULL) {
        printf("error: can't add a node, pointer null\n");
        return;
    }

    node* node = malloc(sizeof(node));
    node->val = c;
    node->next = l->tete;
    l->tete = node;

    return;
}

