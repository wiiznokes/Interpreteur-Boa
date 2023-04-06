#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_analyse.h"

#include "lexical_analyse.h"
#include "stack.h"
#include "node.h"
#include "ast_construction.h"



bool DEBUG_SYNTAX = true;


/* *********************
    private

*/

void instructions(node **a, DataType return_type);
void instruction(node **a, DataType return_type);
void initialisation(node **a, DataType data_type);
void assignation(node **a, DataType data_type);
void condition(node **a);

// function
void function(node **a) ;
void args(node **a);
void arg(node **a);
void arg_suite(node **a);
bool call(node **a, DataType data_type);
void call_args(node **a, node *arg);


// from calculette

void eag(node **a1, DataType data_type);
void seq_terme(node **a2, DataType data_type);
void suite_seq_terme(node *a1, node **a2, DataType data_type);
void terme(node **a1, DataType data_type);
void seq_facteur(node **a2, DataType data_type);
void suite_seq_facteur(node *a1, node **a2, DataType data_type);
void facteur(node **a1, DataType data_type);
int op1(Operateur *op, DataType data_type);
int op2(Operateur *op, DataType data_type);

// helper functions

Operateur nature_lex_to_op(NatureLexeme nature);
DataType nature_to_data_type(NatureLexeme nature);
void next_lexeme_or_quit();
void exit_analyse(char *msg);



void show_debug_syntax(char *txt) { if (DEBUG_SYNTAX) printf("%s\n", txt); }

/* *************** */

/**
    interface impl
*/

void fill_ast(char *fileName, bool show_log)
{

    init_lexical_analyse(fileName);

    start_stack();

    next_lexeme_or_quit();

    instructions(get_ast(), D_UNDEFINED);

    if (get_lexeme().nature != END_FILE) {
        exit_analyse("");
    }

    if (show_log) {
        printf("\n\n");
        print_tree(*get_ast());
        printf("\n\n");
    }
}

void stop_analyse()
{
    free_stack();
    stop_lexical_analyse();
}

/* *************** */

void instructions(node **a, DataType return_type)
{
    show_debug_syntax("instructions");

    switch (get_lexeme().nature)
    {
    case END_FILE:
        break;

    case INT:
    case CHAR:
    case NAME:
    case IF:
    case FUN:
    case NOT:
    case PARO:
    case NUMBER:
    case MINUS:
    case STRING:
    case RETURN:
        node *a1;
        instruction(&a1, return_type);
        *a = a1;
        instructions(&(a1->right), return_type);
        break;
    default:
        *a = NULL;
        break;
    }
}


void instruction(node **a, DataType return_type)
{
    show_debug_syntax("instruction");
    *a = new_node(N_INSTRUCTION);
    node *a1;
    bool need_semi_colon = true;

    switch (get_lexeme().nature)
    {

    case INT:
        initialisation(&a1, D_INT);
        break;
    case CHAR:
        initialisation(&a1, D_CHAR);
        break;
    case NAME:
        Lexeme *next_lexeme = silent_get_next_lexeme();
        DataType data_type;
        switch (next_lexeme->nature)
        {
        case PARO:
            node *n = get_fun(get_lexeme().char_tab, D_UNDEFINED);
            if (n == NULL)
            {
                exit_analyse("");
            }
            eag(&a1, n->data_type);
            break;
        case ASSIGN:
            data_type = check_variable(get_lexeme().char_tab, D_UNDEFINED, true);
            assignation(&a1, data_type);
            break;
        
        default:
            data_type = check_variable(get_lexeme().char_tab, D_UNDEFINED, true);
            if (data_type == D_UNDEFINED)
            {
                exit_analyse("");
            }
            eag(&a1, data_type);
            break;
        }
        break;
    case NOT:
    case PARO:
    case NUMBER:
    case MINUS:
        eag(&a1, D_INT);
        break;
    case STRING:
        eag(&a1, D_CHAR);
        break;
    case IF:
        condition(&a1);
        need_semi_colon = false;
        break;
    case FUN:
        function(&a1);
        need_semi_colon = false;
        break;
    case RETURN:
        if (return_type == D_UNDEFINED) {
            exit_analyse("");
        }

        next_lexeme_or_quit();
        node *a2 = NULL;
        if (get_lexeme().nature == END_INSTRUCTION) {
            if (return_type != D_UNIT) {
                char log[300];
                sprintf(log, "need %s return type", data_type_to_text(return_type));
                exit_analyse(log);
            }
        }
        else 
            eag(&a2, return_type);

        a1 = new_node(N_RETURN);
        a1->left = a2;
        a1->data_type = return_type;
        break;

    default:
        exit_analyse("");
    }

    if (need_semi_colon) {
        if (get_lexeme().nature != END_INSTRUCTION) 
            exit_analyse("une instruction doit finir par ';'");
    }
    
    next_lexeme_or_quit();

    (*a)->left = a1;

}


