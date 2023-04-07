#include <string.h>
#include <stdlib.h>

#include "evaluation.h"
#include "stack.h"
#include <stdio.h>

#include "ast_construction.h"
#include "list.h"

bool DEBUG_EVAL = false;

/* *********************
    private
*/

bool evaluate(node *a, int *res1, char **res2);
void evaluate_eag(node *a, DataType data_type, int *res1, char **res2);
int evaluate_int(node *a);
char *evaluate_char(node *a);

void exit_evaluation(char *msg);

void show_debug_eval(char *txt, node *a)
{
    if (DEBUG_EVAL)
        printf("%s: %s\n", txt, node_type_to_text(a->type));
}

/* ******************** */

/* *********************
    interface impl
*/

void start_evaluation()
{
    start_stack();
    evaluate(*get_ast(), NULL, NULL);
}

void stop_evaluation()
{
    free_ast();
    free_stack();
}

/* ******************** */

bool evaluate(node *a, int *res1, char **res2)
{
    show_debug_eval("evaluate", a);
    int x1;
    char *x2;
    bool res = false;

    if (a == NULL)
        return false;
    switch (a->type)
    {
    case N_INSTRUCTION:
        res = evaluate(a->left, res1, res2);
        if (!res && a->right)
        {
            res = evaluate(a->right, res1, res2);
        }
        break;
    case N_INITIALISATION:
        evaluate_eag(a->right, a->left->data_type, &x1, &x2);
        node *n1 = creer_variable(a->left->name, a->left->data_type);
        switch (a->left->data_type)
        {
        case D_INT:
            n1->number = x1;
            break;
        case D_CHAR:
            strcpy(n1->string, x2);
            break;
        default:
            printf("internal error: evaluate. %s\n", node_type_to_text(a->type));
            exit(1);
            break;
        }
        add_stack(n1);
        break;

    case N_ASSIGNATION:
        evaluate_eag(a->right, a->left->data_type, &x1, &x2);
        switch (a->left->data_type)
        {
        case D_INT:
            set_int(a->left->name, x1);
            break;
        case D_CHAR:
            set_char(a->left->name, x2);
            break;
        default:
            printf("internal error: evaluate. %s\n", node_type_to_text(a->type));
            exit(1);
            break;
        }
        break;
    case N_CONDITION:
        evaluate_eag(a->left, D_INT, &x1, &x2);
        up_scope();
        if (x1)
        {
            res = evaluate(a->right->left, res1, res2);
        }
        else
        {
            if (a->right->right)
            {
                res = evaluate(a->right->right, res1, res2);
            }
        }
        down_scope();
        break;

    case N_VARIABLE:
    case N_VALUE:
    case N_OPERATION:
    case N_CALL:
        evaluate_eag(a, a->data_type, &x1, &x2);
        switch (a->data_type)
        {
        case D_INT:
            printf("%d\n", x1);
            break;
        case D_CHAR:
            printf("%s\n", x2);
            break;
        default:
            break;
        }
        break;
    case N_FUN:
        break;
    case N_RETURN:
        // check if there is something to return (Unit)
        if (a->left)
            evaluate_eag(a->left, a->data_type, res1, res2);
        res = true;
        break;
    default:
        printf("internal error: evaluate. %s\n", node_type_to_text(a->type));
        exit(1);
        break;
    }
    return res;
}

void evaluate_eag(node *a, DataType data_type, int *res1, char **res2)
{
    show_debug_eval("evaluate_eag", a);

    switch (data_type)
    {
    case D_INT:
        *res1 = evaluate_int(a);
        break;
    case D_CHAR:
        *res2 = evaluate_char(a);
        break;
    case D_UNIT:
        evaluate_int(a);
        break;
    default:
        printf("internal error: evaluate_eag. %s\n", node_type_to_text(a->type));
        exit(1);
        break;
    }
}

