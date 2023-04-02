#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_analyse.h"

#include "lexical_analyse.h"
#include "variable.h"
#include "node.h"
#include "ast_construction.h"

/* *********************
    private

*/

tree ast;

void instructions(node **a);
void instruction(node **a);
void initialisation(node **a, DataType data_type);
void assignation(node **a);

void exit_analyse(char *msg);

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
void next_lexeme_or_quit();

/* *************** */

/**
    interface impl
*/

void fill_ast(char *fileName)
{

    init_lexical_analyse(fileName);

    instructions(&ast);

    print_tree(ast);
}

/* *************** */

void instructions(node **a)
{

    next_lexeme_or_quit();

    switch (get_lexeme().nature)
    {
    case END_FILE:
        break;

    case INT:
    case CHAR:
    case NAME:
        node *a1;
        instruction(&a1);
        *a = a1;
        instructions(&(a1->right));
        break;

    default:
        exit_analyse("");
    }
}

void instruction(node **a)
{

    *a = new_node(N_INSTRUCTION);

    node *a1;
    switch (get_lexeme().nature)
    {

    case INT:
        initialisation(&a1, D_INT);
        break;
    case CHAR:
        initialisation(&a1, D_CHAR);
        break;
    case NAME:
        assignation(&a1);
        break;

    default:
        exit_analyse("");
    }

    (*a)->left = a1;

    if (get_lexeme().nature != END_INSTRUCTION)
    {
        exit_analyse("une instruction doit finir par ';'");
    }
}

void initialisation(node **a, DataType data_type)
{

    *a = new_node(N_INITIALISATION);

    next_lexeme_or_quit();

    if (get_lexeme().nature != NAME)
    {
        exit_analyse("");
    }

    if (check_variable(get_lexeme().char_tab, data_type, false) != D_UNDEFINED)
    {
        exit_analyse("");
    }

    // ajout d'une node dans la liste de variables
    node *n = creer_variable(get_lexeme().char_tab, data_type);
    if (!add_global(n))
    {
        free(n);
        exit_analyse("internal error: can't add global");
    }

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

void assignation(node **a)
{

    *a = new_node(N_ASSIGNATION);

    if (get_lexeme().nature != NAME)
    {
        exit_analyse("");
    }

    DataType data_type = check_variable(get_lexeme().char_tab, D_UNDEFINED, true);

    if (data_type == D_UNDEFINED)
    {
        exit_analyse("");
    }

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

    free_tree(ast);

    stop_lexical_analyse();

    exit(1);
}

void stop_analyse()
{

    free_tree(ast);
    stop_lexical_analyse();
}

/* from calculette */

void eag(node **a1, DataType data_type)
{
    seq_terme(a1, data_type);
}

void seq_terme(node **a2, DataType data_type)
{
    node *a1;
    terme(&a1, data_type);
    suite_seq_terme(a1, a2, data_type);
}

void suite_seq_terme(node *a1, node **a2, DataType data_type)
{
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
    seq_facteur(a1, data_type);
}

void seq_facteur(node **a2, DataType data_type)
{
    node *a1;
    facteur(&a1, data_type);
    suite_seq_facteur(a1, a2, data_type);
}

void suite_seq_facteur(node *a1, node **a2, DataType data_type)
{
    node *a3, *a4;
    Operateur op;
    int r = op2(&op, data_type);
    if (r == 1)
    {
        facteur(&a3, data_type);
        a4 = creer_operation(op, a1, a3);
        suite_seq_facteur(a4, a2, data_type);
    }
    else if (r == 2)
    {
        if (atoi(get_lexeme().char_tab) == 0)
        {
            exit_analyse("division par 0 impossible");
        }
        facteur(&a3, data_type);
        a4 = creer_operation(op, a1, a3);
        suite_seq_facteur(a4, a2, data_type);
    }
    else
    {
        // case: plus d'operateur
        *a2 = a1;
    }
}

void facteur(node **a1, DataType data_type)
{
    switch (get_lexeme().nature)
    {
    case NAME:
        if (check_variable(get_lexeme().char_tab, data_type, true) == D_UNDEFINED)
        {
            exit_analyse("");
        }
        *a1 = creer_variable(get_lexeme().char_tab, data_type);
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
        if (get_lexeme().nature == PARF)
        {
            next_lexeme_or_quit();
        }
        else
        {
            exit_analyse("erreur: parenthese");
        }
        break;
    default:
        exit_analyse("erreur: facteur");
    }
}

int op1(Operateur *op, DataType data_type)
{
    switch (get_lexeme().nature)
    {
    case PLUS:
        break;
    case MINUS:
        if (data_type == D_CHAR)
        {
            exit_analyse("can't use '-' with a string\n");
        }
        break;

    default:
        return 0;
    }

    *op = nature_lex_to_op(get_lexeme().nature);
    next_lexeme_or_quit();
    return 1;
}

int op2(Operateur *op, DataType data_type)
{
    int return_value;
    switch (get_lexeme().nature)
    {
    case MUL:
        return_value = 1;
        break;
    case DIV:
        break;
        return_value = 2;
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

    default:
        printf("internal error: nature_lex_to_op\n");
        exit(1);
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