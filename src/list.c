#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list *new_list(void)
{
    list *l = malloc(sizeof(list));

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;

    return l;
}

void clear_list(list *l)
{
    while (l->head != NULL)
    {
        node *tmp = l->head;
        l->head = l->head->right;
        free_node(tmp);
    }
    l->tail = NULL;
    
    l->size = 0;
    
}

void free_list(list *l)
{

    clear_list(l);

    free(l);
}

bool remove_head(list *l)
{
    if (l == NULL)
    {
        printf("error remove_head: pointer null\n");
        return false;
    }
    if (l->size == 0)
    {
        printf("error remove_head: size = 0\n");
        return false;
    }

    if (l->head == NULL)
    {
        printf("internal error remove_head: head = null\n");
        exit(1);
    }

    node *tmp = l->head;
    l->head = l->head->right;

    if (l->size == 1)
    {
        l->tail = NULL;
    }

    free_node(tmp);
    l->size--;

    return true;
}

bool remove_tail(list *l)
{
    if (l == NULL)
    {
        printf("error remove_tail: pointer null\n");
        return false;
    }
    if (l->size == 0)
    {
        printf("error remove_tail: size = 0\n");
        return false;
    }

    if (l->tail == NULL)
    {
        printf("internal error remove_tail: tail = null\n");
        exit(1);
    }

    node *tmp = l->tail;
    l->tail = l->tail->left;

    if (l->size == 1)
    {
        l->head = NULL;
    }

    free_node(tmp);
    l->size--;

    return true;
}

bool remove_index(list *l, int index)
{
    if (l == NULL)
    {
        printf("error remove_index: pointer null\n");
        return false;
    }
    if (l->size <= index)
    {
        printf("error remove_index: index %d out of bounds, size = %d\n", index, l->size);
        return false;
    }

    if (index == 0)
    {
        return remove_head(l);
    }

    if (index == l->size)
    {
        return remove_tail(l);
    }

    int head_iteration = index;
    int tail_iteration = l->size - index - 1;
    node *tmp1;
    node *tmp2;
    node *node_to_delete;

    if (head_iteration <= tail_iteration)
    {
        node_to_delete = l->head;
        for (int i = 1; i <= head_iteration; i++)
        {
            node_to_delete = node_to_delete->right;
        }
        tmp1 = node_to_delete->left;
        tmp2 = node_to_delete->right;

        free_node(node_to_delete);

        tmp1->right = tmp2;
        tmp2->left = tmp1;
    }
    else
    {
        node_to_delete = l->tail;
        for (int i = 1; i <= tail_iteration; i++)
        {
            node_to_delete = node_to_delete->left;
        }
        tmp1 = node_to_delete->left;
        tmp2 = node_to_delete->right;

        free_node(node_to_delete);

        tmp1->right = tmp2;
        tmp2->left = tmp1;
    }

    if (l->size == 1)
    {
        l->head = NULL;
        l->tail = NULL;
    }

    l->size--;

    return true;
}

bool add_head(list *l, node *n)
{
    if (l == NULL)
    {
        printf("error: list null, can't add_head\n");
        return false;
    }

    node *previous_head = l->head;

    n->left = NULL;
    n->right = previous_head;

    if (l->size == 0)
    {
        l->tail = n;
    }

    if (previous_head != NULL)
    {
        previous_head->left = n;
    }

    l->head = n;
    l->size++;
    return true;
}

bool add_tail(list *l, node *n)
{
    if (l == NULL)
    {
        printf("error: list null, can't add_tail\n");
        return false;
    }

    node *previous_tail = l->tail;

    n->right = NULL;
    n->left = previous_tail;

    if (l->size == 0)
    {
        l->head = n;
    }
    if (previous_tail != NULL)
    {
        previous_tail->right = n;
    }

    l->tail = n;
    l->size++;
    return true;
}

bool add_index(list *l, node *n, int index)
{

    if (l == NULL)
    {
        printf("error remove_index: pointer null\n");
        return false;
    }
    if (l->size <= index)
    {
        printf("error insert: index %d out of bounds, size = %d\n", index, l->size);
        return false;
    }

    if (index == 0)
    {
        return add_head(l, n);
    }

    if (index == l->size)
    {
        return add_tail(l, n);
    }

    int head_iteration = index;
    int tail_iteration = l->size - index - 1;
    node *node_to_add;

    if (head_iteration <= tail_iteration)
    {
        node_to_add = l->head;
        for (int i = 1; i <= head_iteration; i++)
        {
            node_to_add = node_to_add->right;
        }

        n->left = node_to_add->left;

        if (n->left != NULL)
        {
            n->left->right = n;
        }

        n->right = node_to_add;
        node_to_add->left = n;
    }
    else
    {
        node_to_add = l->tail;
        for (int i = 1; i <= tail_iteration; i++)
        {
            node_to_add = node_to_add->left;
        }

        n->left = node_to_add->left;

        if (n->left != NULL)
        {
            n->left->right = n;
        }

        n->right = node_to_add;
        node_to_add->left = n;
    }

    l->size++;

    return true;
}

node *get_node(list *l, int index)
{
    if (l == NULL)
    {
        printf("error: list null, can't get_index\n");
        return NULL;
    }

    if (l->size <= index)
    {
        printf("error get_index: index %d out of bounds, size = %d\n", index, l->size);
        return NULL;
    }

    int head_iteration = index;
    int tail_iteration = l->size - index - 1;
    node *n;

    if (head_iteration <= tail_iteration)
    {
        n = l->head;
        for (int i = 1; i <= head_iteration; i++)
        {
            n = n->right;
        }
    }
    else
    {
        n = l->tail;
        for (int i = 1; i <= tail_iteration; i++)
        {
            n = n->left;
        }
    }

    if (n == NULL)
    {
        printf("internal error get_node: node found = null\n");
        exit(1);
    }

    return n;
}

void print_list(list *l)
{
    if (l == NULL)
    {
        printf("error: list null, can't print\n");
        return;
    }

    if (l->size == 0) {
        printf("list empty\n");

        if (l->head != NULL || l->tail != NULL) {
            printf("error: print_list, empty list must have tail/head = null\n");
            exit(1);
        }
        return;
    }

    node *n = l->head;

    int i = 0;

    while (n != NULL)
    {
        printf("%d[%s], ", i, node_type_to_text(n->type));
        n = n->right;
        i++;
    }

    printf("\n");
}
