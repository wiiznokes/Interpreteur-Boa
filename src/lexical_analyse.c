#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lecture_caracteres.h"
#include "lexical_analyse.h"




// private

Lexeme current_lexeme;

void next_char();



void init_lexical_analyse(char *fileName) {
    demarrer_car(fileName);
    next_char();
}

void next_lexeme() {
    next_char();

    if (fin_de_sequence_car()) {
        current_lexeme.nature = END_FILE;
    }
}

Lexeme getLexeme() {
    return current_lexeme;
}

bool is_end() {
    return current_lexeme.nature == END_FILE;
}

void stop_lexical_analyse() {
    arreter_car();
}



void next_char() {
    avancer_car();

    current_lexeme.line = numero_ligne();
    current_lexeme.column = numero_colonne();
}