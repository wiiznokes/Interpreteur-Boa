#ifndef NODE_H
#define NODE_H





typedef enum
{
    N_INITIALISATION,
    N_ASSIGNATION,
    N_VARIABLE,
    N_IF,
    N_ELSE,
    N_WHILE,
    N_FOR,
    N_FUN,
    
    N_OPERATEUR,
    N_STRING,
    N_NUMBER
} node_type;

typedef enum
{
    N_PLUS,
    N_MUL,
    N_MOINS,
    N_DIV
} bin_operateur;


typedef struct node
{
    struct node *right;
    struct node *left;

    node_type type;

    // optionnal

    variable_t *var;
    bin_operateur op;

    int value;
    char *string;
} node;




node *new_node(node_type type);

void free_node(node *n);


char *node_type_to_text(node_type type);


#endif