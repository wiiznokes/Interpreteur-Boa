#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "list.h"


#define MAX_STACK 1000


typedef struct
{
    int size;
    list *stack[MAX_STACK];
} Stack;


Stack stack;


/* ****************
    private
*/

node *get_by_name(char *name);


/* ************** */



void start_stack() {
    stack.stack[0] = new_list();
    stack.size = 1;
}
void free_stack() {
    for (int i = 0; i < stack.size; i++) {
        free_list(stack.stack[i]);
    }
    stack.size = 0;
}


bool up() {
    if (stack.size >= MAX_STACK) {
        printf("error: stack overflow, you reatch the limit of %d\n", MAX_STACK);
        return false;
    } 

    stack.stack[stack.size] = new_list();
    stack.size++;

    return true;
}

void down() {
    stack.size--;

    if (stack.size < 1) {
        printf("internal error: down stack, size < 1\n");
        exit(1);
    }

    free_list(stack.stack[stack.size]);
}



void add_global(node *n) {
    if (n == NULL) {
        printf("internal error: add_global\n");
        exit(1);
    }

    if(!add_tail(stack.stack[0], n)) {
        exit(1);
    }
}


void add_local(node *n) {

}

char *get_char(char *name) {
    node *n = get_by_name(name);

    return n->string;
}


int get_int(char *name) {
    node *n = get_by_name(name);

    return n->number;
}

void set_char(char *name, char *value) {
    node *n = get_by_name(name);
    strcpy(n->string, value);
}

void set_int(char *name, int value) {
    node *n = get_by_name(name);
    n->number = value;
}





node *get_by_name(char *name) {

    // globals
    list *vars = stack.stack[0];

    if (vars == NULL) {
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

    if (stack.size <= 1) {
        if (vars == NULL) {
            printf("internal error: get_by_name\n");
            exit(1);
        }
    }

    // locals
    vars = stack.stack[stack.size];

    if (vars == NULL) {
        printf("internal error: get_by_name\n");
        exit(1);
    }


    while (tmp)
    {
        if (!strcmp(tmp->name, name))
            return tmp;
        tmp = tmp->right;
    }

    printf("internal error: get_by_name\n");
    exit(1);
}