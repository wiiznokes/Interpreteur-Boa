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


void instructions (node **a);
void instruction (node **a);
void initialisation(node **a, DataType data_type);
void assignation(node **a);
void function(node **a);
void if_statement(node **a);
void while_loop(node **a);
void operations(node **a, DataType data_type);
void operations_rec(node **a, DataType data_type);
void operation(node **a, DataType data_type);
void args(node **a);

void if_block(node **a);
void else_block(node **a);

void exit_analyse(char *msg);



/* *************** */


/**
    interface impl
*/

void fill_ast(char *fileName) {

    init_lexical_analyse(fileName);

    instructions(&ast);


    print_tree(ast);
}




/* *************** */


void instructions (node **a) {

    next_lexeme();

    switch (get_lexeme().nature)
    {
    case END_FILE:
        break;
    
    case INT:
    case CHAR:
    case NAME:
        instruction(a);
        // inject a pointeur of pointer of a->right
        instructions(&(*a)->right);
        break;

    default:
        exit_analyse("");
    }
}

void instruction (node **a) {

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

    if (get_lexeme().nature != END_INSTRUCTION) {
        exit_analyse("une instruction doit finir par ';'");
    }
}

void initialisation(node **a, DataType data_type) {

    *a = new_node(N_INITIALISATION);
    
    next_lexeme();

    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }

    if(check_variable(N_VARIABLE, get_lexeme().char_tab, data_type) != D_UNDEFINED) {
        exit_analyse("variable déjà initialisée");
    }

   
    node *n = new_node(N_VARIABLE);
    strcpy(n->name, get_lexeme().char_tab);
    n->data_type = data_type;

    if (!add_global(n)) {
        exit_analyse("internal error: can't add global");
    }


    n = new_node(N_VARIABLE);
    strcpy(n->name, get_lexeme().char_tab);
    n->data_type = data_type;
    (*a)->left = n;
   
    next_lexeme();

    if (get_lexeme().nature != INIT) {
        exit_analyse("");
    }
    
    next_lexeme();

    operations(&(*a)->right, data_type);

}


void assignation(node **a) {

    *a = new_node(N_ASSIGNATION);

    if (get_lexeme().nature != NAME) {
        exit_analyse("");
    }

    DataType data_type = check_variable(N_VARIABLE, get_lexeme().char_tab, D_UNDEFINED);

    if (data_type == D_UNDEFINED) {
        exit_analyse("variable non définie");
    }


    node *n = new_node(N_VARIABLE);
    strcpy(n->name, get_lexeme().char_tab);
    n->data_type = data_type;
    (*a)->left = n;
    

    next_lexeme();

    if (get_lexeme().nature != ASSIGN) {
        exit_analyse("besoin du signe \"=\"");
    }
    
    next_lexeme();

    operations(&(*a)->left, data_type);
}





void operation(node **a, DataType data_type) {

    switch (get_lexeme().nature)
    {
    case NAME:

        data_type = check_variable(N_VARIABLE, get_lexeme().char_tab, data_type);

        if (data_type == D_UNDEFINED) {
            exit_analyse("variable non définie ou du mauvais type");
        }

        node *n = new_node(N_VARIABLE);
        strcpy(n->name, get_lexeme().char_tab);
        n->data_type = data_type;
        *a = n;
        break;

    case STRING:
        if (data_type != D_CHAR) {
            exit_analyse("besoin du type char");
        }
        n = new_node(N_STRING);
        strcpy(n->string, get_lexeme().char_tab);
        *a = n;
        break;

    case NUMBER:
        if (data_type != D_INT) {
            exit_analyse("besoin du type int");
        }
        n = new_node(N_NUMBER);
        n->integer = atoi(get_lexeme().char_tab);
        *a = n;
        break;

    default:
        exit_analyse("besoin d'une operande");
        break;
    }

}




void operations(node **a, DataType data_type) {

    operation(a, data_type);

    next_lexeme();

    operations_rec(a, data_type);
}



void operations_rec(node **a, DataType data_type) {

    switch (get_lexeme().nature)
    {
    case NAME:
    case STRING:
    case NUMBER:
        operation(a, data_type);
        next_lexeme();
        operations_rec(a, data_type);
    default:
        break;
    }

}






void exit_analyse(char *msg) {

    if (get_lexeme().nature != ERROR) {
        printf("Erreur syntaxique %d:%d : %s non autorisé ici. %s\n",
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
