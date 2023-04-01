#ifndef NODE_H
#define NODE_H



typedef enum
{
    N_INITIALISATION,
    N_ASSIGNATION,
    N_VARIABLE,


    N_OPERATEUR,
    N_STRING,
    N_NUMBER,


    N_IF,
    N_ELSE,

    N_FUN,
    N_ARG,
    N_RETURN_TYPE

} NodeType;


typedef enum
{
    D_UNDEFINED,
    D_UNIT, // mean nothing (void)
    D_INT,
    D_CHAR
} DataType;



typedef enum
{
    N_PLUS,
    N_MUL,
    N_MOINS,
    N_DIV
} Operateur;


typedef struct node
{
    struct node *right;
    struct node *left;

    NodeType type;

    /*
        Optional
        todo: utiliser union ?
    */

    // variable
    char name[256];
    DataType data_type;

    // valeur
    int integer;
    char string[256];

    // operateur
    Operateur op;

    // function
    DataType return_type;


} node;




node *new_node(NodeType type);

void free_node(node *n);


char *node_type_to_text(NodeType type);


#endif