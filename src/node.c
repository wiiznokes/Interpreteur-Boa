#include <stdlib.h>
#include <stdio.h>

#include "node.h"

node *new_node(NodeType type)
{
    node *n = malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;

    n->type = type;
    return n;
}

void free_node(node *n)
{
    free(n);
}

char *node_type_to_text(NodeType type)
{
    switch (type)
    {
    case N_INSTRUCTION:
        return "N_INSTRUCTION";

    case N_INITIALISATION:
        return "N_INITIALISATION";
    case N_ASSIGNATION:
        return "N_ASSIGNATION";
    case N_VARIABLE:
        return "N_VARIABLE";
    case N_CALL:
        return "N_CALL";

    case N_OPERATION:
        return "N_OPERATION";
    case N_VALUE:
        return "N_VALUE";

    case N_CONDITION:
        return "N_CONDITION";
    case N_FUN:
        return "N_FUN";
    case N_RETURN:
        return "N_RETURN";

    default:
        printf("internal error: node_type_to_text\n");
        exit(1);
    }
}

char *data_type_to_text(DataType type)
{
    switch (type)
    {
    case D_UNDEFINED:
        return "D_UNDEFINED";
    case D_UNIT:
        return "D_UNIT";
    case D_INT:
        return "D_INT";
    case D_CHAR:
        return "D_CHAR";
    default:
        printf("internal error: data_type_to_text\n");
        exit(1);
    }
}

char *operateur_to_text(Operateur op)
{
    switch (op)
    {
    case O_PLUS:
        return "O_PLUS";
    case O_MINUS:
        return "O_MINUS";
    case O_MUL:
        return "O_MUL";
    case O_DIV:
        return "O_DIV";
    case O_EQUAL:
        return "O_EQUAL";
    case O_LESS:
        return "O_LESS";
    case O_MORE:
        return "O_MORE";
    case O_LESS_EQUAL:
        return "O_LESS_EQUAL";
    case O_MORE_EQUAL:
        return "O_MORE_EQUAL";
    case O_OR:
        return "O_OR";
    case O_AND:
        return "O_AND";
    case O_NOT_EQUAL:
        return "O_NOT_EQUAL";
    case O_NOT:
        return "O_NOT";
    default:
        printf("internal error: data_type_to_text\n");
        exit(1);
    }
}