#ifndef LEXICAL_ANALYSE_H
#define LEXICAL_ANALYSE_H

#include "stdbool.h"

typedef enum
{
    // data type
    INT,
    CHAR,
    // symbol
    INIT,
    ASSIGN,

    NAME,
    STRING,
    NUMBER,
    END_INSTRUCTION,
    END_FILE,

    PLUS,
    MINUS,
    MUL,
    DIV,
    PARO,
    PARF,

    ERROR
} NatureLexeme;

typedef struct
{
    NatureLexeme nature;

    // for log error
    unsigned int line;
    unsigned int column;

    char char_tab[256];

} Lexeme;

void init_lexical_analyse(char *fileName);

void next_lexeme();
Lexeme get_lexeme();


void stop_lexical_analyse();

char* nature_to_text(NatureLexeme nature);



#endif
