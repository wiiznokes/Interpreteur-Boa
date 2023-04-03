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


int x1;
char *x2;

void evaluate(node *a)
{
    if (a == NULL) return;
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
            x1 = evaluate_int(a->right);
            node *n1 = creer_variable(a->left->name, a->left->data_type);
            n1->number = x1;
            printf("%s = %d\n", n1->name, x1);
            add_stack(n1);
            break;
        case D_CHAR:
            x2 = evaluate_char(a->right);
            node *n2 = creer_variable(a->left->name, a->left->data_type);
            strcpy(n2->string, x2);
            printf("%s = %s\n", n2->name, x2);
            add_stack(n2);
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
            x1 = evaluate_int(a->right);
            set_int(a->left->name, x1);
            printf("%s = %d\n", a->left->name, x1);
            break;
        case D_CHAR:
            x2 = evaluate_char(a->right);
            set_char(a->left->name, x2);
            printf("%s = %s\n", a->left->name, x2);
            break;

        default:
            printf("internal error: evaluate\n");
            exit(1);
            break;
        }
        break;
    case N_CONDITION:
        int res = evaluate_int(a->left);
        up_scope();
        if (res)
            evaluate(a->right->left);
        else 
            evaluate(a->right->right);
        down_scope();
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
            return !evaluate_int(a->right);
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

