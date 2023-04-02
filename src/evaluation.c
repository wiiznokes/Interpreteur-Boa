#include <string.h>

#include "evaluation.h"
#include "stack.h"
#include <stdio.h>

#include "ast_construction.h"

void start_evaluation()
{
    evaluate(*get_ast());
}



int evaluate_int(node *a)
{
    
    switch (a->type)
    {
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
            if (x2 == 0) {
                exit_evaluation("division par 0");
            }
            return x1 / x2;
        default:
            printf("internal error: evaluate_int\n");
            exit(1);
        }
        case N_VALUE:
            return a->number;
    default:
        printf("internal error: evaluate_int\n");
        exit(1);
        break;
    }
}


char *evaluate_char(node *a) {
 switch (a->type)
    {
    case N_VARIABLE:
        return get_char(a->name);
    case N_VALUE:
        return a->string;
    default:
        printf("internal error: evaluate_char\n");
        exit(1);
        break;
    }
}

void evaluate(node *a)
{

    switch (a->type)
    {
    case N_INSTRUCTION:
        evaluate(a->left);
        evaluate(a->right);
        break;
    case N_INITIALISATION:
        switch (a->left->data_type)
        {
        case D_INT:
            int x = evaluate_int(a->right);
            node *n = creer_variable(a->left->name, a->left->data_type);
            n->number = x;
            add_global(n);
            break;
        case D_CHAR:
            char *x = evaluate_char(a->right);
            node *n = creer_variable(a->left->name, a->left->data_type);
            strcpy(n->string, x);
            add_global(n);
            break;

        default:
            printf("internal error: evaluate\n");
            exit(1);
            break;
        }

    case N_ASSIGNATION:
        switch (a->left->data_type)
        {
        case D_INT:
            set_int(a->left->name, evaluate_int(a->right));
            break;
        case D_CHAR:
            set_char(a->left->name, evaluate_char(a->right));
            break;

        default:
            printf("internal error: evaluate\n");
            exit(1);
            break;
        }
    case N_VARIABLE:
        break;

    case N_VALUE:
        break;

    default:
        printf("internal error: evaluate\n");
        exit(1);
    }
}


void exit_evaluation(char *msg)
{


    
}


void stop_evaluation() {
    free_ast();
}