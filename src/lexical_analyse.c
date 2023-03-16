#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lecture_caracteres.h"
#include "lexical_analyse.h"




// private

Lexeme currentLexeme;

void next_char();



void init_lexical_analyse(char *fileName) {
    demarrer_car(fileName);
    next_char();
}

void next_lexeme() {

}

Lexeme getLexeme() {
    return currentLexeme;
}

bool is_end() {
    return currentLexeme.nature == END_FILE;
}

void stop_lexical_analyse() {
    arreter_car();
}



void next_char() {

}