/*
    return false if there is no fun with
    the current name
*/
bool call(node **a, DataType data_type) {
    show_debug_syntax("call");

    *a = new_node(N_CALL);

    if (get_lexeme().nature != NAME)
    {
        exit_analyse("");
    }

    node *fun = get_fun(get_lexeme().char_tab, data_type);

    if (!fun) {
        return false;
    }

    next_lexeme_or_quit();
    if (get_lexeme().nature != PARO)
    {
        exit_analyse("");
    }

    // verifier que fun.left est bien null (est bien le bon compte d'args)

    // args bloc
    node *a1 = NULL;
    up_scope();

    next_lexeme_or_quit();

    if (fun->left == NULL) {
        if (get_lexeme().nature != PARF) {
            exit_analyse("");
        }
    }
    else {
        call_args(&a1, fun->left);
    }

    (*a)->left = a1;
    
    return true;
}

/*
    condition: arg != NULL 
    (can't have more arg than the function definition)
*/
void call_args(node **a, node *arg) {
    show_debug_syntax("call_args");

    if (arg == NULL) {
        exit_analyse("");
    }

    *a = new_node(N_INSTRUCTION);



    node *a1 = new_node(N_INITIALISATION);

    a1->left = creer_variable(arg->name, arg->data_type);



    node *a2;
    eag(&a2, arg->data_type);

    a1->right = a2;

    (*a)->left = a1;

    node *suite_arg;
    if (arg->left == NULL) {
        if (get_lexeme().nature != PARF) {
            exit_analyse("");
        }
    }
    else {
        call_args(&suite_arg, arg->left);
    }

    (*a)->right = suite_arg;


}



void function(node **a) {

    show_debug_syntax("function");

    *a = new_node(N_FUN);

    next_lexeme_or_quit();
    if (get_lexeme().nature != NAME)
    {
        exit_analyse("");
    }

    if (check_variable(get_lexeme().char_tab, D_UNDEFINED, false) != D_UNDEFINED)
    {
        char log[300];
        sprintf(log, "'%s' déjà dénini.", get_lexeme().char_tab);
        exit_analyse(log);
    }

    next_lexeme_or_quit();
    if (get_lexeme().nature != PARO)
    {
        exit_analyse("");
    }

    // args bloc
    node *a1 = NULL;
    up_scope();

    next_lexeme_or_quit();
    if (get_lexeme().nature != PARF)
    {
        args(&a1);
    }

    (*a)->left = a1;
    
    next_lexeme_or_quit();

    if (get_lexeme().nature == COLON) {
        next_lexeme_or_quit();

        DataType data_type = nature_to_data_type(get_lexeme().nature);

        if (data_type == D_UNDEFINED) {
            exit_analyse("need a return type with a colon\n");
        }
        (*a)->data_type = data_type;

        next_lexeme_or_quit();
    }
    else {
        (*a)->data_type = D_UNIT;
    }

    if (get_lexeme().nature != BRACE_OPEN) {
        exit_analyse("symbole { attendu\n");
    }



    node *a2;
    next_lexeme_or_quit();
    instructions(&a2, (*a)->data_type);

    (*a)->right = a2;

    

    if (get_lexeme().nature != BRACE_CLOSE) {
        exit_analyse("symbole } attendu\n");
    }

    down_scope();
}

/*
    met chaque argument dans n->left sous
    forme de variable, et ajoute celle ci sur la
    stack
*/
void args(node **a) {

    node *a1;
    arg(&a1);

    *a = a1;
}

void arg(node **a) {

    DataType data_type = nature_to_data_type(get_lexeme().nature);

    if (data_type == D_UNDEFINED) {
        exit_analyse("");
    }



    next_lexeme_or_quit();


    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }




    if (check_variable(get_lexeme().char_tab, data_type, false) != D_UNDEFINED)
    {
        char log[300];
        sprintf(log, "variable '%s' déjà déninie.", get_lexeme().char_tab);
        exit_analyse(log);
    }
    node *n = creer_variable(get_lexeme().char_tab, data_type);
    add_stack(n);

    *a = creer_variable(get_lexeme().char_tab, data_type);

    arg_suite(&(*a)->left);
    
}

void arg_suite(node **a) {

    next_lexeme_or_quit();

    switch (get_lexeme().nature)
    {
    case COMMA:
        next_lexeme_or_quit();
        arg(a);
        break;
    case PARF:
        // no more args
        *a = NULL;
        break;

    default:
        exit_analyse("");
        break;
    }
}


