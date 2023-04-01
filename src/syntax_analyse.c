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
void initialisation(node *a, data_t type);
void assignation(node *a);
void function(node *a);
void if_statement(node *a);
void while_loop(node *a);
void operations(node *a, data_t type);
void operations_rec(node *a, data_t type);
void operation(node *a, data_t type);
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

void initialisation(node *a, data_t type) {

    a = new_node(N_INITIALISATION);
    
    next_lexeme();

    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }

    a->left = new_variable(get_lexeme().char_tab, type);
    


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

    data_t type = check_variable(get_lexeme().char_tab, D_UNDEFINED);

    if (type == D_UNDEFINED) {
        exit_analyse("");
    }

    a->left = new_variable(get_lexeme().char_tab, type);
    

    next_lexeme();

    if (get_lexeme().nature != ASSIGN) {
        exit_analyse("");
    }
    
    next_lexeme();

    operations(a->right, type);
}





void operation(node *a, data_t type) {

    switch (get_lexeme().nature)
    {
    case NAME:

        type = check_variable(a->var->name, type);

        if (type == D_UNDEFINED) {
            exit_analyse("");
        }
        a->right = new_variable(get_lexeme().char_tab, type);
        break;

    case STRING:
        if (type != D_CHAR) {
            exit_analyse("");
        }
        a->right = new_node(N_STRING);
        a->right->string = get_lexeme().char_tab;
        break;

    case NUMBER:
        if (type != D_INT) {
            exit_analyse("");
        }
        a->right = new_node(N_NUMBER);
        a->right->value = atoi(get_lexeme().char_tab);
        break;

    default:
        exit_analyse("");
        break;
    }

}




void operations(node *a, data_t type) {

    operation(a, type);

    next_lexeme();

    operations_rec(a, type);
}



void operations_rec(node *a, data_t type) {

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
