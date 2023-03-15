#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lecture_caracteres.h"
#include "analyse_lexical.h"


Lexeme currentLexeme;

void start(char *fileName) {
    demarrer_car(fileName);
    advance();
}

void advance() {
    analyse();
}


Lexeme getLexeme() {
    return currentLexeme;
}


bool isEnd() {
    return currentLexeme.nature ==
}