void initialisation(node **a, DataType data_type)
{
    show_debug_syntax("initialisation");

    *a = new_node(N_INITIALISATION);

    next_lexeme_or_quit();

    if (get_lexeme().nature != NAME)
    {
        exit_analyse("");
    }

    if (check_variable(get_lexeme().char_tab, data_type, false) != D_UNDEFINED)
    {
        char log[300];
        sprintf(log, "variable '%s' déjà déninie.", get_lexeme().char_tab);
        exit_analyse(log);
    }


    node *n = creer_variable(get_lexeme().char_tab, data_type);
    add_stack(n);

    (*a)->left = creer_variable(get_lexeme().char_tab, data_type);

    next_lexeme_or_quit();

    if (get_lexeme().nature != INIT)
    {
        exit_analyse("");
    }

    next_lexeme_or_quit();

    node *a1;
    eag(&a1, data_type);

    (*a)->right = a1;

}

void assignation(node **a, DataType data_type)
{
    show_debug_syntax("assignation");

    *a = new_node(N_ASSIGNATION);

    (*a)->left = creer_variable(get_lexeme().char_tab, data_type);


    next_lexeme_or_quit();
    if (get_lexeme().nature != ASSIGN)
    {
        exit_analyse("besoin du signe \"=\"");
    }


    next_lexeme_or_quit();
    node *a1;
    eag(&a1, data_type);

    (*a)->right = a1;

}


void condition(node **a) {
    show_debug_syntax("condition");

    *a = new_node(N_CONDITION);

    next_lexeme_or_quit();
    if (get_lexeme().nature != PARO)
    {
        exit_analyse("besoin de '(' après if");
    }

    next_lexeme_or_quit();
    node *a1;
    eag(&a1, D_INT);
    (*a)->left = a1;

    if (get_lexeme().nature != PARF)
    {
        exit_analyse("besoin de ')' après if");
    }

    next_lexeme_or_quit();
    if (get_lexeme().nature != BRACE_OPEN)
    {
        exit_analyse("besoin de '{' après if");
    }

    next_lexeme_or_quit();
    node *a2 = new_node(N_CONDITION);
    node *a3;
    up_scope();
    instructions(&a3, D_UNDEFINED);
    down_scope();
    a2->left = a3;

    (*a)->right = a2;

    if (get_lexeme().nature != BRACE_CLOSE)
    {
        exit_analyse("besoin de '}' après if");
    }

    Lexeme *next_lexeme = silent_get_next_lexeme();

    
    if (next_lexeme->nature != ELSE)
    {
        return;
    }
    next_lexeme_or_quit();

    next_lexeme_or_quit();
    if (get_lexeme().nature != BRACE_OPEN)
    {
        exit_analyse("besoin de '{' après else");
    }


    next_lexeme_or_quit();
    node *a4;
    up_scope();
    instructions(&a4, D_UNDEFINED);
    down_scope();
    a2->right = a4;


    if (get_lexeme().nature != BRACE_CLOSE)
    {
        exit_analyse("besoin de '}' après else");
    }

}

/* from calculette */

void eag(node **a1, DataType data_type)
{
    show_debug_syntax("eag");
    seq_terme(a1, data_type);
}

void seq_terme(node **a2, DataType data_type)
{
    show_debug_syntax("seq_terme");
    node *a1;
    terme(&a1, data_type);
    suite_seq_terme(a1, a2, data_type);
}

void suite_seq_terme(node *a1, node **a2, DataType data_type)
{
    show_debug_syntax("suite_seq_terme");
    node *a3, *a4;
    Operateur op;

    if (op1(&op, data_type))
    {
        terme(&a3, data_type);
        a4 = creer_operation(op, a1, a3);
        suite_seq_terme(a4, a2, data_type);
    }
    else
    {
        *a2 = a1;
    }
}

void terme(node **a1, DataType data_type)
{
    show_debug_syntax("terme");
    seq_facteur(a1, data_type);
}

void seq_facteur(node **a2, DataType data_type)
{
    show_debug_syntax("seq_facteur");
    node *a1;
    facteur(&a1, data_type);
    suite_seq_facteur(a1, a2, data_type);
}

void suite_seq_facteur(node *a1, node **a2, DataType data_type)
{
    show_debug_syntax("suite_seq_facteur");
    node *a3, *a4;
    Operateur op;

    switch (op2(&op, data_type))
    {
    case 1:
        facteur(&a3, data_type);
        a4 = creer_operation(op, a1, a3);
        suite_seq_facteur(a4, a2, data_type);
        break;
    case 2:
        if (atoi(get_lexeme().char_tab) == 0)
        {
            exit_analyse("division par 0 impossible");
        }
        facteur(&a3, data_type);
        a4 = creer_operation(op, a1, a3);
        suite_seq_facteur(a4, a2, data_type);
        break;
    default:
        // case: plus d'operateur
        *a2 = a1;
    }
}

