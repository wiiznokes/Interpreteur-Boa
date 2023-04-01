#include "string.h"
#include "stdio.h"

#include "variable.h"
#include "lexical_analyse.h"




list global_var;


char log_message[200];



bool add_global(node *n) {

    if(global_var.size == 0) {
        add_tail(&global_var, n);
        return true;
    }


    node *tmp = global_var.head;

    while(tmp->right != NULL) {

    
        if (!strcmp(tmp->var->name, n->var->name)) {
            snprintf(log_message, 200, "variable %s already defined",
                n->var->name);
            show_error(log_message);
        }
        tmp = tmp->right;
    }

    add_tail(&global_var, n);
}




node *new_variable(char *name, data_t type) {

    node *n = new_node(N_VARIABLE);

    variable_t *var = malloc(sizeof(variable_t));

    strcpy(var->name, name);
    var->type = type;
    
    n->var = var;

    return n;
}




node *get_by_name(char *name) {

    if(global_var.size == 0) {
        return NULL;
    }


    node *tmp = global_var.head;

    while(tmp != NULL) {

        if (!strcmp(tmp->var->name, name)) {
            return tmp;
        }

        tmp = tmp->right;
    }

    return NULL;
}



data_t check_variable(char *name, data_t type) {

    node *n = get_by_name(name);

    if (n == NULL) {
        return D_UNDEFINED;
    }

    if (type == D_UNDEFINED) {
        return n->var->type;
    }

    if (type == n->var->type) {
        return type;
    }
    else {
        return D_UNDEFINED;
    }
}









show_error(char *msg) {
    printf("Erreur variable %d:%d : %s\n",
           get_lexeme().line,
           get_lexeme().column,
           msg
    );
}
