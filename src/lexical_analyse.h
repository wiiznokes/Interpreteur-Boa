#ifndef LEXICAL_ANALYSE_H
#define LEXICAL_ANALYSE_H

#include <stdbool.h>

typedef enum
{

    ERROR,
    END_FILE,

    // data type
    INT,
    CHAR,
    
    // symbol
    INIT,
    ASSIGN,
    END_INSTRUCTION,

    // variable
    NAME,
    STRING,
    NUMBER,
    
    // operation
    PARO,
    PARF,
    PLUS,
    MINUS,
    MUL,
    DIV,
    EQUAL,
    LESS,
    MORE,
    LESS_EQUAL,
    MORE_EQUAL,
    OR,
    AND,
    NOT_EQUAL,
    NOT,

    // condition
    IF,
    ELSE,
    BRACE_OPEN,     // {
    BRACE_CLOSE,    // }

    // function
    FUN,
    COLON, // :
    RETURN
    
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
