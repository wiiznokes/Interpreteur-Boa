#ifndef TREE_H
#define TREE_H

#include "node.h"

typedef struct node *tree;


void free_tree(tree t);

void print_tree(tree t);

#endif
