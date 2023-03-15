#ifndef ANALYSE_LEXICAL_H
#define ANALYSE_LEXICAL_H
#include "stdbool.h"

typedef enum
{
    ERREUR_CAR,     // caractere incorrect
    CHIFFRE,        // chiffre
    SYMBOLE,        // symbole
    C_FIN_SEQUENCE, // caractere de fin de sequence
    LETTER
} Nature_carac;





typedef enum
{
    // sequence of number
    INT,
    // symbol
    INIT,
    AFFEC,
    SYM_,
    END_SEQ, // pseudo lexeme ajoute en fin de sequence
    VAR_NAME
} NatureLexeme;


typedef struct
{
    NatureLexeme nature; // nature du lexeme
    unsigned int line;   // numero de ligne
    unsigned int column; // numero de colonne
    char chain[256];     // chaine de caracteres
    int value;           // valeur d'un entier
} Lexeme;




void start(char *fileName);

void advance();


Lexeme getLexeme();

bool isEnd();

void stop();



#endif //ANALYSE_LEXICAL_H
