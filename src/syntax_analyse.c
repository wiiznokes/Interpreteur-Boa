#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexical_analyse.h"
#include "syntax_analyse.h"


/* *********************
    private

*/

void instructions (node *a);
void instruction (node *a);
void initialisation(node *a, Data_type type);
void assignation(node *a);
void function(node *a);
void if_statement(node *a);
void while_loop(node *a);
void for_loop(node *a);
void operations(node *a);
void operation(node *a);
void args(node *a);

void if_block(node *a);
void else_block(node *a);
void args(node *a);
void operations(node *a);
void operation(node *a);
void args(node *a);


void exit_analyse(char *msg);



/* *************** */

void fill_ast(char *fileName, tree *a) {

    init_lexical_analyse(fileName);

    instructions(a);
}



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

void initialisation(node *a, Data_type type) {

    node* n_init = new_node();
    init_t init_stuct;
    init_stuct.type = type;
    n_init->ptr = &init_stuct;

    n_init->type = INITIALISATION;

    next_lexeme();

    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }


    // add name to list of variable

    strcpy(n_init->key, get_lexeme().char_tab);


    




}


void assignation(node *a) {

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

    stop_lexical_analyse();

    exit(1);
}

