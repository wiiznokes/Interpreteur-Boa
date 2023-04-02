#ifndef NODE_H
#define NODE_H



typedef enum
{
    N_INSTRUCTION,
    
    N_INITIALISATION,
    N_ASSIGNATION,
    N_VARIABLE,


    N_OPERATION,
    N_VALUE,

    N_FUN

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
    O_PLUS,
    O_MUL,
    O_MINUS,
    O_DIV
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
    int number;
    char string[256];

    // operateur
    Operateur op;

    // function
    DataType return_type;


} node;




node *new_node(NodeType type);

void free_node(node *n);


char *node_type_to_text(NodeType type);

char *data_type_to_text(DataType type);

#endif