void evalutate_args(node *a, list *args)
{
    show_debug_eval("evalutate_args", a);

    int x1;
    char *x2;

    if (a == NULL)
        return;
    switch (a->type)
    {
    case N_INSTRUCTION:
        evalutate_args(a->left, args);
        if (a->right)
        {
            evalutate_args(a->right, args);
        }
        break;
    case N_INITIALISATION:
        evaluate_eag(a->right, a->left->data_type, &x1, &x2);
        node *n1 = creer_variable(a->left->name, a->left->data_type);
        switch (a->left->data_type)
        {
        case D_INT:
            n1->number = x1;
            break;
        case D_CHAR:
            strcpy(n1->string, x2);
            break;
        default:
            printf("internal error: evalutate_args. %s\n", node_type_to_text(a->type));
            exit(1);
            break;
        }
        add_head(args, n1);
        break;

    default:
        printf("internal error: evalutate_args. %s\n", node_type_to_text(a->type));
        exit(1);
    }
}

int evaluate_int(node *a)
{
    show_debug_eval("evaluate_int", a);
    switch (a->type)
    {
    case N_CALL:
        // args (can't up stack directly because we need the current stack
        // in order to calcul arguments)
        list *args = new_list();
        evalutate_args(a->left, args);
        up_stack();
        while (args->size > 0)
        {
            node *tmp = pop_head(args);
            add_stack(tmp);
        }
        
        free_list(args);

        int res1;
        node *n = get_fun(a->name, a->data_type);
        evaluate(n->right, &res1, NULL);
        down_stack();
        return res1;

    case N_VARIABLE:
        return get_int(a->name);
    case N_OPERATION:
        switch (a->op)
        {
        case O_PLUS:
            return evaluate_int(a->left) + evaluate_int(a->right);
        case O_MINUS:
            return evaluate_int(a->left) - evaluate_int(a->right);
        case O_MUL:
            return evaluate_int(a->left) * evaluate_int(a->right);
        case O_DIV:
            int x1 = evaluate_int(a->left);
            int x2 = evaluate_int(a->right);
            if (x2 == 0)
            {
                exit_evaluation("division par 0");
            }
            return x1 / x2;
        case O_EQUAL:
            return evaluate_int(a->left) == evaluate_int(a->right);
        case O_LESS:
            return evaluate_int(a->left) < evaluate_int(a->right);
        case O_MORE:
            return evaluate_int(a->left) > evaluate_int(a->right);
        case O_LESS_EQUAL:
            return evaluate_int(a->left) <= evaluate_int(a->right);
        case O_MORE_EQUAL:
            return evaluate_int(a->left) >= evaluate_int(a->right);
        case O_OR:
            return evaluate_int(a->left) || evaluate_int(a->right);
        case O_AND:
            return evaluate_int(a->left) && evaluate_int(a->right);
        case O_NOT_EQUAL:
            return evaluate_int(a->left) != evaluate_int(a->right);
        case O_NOT:
            return !evaluate_int(a->right);
        default:
            printf("internal error: evaluate_int. %s\n", node_type_to_text(a->type));
            exit(1);
        }
    case N_VALUE:
        return a->number;
    default:
        printf("internal error: evaluate_int. %s\n", node_type_to_text(a->type));
        exit(1);
        break;
    }
}

char *evaluate_char(node *a)
{
    show_debug_eval("evaluate_char", a);
    switch (a->type)
    {
    case N_CALL:
        up_stack();
        evaluate(a->left, NULL, NULL);
        char *res2;
        node *n = get_fun(a->name, a->data_type);
        evaluate(n->right, NULL, &res2);
        down_stack();
        return res2;

    case N_VARIABLE:
        return get_char(a->name);
    case N_VALUE:
        return a->string;

    default:
        printf("internal error: evaluate_char. %s\n", node_type_to_text(a->type));
        exit(1);
        break;
    }
}

void exit_evaluation(char *msg)
{

    stop_evaluation();
}