void facteur(node **a1, DataType data_type)
{
    show_debug_syntax("facteur");

    node *a2;

    switch (get_lexeme().nature)
    {
    case NAME:
        if (check_variable(get_lexeme().char_tab, data_type, true) != D_UNDEFINED)
        {
            *a1 = creer_variable(get_lexeme().char_tab, data_type);
        }
        else 
        {
            if(!call(a1, data_type))
            {
                printf("variable '%s' is not defined\n", get_lexeme().char_tab);
                exit_analyse("");
            }
        }

        next_lexeme_or_quit();
        break;

    case NUMBER:
        if (data_type != D_INT)
        {
            printf("besoin du type %s: %s\n",
                   data_type_to_text(data_type),
                   get_lexeme().char_tab);
            exit_analyse("");
        }
        *a1 = creer_number(atoi(get_lexeme().char_tab));
        next_lexeme_or_quit();
        break;

    case STRING:
        if (data_type != D_CHAR)
        {
            printf("besoin du type %s: %s\n",
                   data_type_to_text(data_type),
                   get_lexeme().char_tab);
            exit_analyse("");
        }
        *a1 = creer_string(get_lexeme().char_tab);
        next_lexeme_or_quit();
        break;

    case PARO:
        next_lexeme_or_quit();
        eag(a1, data_type);
        if (get_lexeme().nature != PARF)
        {
            exit_analyse("erreur: besoin parenthèse fermante");
        }
        next_lexeme_or_quit();
        break;

    case NOT:
        next_lexeme_or_quit();
        facteur(&a2, data_type);
        *a1 = creer_operation(O_NOT, NULL, a2);
        break;

    case MINUS:
        next_lexeme_or_quit();
        facteur(&a2, data_type);
        
        node *zero_factice = creer_number(0);
        *a1 = creer_operation(O_MINUS, zero_factice, a2);
        break;
    default:

        exit_analyse("");
    }

}


int op1(Operateur *op, DataType data_type)
{
    show_debug_syntax("op1");
    switch (get_lexeme().nature)
    {
    case PLUS:
    case MINUS:
    case OR:
    case AND:
    case EQUAL:
    case NOT_EQUAL:
    case LESS:
    case MORE:
    case LESS_EQUAL:
    case MORE_EQUAL:

        if (data_type == D_CHAR)
        {
            exit_analyse("Pas compatible avec char");
        }
        *op = nature_lex_to_op(get_lexeme().nature);
        next_lexeme_or_quit();
        
        return 1;
    default:
        return 0;
    }
}

int op2(Operateur *op, DataType data_type)
{
    show_debug_syntax("op2");
    int return_value;
    switch (get_lexeme().nature)
    {
    case MUL:
        return_value = 1;
        break;
    case DIV:
        return_value = 2;
        break;
    default:
        return 0;
    }

    if (data_type == D_CHAR)
    {
        exit_analyse("can't use '/' or '*' with a string\n");
    }
    *op = nature_lex_to_op(get_lexeme().nature);
    next_lexeme_or_quit();

    return return_value;
}

// helper functions

void exit_analyse(char *msg)
{

    if (get_lexeme().nature != ERROR)
    {
        printf("Erreur syntaxique %d:%d : %s non autorisé ici. %s\n",
               get_lexeme().line,
               get_lexeme().column,
               nature_to_text(get_lexeme().nature),
               msg);
    }

    stop_analyse();
    free_ast();

    exit(1);
}

Operateur nature_lex_to_op(NatureLexeme nature)
{
    switch (nature)
    {
    case PLUS:
        return O_PLUS;
    case MINUS:
        return O_MINUS;
    case MUL:
        return O_MUL;
    case DIV:
        return O_DIV;
    case EQUAL:
        return O_EQUAL;
    case LESS:
        return O_LESS;
    case MORE:
        return O_MORE;
    case LESS_EQUAL:
        return O_LESS_EQUAL;
    case MORE_EQUAL:
        return O_MORE_EQUAL;
    case OR:
        return O_OR;
    case AND:
        return O_AND;
    case NOT_EQUAL:
        return O_NOT_EQUAL;
    case NOT:
        return O_NOT;

    default:
        printf("internal error: nature_lex_to_op\n");
        exit(1);
    }
}

DataType nature_to_data_type(NatureLexeme nature) {

    switch (nature)
    {
    case INT:
        return D_INT;
    case CHAR:
        return D_CHAR;
    
    default:
        return D_UNDEFINED;
    }

}

void next_lexeme_or_quit()
{
    next_lexeme();

    if (get_lexeme().nature == ERROR)
    {
        exit_analyse("");
    }
}