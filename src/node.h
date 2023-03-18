#ifndef NODE_H
#define NODE_H

typedef struct node {
    struct node *right;
    struct node *left;


	char *val;
} node;


node* new_node();

void free_node(node *n);

void print_node(node *n);

#endif