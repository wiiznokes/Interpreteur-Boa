#include "analyse_syntaxique.h"
#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

#include "ast_construction.h"


/* interne au module: */
void rec_eaep();

void rec_eag(Ast *a);

void rec_seq_terme(Ast *a);
void rec_terme(Ast *a);
void rec_suite_seq_terme(Ast ag, Ast *a);

void rec_seq_facteur(Ast *a);
void rec_facteur(Ast *a);
void rec_suite_seq_facteur(Ast ag, Ast *a);

void rec_op1(TypeOperateur *op);
void rec_op2(TypeOperateur *op);

void rec_op();
void rec_eaep();

/* ************************* */

void demarrer_s(char *nom_fichier)
{
    demarrer(nom_fichier);
}

void analyser(Ast *a)
{
    rec_eag(a);
}

void arreter_s()
{
    arreter();
}


void rec_eag(Ast *a) {
    rec_seq_terme(a);
}

void rec_seq_terme(Ast *a) {
    Ast a1;
    rec_terme(&a1);
    rec_suite_seq_terme(a1, a);
}

void rec_suite_seq_terme(Ast ag, Ast *a) {
    Ast ad, a1;
    TypeOperateur op;
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            rec_op1(&op);
            rec_terme(&ad);
            a1 = creer_operation(op, ag, ad);
            rec_suite_seq_terme(a1, a);
        
        default:
            a = &ag;
            break;
    }
}

void rec_seq_facteur(Ast *a) {
    Ast ad, a1;
    TypeOperateur op;
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            rec_op2(&op);
            rec_terme(&ad);
            a1 = creer_operation(op, ag, ad);
            rec_suite_seq_terme(a1, a);
        
        default:
            a = &ag;
            break;
    }
}


void rec_suite_seq_facteur(Ast ag, Ast *a) {
    Ast ad, a1;
    TypeOperateur op;
    switch (lexeme_courant().nature) {
        case PLUS:
        case MOINS:
            rec_op2(&op);
            rec_terme(&ad);
            a1 = creer_operation(op, ag, ad);
            rec_suite_seq_terme(a1, a);
        
        default:
            a = &ag;
            break;
    }
}


void rec_op2(TypeOperateur *op) {
    switch (lexeme_courant().nature)
    {
    case MUL:
        *op = N_MUL;
        avancer();
        break;
    
    default:
        printf("rec_op2: opérande attendu\n");
        exit(1);
    }
}

void rec_op1(TypeOperateur *op) {
    switch (lexeme_courant().nature)
    {
    case PLUS:
        *op = N_PLUS;
        avancer();
        break;
    case MOINS:
        *op = N_MOINS;
        avancer();
        break;
    
    default:
        printf("rec_op1: opérande attendu\n");
        exit(1);
    }
}

void rec_terme(Ast *a) {
    rec_seq_facteur(a);
}

void rec_facteur(Ast *a)
{
    switch (lexeme_courant().nature)
    {
    case ENTIER:
        *a = creer_valeur(lexeme_courant().valeur);
        avancer();
        break;

    case PARO:
        avancer();
        rec_eag(a);
        switch (lexeme_courant().nature)
        {
        case PARF:
            avancer();
            break;
        default:
            printf("rec_facteur: PARF attendu\n");
            exit(1);
        }
        break;
    default:
        printf("rec_facteur: debut attendu\n");
        exit(1);
    }
}





void rec_op()
{
    switch (lexeme_courant().nature)
    {
    case PLUS:
    case MUL:
    case MOINS:
    case DIV:
        avancer();
        break;
    default:
        printf("Erreur syntaxique: operande attendu\n");
        exit(1);
    }
}

void rec_eaep()
{
    switch (lexeme_courant().nature)
    {
    case ENTIER:
        avancer();
        break;
    case PARO:
        avancer();
        rec_eaep();
        rec_op();
        rec_eaep();
        switch (lexeme_courant().nature)
        {
        case PARF:
            avancer();
            break;

        default:
            printf("Erreur syntaxique: PARF attendu\n");
            exit(1);
        }
        break;
    default:
        printf("Erreur syntaxique: ENTIER ou PARF attendu\n");
        exit(1);
    }
}