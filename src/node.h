#ifndef NODE_H
#define NODE_H


typedef enum {
    // rempli un peu au pif pour l'instant, manque de truc
    UN_DEFINED,
    INSTRUCTION,
    VARIABLE,
    FUNCTION
} node_type;

typedef struct node {
    struct node *right;
    struct node *left;

    node_type type;

    char *key; // pourra representé le nom d'une fonction, ou du variable


    /*
        pointeur vers une structure générique
        permettra d'avoir une structure pour chaque node_type
        en utilisant l'interface de list.h tt le temps
    */
	void *ptr;
} node;


node* new_node();

void free_node(node *n);

void print_node(node *n);

#endif