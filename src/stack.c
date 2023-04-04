#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "list.h"

#define MAX_STACK 1000

int stack_count;
int scope_count[MAX_STACK];
list *stack[MAX_STACK][MAX_STACK];

/* ****************
    private
*/

node *get_by_name(char *name);

int *get_scope_count() { return &scope_count[stack_count - 1]; }

list **get_last_scope() { return &stack[stack_count - 1][*get_scope_count() - 1]; }

/* ************** */

void start_stack()
{
    stack_count = 0;
    *get_scope_count() = 0;
    up_stack();
}

void free_stack()
{
    while (stack_count > 0)
    {
        down_stack();
    }

    stack_count = 0;
    *get_scope_count() = 0;
}

bool up_stack()
{
    if (stack_count >= MAX_STACK)
    {
        printf("error: stack overflow, you reatch the limit of %d\n", MAX_STACK);
        return false;
    }

    stack_count++;
    stack[stack_count - 1][0] = new_list();
    *get_scope_count() = 1;

    return true;
}

void down_stack()
{
    if (stack_count < 1)
    {
        printf("internal error: down stack, size < 1\n");
        exit(1);
    }

    while (*get_scope_count() > 0)
    {
        down_scope();
    }
    stack_count--;
}

bool up_scope()
{
    if (*get_scope_count() >= MAX_STACK)
    {
        printf("error: stack overflow, you reatch the limit of %d\n", MAX_STACK);
        return false;
    }

    *get_scope_count() = *get_scope_count() + 1;
    *get_last_scope() = new_list();

    return true;
}

void down_scope()
{
    if (*get_scope_count() < 1)
    {
        printf("internal error: down_scope, size < 1\n");
        exit(1);
    }

    free_list(*get_last_scope());
    *get_scope_count() = *get_scope_count() - 1;
}

void add_stack(node *n)
{
    if (n == NULL)
    {
        printf("internal error: add_stack\n");
        exit(1);
    }

    if (!add_tail(*get_last_scope(), n))
    {
        printf("internal error: add_stack\n");
        exit(1);
    }
}

char *get_char(char *name)
{
    node *n = get_by_name(name);
    if (n == NULL || n->type != N_VARIABLE || n->data_type != D_CHAR)
    {
        printf("internal error: set_char\n");
        exit(1);
    }
    return n->string;
}

int get_int(char *name)
{
    node *n = get_by_name(name);
    if (n == NULL || n->type != N_VARIABLE || n->data_type != D_INT)
    {
        printf("internal error: set_int\n");
        exit(1);
    }
    return n->number;
}

void set_char(char *name, char *value)
{
    node *n = get_by_name(name);
    if (n == NULL || n->type != N_VARIABLE || n->data_type != D_CHAR)
    {
        printf("internal error: set_char\n");
        exit(1);
    }
    strcpy(n->string, value);
}

void set_int(char *name, int value)
{
    node *n = get_by_name(name);
    if (n == NULL || n->type != N_VARIABLE || n->data_type != D_INT)
    {
        printf("internal error: set_int\n");
        exit(1);
    }
    n->number = value;
}

node *get_fun(char *name)
{
    node *n = get_by_name(name);
    if (n == NULL || n->type != N_FUN)
    {
        printf("internal error: get_fun\n");
        exit(1);
    }
    return n;
}

DataType check_variable(
    char *name,
    DataType data_type,
    bool show_error_if_undefined)
{

    node *n = get_by_name(name);

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

node *get_by_name(char *name)
{
    for (int scope = 0; scope < scope_count[stack_count - 1]; scope++)
    {

        list *vars = stack[stack_count - 1][scope];

        if (vars == NULL)
        {
            printf("internal error: get_by_name\n");
            exit(1);
        }

        node *tmp = vars->head;

        while (tmp)
        {
            if (!strcmp(tmp->name, name))
                return tmp;
            tmp = tmp->right;
        }
    }

    return NULL;
}