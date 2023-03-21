#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"

int main(int argc, char **argv)
{

    node *n1 = new_node(VALEUR);
    node *n2 = new_node(VALEUR);
    node *n3 = new_node(VALEUR);
    node *n4 = new_node(VALEUR);
    node *n5 = new_node(OPERATEUR);
    node *n6 = new_node(OPERATEUR);

/*

    list *l = new_list();

    add_head(l, n1);
    add_tail(l, n2);
    add_tail(l, n3);
    add_tail(l, n4);
    add_index(l, n5, 3);
    print_list(l);

    add_index(l, n6, 1);
    print_list(l);

    remove_index(l, 1);
    print_list(l);


    clear_list(l);
    print_list(l);

    free_list(l);

*/
    tree t = NULL;

    t = n1;

    t->right = n2;

    t->right->left = n3;

    t->left = n4;



    print_tree(t);

    free_tree(t);



    return 0;
}