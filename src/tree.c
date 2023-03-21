#include <stdlib.h>
#include <stdio.h>
#include "tree.h"



void free_tree(tree t)
{
    if (t == NULL)
    {
        return;
    }
    free_tree(t->left);
    free_tree(t->right);
    free_node(t);
}



/*
    Helper function to recursively print a tree

    type:   0 -> racine
            1 -> left
            2 -> right
*/
static void print_tree_helper(tree t, int depth, int type)
{
    if (t == NULL)
    {
        return;
    }
    print_tree_helper(t->left, depth + 1, 1);
    for (int i = 0; i < depth; i++)
    {
        printf("│   ");
    }
    switch (type)
    {
    case 0:
        printf("├── ");
        break;
    case 1:
        printf("┌── ");
        break;
    case 2:
        printf("└── ");
        break;
    default:
        exit(1);
    }
    print_node(t);
    print_tree_helper(t->right, depth + 1, 2);
}


void print_tree(tree t)
{
    print_tree_helper(t, 0, 0);
}