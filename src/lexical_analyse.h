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

    END_INSTRUCTION,

    END_FILE
} NatureLexeme;





typedef struct
{
    NatureLexeme nature;

    // for log error
    unsigned int line;
    unsigned int column;


    char string[256];
    int integer;
} Lexeme;




void init_lexical_analyse(char *fileName);

void next_lexeme();
Lexeme get_lexeme();

bool is_end();

void stop_lexical_analyse();


#endif
