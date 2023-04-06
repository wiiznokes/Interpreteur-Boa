#ifndef NODE_H
#define NODE_H



typedef enum
{
    N_INSTRUCTION,
    
    N_INITIALISATION,
    N_ASSIGNATION,
    N_VARIABLE,
    N_CALL,


    N_OPERATION,
    N_VALUE,

    N_CONDITION,
    N_FUN,
    N_RETURN

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
    O_MINUS,
    O_MUL,
    O_DIV,
    O_EQUAL,
    O_LESS,
    O_MORE,
    O_LESS_EQUAL,
    O_MORE_EQUAL,
    O_OR,
    O_AND,
    O_NOT_EQUAL,
    O_NOT,

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


} node;




node *new_node(NodeType type);

void free_node(node *n);


char *node_type_to_text(NodeType type);
char *data_type_to_text(DataType type);
char *operateur_to_text(Operateur op);

#endif