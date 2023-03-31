#include <stdio.h>
#include <stdlib.h>

#include "lexical_analyse.h"
#include "syntax_analyse.h"


/* *********************
    private

*/

void instructions (node *ast);
void instruction (node *ast);
void initialisation(node *ast, Data_type type);
void assignation(node *ast);
void function(node *ast);
void if_statement(node *ast);
void while_loop(node *ast);
void for_loop(node *ast);
void operations(node *ast);
void operation(node *ast);
void args(node *ast);

void if_block(node *ast);
void else_block(node *ast);
void args(node *ast);
void operations(node *ast);
void operation(node *ast);
void args(node *ast);


void exit_analyse(char *msg);



/* *************** */

void fill_ast(char *fileName, tree *ast) {

    init_lexical_analyse(fileName);

    instructions(ast);
}



void instructions (node *ast) {

    next_lexeme();

    switch (get_lexeme().nature)
    {
    case END_FILE:
        break;
    
    case INT:
    case CHAR:
    case NAME:
        instruction(ast);
        instructions(ast);
        break;

    default:
        exit_analyse("");
    }

}

void instruction (node *ast) {

    switch (get_lexeme().nature)
    {
    
    case INT:
        initialisation(ast, D_INT);
        break;
    case CHAR:
        initialisation(ast, D_CHAR);
        break;
    case NAME:
        assignation(ast);
        break;

    default:
        exit_analyse("");
    }

}

void initialisation(node *ast, Data_type type) {

}


void assignation(node *ast) {

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

