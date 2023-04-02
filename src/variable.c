#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "variable.h"
#include "lexical_analyse.h"
#include "node.h"


list globals;

list locals;


void show_error(char *msg);


bool add_global(node *n) {

    if (n == NULL) {
        printf("internal error: add_global\n");
        exit(1);
    }

    if (n->type != N_VARIABLE && n->type != N_FUN) {
        printf("internal error: add_global\n");
        exit(1);
    }

    node *tmp = globals.head;

    while(tmp) {
        if (!strcmp(tmp->name, n->name)) {
            show_error("variable already defined");
            return false;
        }
        tmp = tmp->right;
    }


    add_tail(&globals, n);
    return true;
}


bool add_local(node *n) {
    if (n == NULL) {
        printf("internal error: add_local\n");
        exit(1);
    }

    if (n->type != N_VARIABLE) {
        printf("internal error: add_local\n");
        exit(1);
    }

    if(!get_by_name(n->name)) {
        add_tail(&locals, n);
        return true;
    }

    return false;
    
}


void clear_local() {
    clear_list(&locals);
}



node *get_by_name(char *name) {
   
    node *tmp = globals.head;

    while(tmp) {
        if (!strcmp(tmp->name, name)) return tmp;
        tmp = tmp->right;
    }



    tmp = locals.head;

    while(tmp) {
        if (!strcmp(tmp->name, name)) return tmp;
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
