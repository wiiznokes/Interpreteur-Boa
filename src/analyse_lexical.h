#ifndef ANALYSE_LEXICAL_H
#define ANALYSE_LEXICAL_H


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
    INIT,
    AFFEC
} Symbole;


typedef enum
{
    INT,       // sequence de chiffres
    Symbole,
    SYM_
    END_SEQ, // pseudo lexeme ajoute en fin de sequence
    VAR_NAME
} Nature_Lexeme;


typedef struct
{
    Nature_Lexeme nature; // nature du lexeme
    unsigned int lign;   // numero de ligne
    unsigned int colonne; // numero de colonne
    char chaine[256];     // chaine de caracteres
    int valeur;           // valeur d'un entier
} Lexeme;




void start();

void advance();


Lexeme current_lexeme();

int seq_end();

void stop();



#endif //ANALYSE_LEXICAL_H
