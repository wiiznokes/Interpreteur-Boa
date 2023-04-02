#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "variable.h"
#include "lexical_analyse.h"
#include "node.h"



/* ***************
    private
*/


list *globals;
list *locals;


void show_error(char *msg);


/*
    returns the node with the corresponding name (count <= 1 by impl)
    or returns NULL
*/
node *get_by_name_analyse(char *name);

/* ********************* */

bool add_global_analyse(node *n)
{

    if (n == NULL)
    {
        printf("internal error: add_global\n");
        exit(1);
    }

    if (n->type != N_VARIABLE && n->type != N_FUN)
    {
        printf("internal error: add_global\n");
        exit(1);
    }

    node *tmp = globals->head;

    while (tmp)
    {
        if (!strcmp(tmp->name, n->name))
        {
            show_error("variable already defined");
            return false;
        }
        tmp = tmp->right;
    }

    add_tail(globals, n);
    return true;
}

bool add_local_analyse(node *n)
{
    if (n == NULL)
    {
        printf("internal error: add_local\n");
        exit(1);
    }

    if (n->type != N_VARIABLE)
    {
        printf("internal error: add_local\n");
        exit(1);
    }

    if (!get_by_name_analyse(n->name))
    {
        add_tail(locals, n);
        return true;
    }

    return false;
}

void clear_local()
{
    clear_list(locals);
}

node *get_by_name_analyse(char *name)
{

    node *tmp = globals->head;

    while (tmp)
    {
        if (!strcmp(tmp->name, name))
            return tmp;
        tmp = tmp->right;
    }

    tmp = locals->head;

    while (tmp)
    {
        if (!strcmp(tmp->name, name))
            return tmp;
        tmp = tmp->right;
    }

    return NULL;
}

DataType check_variable(
    char *name,
    DataType data_type,
    bool show_error_if_undefined)
{

    node *n = get_by_name_analyse(name);

    if (n == NULL)
    {
        if (show_error_if_undefined)
        {
            printf("variable %s is not defined\n", name);
        }
        return D_UNDEFINED;
    }

    if (data_type == D_UNDEFINED)
    {
        return n->data_type;
    }

    if (data_type == n->data_type)
    {
        return data_type;
    }
    else
    {
        printf("variable %s n'a pas le type %s\n", name, data_type_to_text(data_type));
        return D_UNDEFINED;
    }
}

void show_error(char *msg)
{
    printf("Erreur variable %d:%d : %s\n",
           get_lexeme().line,
           get_lexeme().column,
           msg);
}



void start_variable() {
    globals = new_list();
    locals = new_list();
}

void stop_variable() {
    free_list(globals);
    free_list(locals);
}