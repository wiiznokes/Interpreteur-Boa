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
void evaluate_eag(node *a, DataType data_type, int *res1, char **res2);
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
            printf("internal error: evaluate\n");
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
            printf("internal error: evaluate\n");
            exit(1);
            break;
        }
        break;
    case N_CONDITION:
        evaluate_eag(a->left, D_INT, &x1, &x2);
        up_scope();
        if (x1)
            evaluate(a->right->left);
        else 
            evaluate(a->right->right);
        down_scope();
        break;

    case N_VARIABLE:
    case N_VALUE:
    case N_OPERATION:
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
    default:
        printf("internal error: evaluate\n");
        exit(1);
        break;
    }
}




void evaluate_eag(node *a, DataType data_type, int *res1, char **res2) {

    
    switch (data_type)
    {
    case D_INT:
        *res1 = evaluate_int(a);
        break;
    case D_CHAR:
        *res2 = evaluate_char(a);
    default:
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

