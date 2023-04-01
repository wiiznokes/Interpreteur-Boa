#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_analyse.h"

#include "lexical_analyse.h"
#include "variable.h"
#include "node.h"

/* *********************
    private

*/

tree ast;


void instructions (node *a);
void instruction (node *a);
void initialisation(node *a, DataType type);
void assignation(node *a);
void function(node *a);
void if_statement(node *a);
void while_loop(node *a);
void operations(node *a, DataType type);
void operations_rec(node *a, DataType type);
void operation(node *a, DataType type);
void args(node *a);

void if_block(node *a);
void else_block(node *a);
void args(node *a);


void exit_analyse(char *msg);



/* *************** */


/**
    interface impl
*/

void fill_ast(char *fileName) {

    init_lexical_analyse(fileName);

    instructions(ast);
}



tree get_ast() {

    return ast;

}


/* *************** */


void instructions (node *a) {

    next_lexeme();

    switch (get_lexeme().nature)
    {
    case END_FILE:
        break;
    
    case INT:
    case CHAR:
    case NAME:
        instruction(a);
        instructions(a);
        break;

    default:
        exit_analyse("");
    }

}

void instruction (node *a) {

    switch (get_lexeme().nature)
    {
    
    case INT:
        initialisation(a, D_INT);
        break;
    case CHAR:
        initialisation(a, D_CHAR);
        break;
    case NAME:
        assignation(a);
        break;

    default:
        exit_analyse("");
    }

}

void initialisation(node *a, DataType type) {

    a = new_node(N_INITIALISATION);
    
    next_lexeme();

    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }

    type = check_variable(N_VARIABLE, get_lexeme().char_tab, type);

    if (type != D_UNDEFINED) {
        exit_analyse("variable déjà initialisée");
    }

    node *n = new_node(N_VARIABLE);
    strcpy(n->name, get_lexeme().char_tab);
    n->type = type;

    if (!add_global(n)) {
        exit_analyse("internal error: can't add global");
    }


    n = new_node(N_VARIABLE);
    strcpy(n->name, get_lexeme().char_tab);
    n->type = type;
    a->left = n;
   
    next_lexeme();

    if (get_lexeme().nature != INIT) {
        exit_analyse("");
    }
    
    next_lexeme();

    operations(a->right, type);

}


void assignation(node *a) {

    a = new_node(N_ASSIGNATION);

    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }

    DataType type = check_variable(N_VARIABLE, get_lexeme().char_tab, D_UNDEFINED);

    if (type == D_UNDEFINED) {
        exit_analyse("variable non définie");
    }


    node *n = new_node(N_VARIABLE);
    strcpy(n->name, get_lexeme().char_tab);
    n->type = type;
    a->left = n;
    

    next_lexeme();

    if (get_lexeme().nature != ASSIGN) {
        exit_analyse("");
    }
    
    next_lexeme();

    operations(a->right, type);
}





void operation(node *a, DataType type) {

    switch (get_lexeme().nature)
    {
    case NAME:

        type = check_variable(N_VARIABLE, a->name, type);

        if (type == D_UNDEFINED) {
            exit_analyse("variable non définie ou du mauvais type");
        }

        node *n = new_node(N_VARIABLE);
        strcpy(n->name, get_lexeme().char_tab);
        n->type = type;
        a->right = n;
        break;

    case STRING:
        if (type != D_CHAR) {
            exit_analyse("besoin du type char");
        }
        a->right = new_node(N_STRING);
        a->right->string = get_lexeme().char_tab;
        break;

    case NUMBER:
        if (type != D_INT) {
            exit_analyse("besoin du type int");
        }
        a->right = new_node(N_NUMBER);
        a->right->integer = atoi(get_lexeme().char_tab);
        break;

    default:
        exit_analyse("besoin d'une operande");
        break;
    }

}




void operations(node *a, DataType type) {

    operation(a, type);

    next_lexeme();

    operations_rec(a, type);
}



void operations_rec(node *a, DataType type) {

    switch (get_lexeme().nature)
    {
    case NAME:
    case STRING:
    case NUMBER:
        operation(a, type);
        next_lexeme();
        operations_rec(a, type);
    default:
        break;
    }

}










void exit_analyse(char *msg) {

    if (get_lexeme().nature != ERROR) {
        printf("Erreur syntaxique %d:%d : lexeme %s non autorisé ici.\n%s\n",
           get_lexeme().line,
           get_lexeme().column, 
           nature_to_text(get_lexeme().nature),
           msg
        );
    }

    free_tree(ast);

    stop_lexical_analyse();

    exit(1);
}


void stop_analyse() {

    free_tree(ast);
    stop_lexical_analyse();
}
