#include <string.h>
#include <stdlib.h>

#include "evaluation.h"
#include "stack.h"
#include <stdio.h>

#include "ast_construction.h"



/* *********************
    private
*/

void evaluate(node *a);
int evaluate_int(node *a);
char *evaluate_char(node *a);

void exit_evaluation(char *msg);
/* ******************** */


/* *********************
    interface impl
*/

void start_evaluation()
{
    start_stack();
    evaluate(*get_ast());
}


void stop_evaluation() {
    free_ast();
    free_stack();
}


/* ******************** */




void evaluate(node *a)
{
    switch (a->type)
    {
    case N_INSTRUCTION:
        evaluate(a->left);
        if (a->right) {
            evaluate(a->right);
        }
        break;
    case N_INITIALISATION:
        switch (a->left->data_type)
        {
        case D_INT:
            int x1 = evaluate_int(a->right);
            node *n1 = creer_variable(a->left->name, a->left->data_type);
            n1->number = x1;
            printf("%s = %d\n", n1->name, n1->number);
            add_global(n1);
            break;
        case D_CHAR:
            char *x2 = evaluate_char(a->right);
            node *n2 = creer_variable(a->left->name, a->left->data_type);
            strcpy(n2->string, x2);
            printf("%s = %s\n", a->left->name, x2);
            add_global(n2);
            break;

        default:
            printf("internal error: evaluate\n");
            exit(1);
            break;
        }
        break;
    case N_ASSIGNATION:
        switch (a->left->data_type)
        {
        case D_INT:
            set_int(a->left->name, evaluate_int(a->right));
            printf("%s = %d\n", a->left->name, a->left->number);
            break;
        case D_CHAR:
            set_char(a->left->name, evaluate_char(a->right));
            printf("%s = %s\n", a->left->name, get_char(a->left->name));
            break;

        default:
            printf("internal error: evaluate\n");
            exit(1);
            break;
        }
        break;
    case N_VARIABLE:
        break;

    case N_VALUE:
        break;

    default:
        printf("internal error: evaluate\n");
        exit(1);
        break;
    }
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
            return evaluate_int(a->left);
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









void exit_evaluation(char *msg)
{

    stop_evaluation();
    
}

