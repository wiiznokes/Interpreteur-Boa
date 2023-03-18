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

// Helper function to recursively print a tree
static void print_tree_helper(tree t, int depth)
{
    if (t == NULL)
    {
        return;
    }
    print_tree_helper(t->right, depth + 1);
    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }
    print_node(t);
    print_tree_helper(t->left, depth + 1);
}

void print_tree(tree t)
{
    print_tree_helper(t, 0);
}