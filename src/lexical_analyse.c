#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lecture_caracteres.h"
#include "lexical_analyse.h"


/*
    private
*/

#define MAX_LEXEME_SIZE 250

typedef enum
{
    S_START, // accepteur (compte comme fin de fichier)
    S_ERROR,

    // int
    S_I,   // accepteur
    S_IN,  // accepteur
    S_INT, // accepteur

    // char
    S_C,    // accepteur
    S_CH,   // accepteur
    S_CHA,  // accepteur
    S_CHAR, // accepteur

    // name
    S_NAME, // accepteur

    // string
    S_GUILL,
    S_STRING, // accepteur

    // number
    S_NUMBER, // accepteur

    // symbole
    S_INFERIOR,
    S_INITIALISATION,  // accepteur
    S_EGALE,           // accpteur
    S_END_INSTRUCTION, // accepteur

} State;

Lexeme current_lexeme;
State current_state;


void next_char();
// return true si on doit refaire une itération
bool transition(char c);
void proccess_end();
bool is_number(char c);
bool is_letter(char c);
bool is_separator(char c);
void add_char(char *s, char c);
void handle_error(char* message);

/*
 ***************
 */

void init_lexical_analyse(char *fileName)
{
    demarrer_car(fileName);
    next_char();
}

void next_lexeme()
{
    current_state = S_START;
    current_lexeme.char_tab[0] = '\0';
   

    if (fin_de_sequence_car())
    {
        proccess_end();
        return;
    }

    while (is_separator(caractere_courant()))
    {
        next_char();
        if (fin_de_sequence_car())
        {
            proccess_end();
            return;
        }
    }


    if (!transition(caractere_courant())) {
        handle_error("");
        return;
    }

    add_char(current_lexeme.char_tab, caractere_courant());
    next_char();
    int counter = 1;

    while (transition(caractere_courant()))
    {
        if (counter >= MAX_LEXEME_SIZE) {
            char log_message[200];
            snprintf(log_message, 200, "Erreur lexical: un lexeme ne peut pas faire plus de %d caractère.\n",
                MAX_LEXEME_SIZE);
            handle_error(log_message);
            return;
        }
        add_char(current_lexeme.char_tab, caractere_courant());
        next_char();
        counter++;
    }

    proccess_end();

    printf("Lexeme de nature %s = \"%s\"\n",
			   nature_to_text(current_lexeme.nature), current_lexeme.char_tab);
}

Lexeme get_lexeme() { return current_lexeme; }


void stop_lexical_analyse() { arreter_car(); }

char *nature_to_text(NatureLexeme nature)
{
    switch (nature)
    {
    case ERROR:
        return "ERROR";
    case INT:
        return "INT";
    case CHAR:
        return "CHAR";
    case STRING:
        return "STRING";
    case NUMBER:
        return "NUMBER";
    case INIT:
        return "INIT";
    case ASSIGN:
        return "ASSIGN";
    case NAME:
        return "NAME";
    case END_INSTRUCTION:
        return "END_INSTRUCTION";
    case END_FILE:
        return "END_FILE";
    }
}

/*
    private impl
*/

void next_char()
{
    avancer_car();

    current_lexeme.line = numero_ligne();
    current_lexeme.column = numero_colonne();
}

bool transition(char c)
{

    switch (current_state)
    {
    case S_START:
        switch (c)
        {
        case 'i':
            current_state = S_I;
            return true;
        case 'c':
            current_state = S_C;
            return true;
        case '"':
            current_state = S_GUILL;
            return true;
        case '<':
            current_state = S_INFERIOR;
            return true;
        case '=':
            current_state = S_EGALE;
            return true;
        case ';':
            current_state = S_END_INSTRUCTION;
            return true;

        default:
            if (is_number(c))
            {
                current_state = S_NUMBER;
                return true;
            }
            if (is_letter(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }

    case S_ERROR:
        printf("error: case error dans transition");
        return false;

    case S_I:
        switch (c)
        {
        case 'n':
            current_state = S_IN;
            return true;
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }

    case S_IN:
        switch (c)
        {
        case 't':
            current_state = S_INT;
            return true;
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }
    case S_INT:
        switch (c)
        {
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }
    case S_C:
        switch (c)
        {
        case 'h':
            current_state = S_CH;
            return true;
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }
    case S_CH:
        switch (c)
        {
        case 'a':
            current_state = S_CHA;
            return true;
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }
    case S_CHA:
        switch (c)
        {
        case 'r':
            current_state = S_CHAR;
            return true;
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }
    case S_CHAR:
        switch (c)
        {
        default:
            if (is_letter(c) || is_number(c))
            {
                current_state = S_NAME;
                return true;
            }
            return false;
        }
    case S_NAME:
        if (is_letter(c) || is_number(c))
        {
            current_state = S_NAME;
            return true;
        }
        else
        {
            return false;
        }

    case S_GUILL:
        if (c == '"')
        {
            current_state = S_STRING;
        }
        return true;
    case S_STRING:
        return false;

    case S_NUMBER:
        if (is_number(caractere_courant()))
        {
            return true;
        }
        else
        {
            return false;
        }
    case S_INFERIOR:
        switch (c)
        {
        case '-':
            current_state = S_INITIALISATION;
            return true;
        default:
            return false;
        }

    case S_INITIALISATION:
        switch (c)
        {
        default:
            return false;
        }
    case S_EGALE:
        switch (c)
        {
        default:
            return false;
        }
    case S_END_INSTRUCTION:
        switch (c)
        {
        default:
            return false;
        }
    }
}

void proccess_end()
{
    
    switch (current_state)
    {
    case S_START:
        current_lexeme.nature = END_FILE;
        break;
    case S_I:
        current_lexeme.nature = NAME;
        break;
    case S_IN:
        current_lexeme.nature = NAME;
        break;
    case S_INT:
        current_lexeme.nature = INT;
        break;
    case S_C:
        current_lexeme.nature = NAME;
        break;
    case S_CH:
        current_lexeme.nature = NAME;
        break;
    case S_CHA:
        current_lexeme.nature = NAME;
        break;
    case S_CHAR:
        current_lexeme.nature = CHAR;
        break;
    case S_NAME:
        current_lexeme.nature = NAME;
        break;
    case S_STRING:
        current_lexeme.nature = STRING;
        break;
    case S_NUMBER:
        current_lexeme.nature = NUMBER;
        break;
    case S_INITIALISATION:
        current_lexeme.nature = INIT;
        break;
    case S_EGALE:
        current_lexeme.nature = ASSIGN;
        break;
    case S_END_INSTRUCTION:
        current_lexeme.nature = END_INSTRUCTION;
        break;

    default:
        handle_error("");
    }
}
bool is_number(char c) { return c >= '0' && c <= '9'; }
bool is_letter(char c) { return c >= 'A' && c <= 'z'; }

bool is_separator(char c)
{
    return c == '\n' || c == ' ' || c == EOF || c == '\t';
}

void handle_error(char* message)
{
    current_lexeme.nature = ERROR;

    printf("Erreur lexical %d:%d : caractère \'%c\' non autorisé ici.\n%s\n",
           current_lexeme.line, current_lexeme.column, caractere_courant(), message);
}

void add_char(char *s, char c)
{
    int l;

    l = strlen(s);
    s[l] = c;
    s[l + 1] = '\0';
};
