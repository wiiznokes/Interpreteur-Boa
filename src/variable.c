#include "string.h"
#include "stdio.h"

#include "variable.h"
#include "lexical_analyse.h"
#include "node.h"



list globals;

list locals;


void show_error(char *msg);
char log_message[200];



bool add_global(node *n) {

    if(globals.size == 0) {
        add_tail(&globals, n);
        return true;
    }


    node *tmp = globals.head;

    while(tmp != NULL) {

        if (!strcmp(tmp->name, n->name)) {
            snprintf(log_message, 200, "variable %s already defined",
                n->name);
            show_error(log_message);
            return false;
        }
        tmp = tmp->right;
    }

    add_tail(&globals, n);
    return true;
}





node *get_by_name(char *name) {

    if(globals.size == 0) {
        return NULL;
    }


    node *tmp = globals.head;

    while(tmp != NULL) {

        if (!strcmp(tmp->name, name)) {
            return tmp;
        }

        tmp = tmp->right;
    }

    return NULL;
}



DataType check_variable(NodeType nodeType, char *name, DataType dataType) {

    node *n = get_by_name(name);

    if (n == NULL) {
        return D_UNDEFINED;
    }

    if (dataType == D_UNDEFINED) {
        return n->data_type;
    }

    if (dataType == n->data_type) {
        return dataType;
    }
    else {
        return D_UNDEFINED;
    }
}









void show_error(char *msg) {
    printf("Erreur variable %d:%d : %s\n",
           get_lexeme().line,
           get_lexeme().column,
           msg
    );
}
