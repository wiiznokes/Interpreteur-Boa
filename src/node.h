#ifndef NODE_H
#define NODE_H

typedef enum
{
    // il en manque bcp
    
    OPERATEUR,
    VALEUR
} node_type;

typedef enum
{
    N_PLUS,
    N_MUL,
    N_MOINS,
    N_DIV
} TypeOperateur;

typedef struct node
{
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

node *new_node(node_type type);

void free_node(node *n);

void print_node(node *n);

#endif