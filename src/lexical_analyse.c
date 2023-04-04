#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexical_analyse.h"
#include "lecture_caracteres.h"

/*
    private
*/

#define MAX_LEXEME_SIZE 250

typedef enum
{
    S_START, // accepteur (compte comme fin de fichier)
    S_ERROR, // non accepteur

    // int
    S_I,
    S_IN,
    S_INT,

    // char
    S_C,
    S_CH,
    S_CHA,
    S_CHAR,

    // generic
    S_NAME,
    S_NUMBER,

    // string
    S_GUILL, // non accepteur
    S_STRING,

    // operation

    S_EGALE,
    S_EQUAL,

    S_LESS,
    S_LESS_EQUAL,

    S_MORE,
    S_MORE_EQUAL,

    S_BAR, // non accepteur
    S_OR,

    S_AMPERSAND, // (&) non accepteur
    S_AND,

    S_INIT,

    S_NOT,
    S_NOT_EQUAL,

    S_PARO,
    S_PARF,
    S_PLUS,
    S_MINUS,
    S_MUL,
    S_DIV,

    // condition
    S_IF,
    S_E,
    S_EL,
    S_ELS,
    S_ELSE,
    S_BRACE_OPEN,
    S_BRACE_CLOSE,

    // function
    S_F,
    S_FU,
    S_FUN,
    S_COLON, // :
    S_R,
    S_RE,
    S_RET,
    S_RETU,
    S_RETUR,
    S_RETURN,

    S_END_INSTRUCTION,

} State;

Lexeme current_lexeme;
State current_state;

void next_char();
// return true si on doit refaire une itération
bool transition(char c);
void proccess_end();
bool is_number(char c);
bool is_letter(char c);
bool set_name_if_needed(char c);
bool is_separator(char c);
void add_char(char *s, char c);
void handle_error(char *message);


bool debug_lexical = true;
/*
 ***************
 */



void init_lexical_analyse(char *fileName)
{
    demarrer_car(fileName);
    next_char();
}


/*
    tricks to know the next lexeme without
    changing the current_lexeme variable
*/

bool silent_was_called = false;
Lexeme prev_lexeme;
Lexeme next_lexeme_cached;

void copy_lexeme(Lexeme *dest, Lexeme *src) {
    strcpy(dest->char_tab, src->char_tab);
    dest->column = src->column;
    dest->line = src->line;
    dest->nature = src->nature;
}

Lexeme silent_get_next_lexeme() {
    silent_was_called = true;
    copy_lexeme(&prev_lexeme, &current_lexeme);
    next_lexeme();
    copy_lexeme(&next_lexeme_cached, &current_lexeme);
    copy_lexeme(&current_lexeme, &prev_lexeme);
    return next_lexeme_cached;
}

/* ********************** */


void next_lexeme()
{
    if(silent_was_called) {
        copy_lexeme(&current_lexeme, &next_lexeme_cached);
        silent_was_called = false;
        return;
    }
    

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

    if (!transition(caractere_courant()))
    {
        handle_error("");
        return;
    }

    add_char(current_lexeme.char_tab, caractere_courant());
    next_char();
    int counter = 1;

    while (transition(caractere_courant()))
    {
        if (counter >= MAX_LEXEME_SIZE)
        {
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

    if (debug_lexical) {
        printf("Lexeme de nature %s = \"%s\"\n",
           nature_to_text(current_lexeme.nature), current_lexeme.char_tab);
    }
}

Lexeme get_lexeme() { return current_lexeme; }

void stop_lexical_analyse() { arreter_car(); }

char *nature_to_text(NatureLexeme nature)
{
    switch (nature)
    {
    case ERROR:
        return "ERROR";
    case END_FILE:
        return "END_FILE";

    case INT:
        return "INT";
    case CHAR:
        return "CHAR";

    case INIT:
        return "INIT";
    case ASSIGN:
        return "ASSIGN";
    case END_INSTRUCTION:
        return "END_INSTRUCTION";

    case NAME:
        return "NAME";
    case STRING:
        return "STRING";
    case NUMBER:
        return "NUMBER";

    case PARO:
        return "PARO";
    case PARF:
        return "PARF";
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case EQUAL:
        return "EQUAL";
    case LESS:
        return "LESS";
    case LESS_EQUAL:
        return "LESS_EQUAL";
    case MORE_EQUAL:
        return "MORE_EQUAL";
    case OR:
        return "OR";
    case AND:
        return "AND";
    case NOT_EQUAL:
        return "NOT_EQUAL";
    case NOT:
        return "NOT";

    case IF:
        return "IF";
    case ELSE:
        return "ELSE";
    case BRACE_OPEN:
        return "BRACE_OPEN";
    case BRACE_CLOSE:
        return "BRACE_CLOSE";
    
    case FUN:
        return "FUN";
    case COLON:
        return "COLON";
    case RETURN:
        return "RETURN";

    default:
        printf("internal error: nature_to_text\n");
        exit(1);
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
        case '=':
            current_state = S_EGALE;
            return true;
        case '<':
            current_state = S_LESS;
            return true;
        case '>':
            current_state = S_MORE;
            return true;
        case '|':
            current_state = S_BAR;
            return true;
        case '&':
            current_state = S_AMPERSAND;
            return true;
        case '!':
            current_state = S_NOT;
            return true;
        case '(':
            current_state = S_PARO;
            return true;
        case ')':
            current_state = S_PARF;
            return true;
        case '+':
            current_state = S_PLUS;
            return true;
        case '-':
            current_state = S_MINUS;
            return true;
        case '*':
            current_state = S_MUL;
            return true;
        case '/':
            current_state = S_DIV;
            return true;
        case 'e':
            current_state = S_E;
            return true;
        case '{':
            current_state = S_BRACE_OPEN;
            return true;
        case '}':
            current_state = S_BRACE_CLOSE;
            return true;
        case 'f':
            current_state = S_F;
            return true;
        case ':':
            current_state = S_COLON;
            return true;
        case 'r':
            current_state = S_R;
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
        case 'f':
            current_state = S_IF;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_IN:
        switch (c)
        {
        case 't':
            current_state = S_INT;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_INT:
        return set_name_if_needed(c);

    case S_C:
        switch (c)
        {
        case 'h':
            current_state = S_CH;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_CH:
        switch (c)
        {
        case 'a':
            current_state = S_CHA;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_CHA:
        switch (c)
        {
        case 'r':
            current_state = S_CHAR;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_CHAR:
        return set_name_if_needed(c);

    case S_NAME:
        return is_letter(c) || is_number(c);

    case S_NUMBER:
        return is_number(caractere_courant());

    case S_GUILL:
        if (c == '"')
        {
            current_state = S_STRING;
        }
        return true;
    case S_STRING:
        return false;

    case S_EGALE:
        switch (c)
        {
        case '=':
            current_state = S_EQUAL;
            return true;
        default:
            return false;
        }
    case S_EQUAL:
        return false;

    case S_LESS:
        switch (c)
        {
        case '-':
            current_state = S_INIT;
            return true;
        case '=':
            current_state = S_LESS_EQUAL;
            return true;
        default:
            return false;
        }
    case S_LESS_EQUAL:
        return false;

    case S_MORE:
        switch (c)
        {
        case '=':
            current_state = S_MORE_EQUAL;
            return true;
        default:
            return false;
        }
    case S_MORE_EQUAL:
        return false;

    case S_BAR:
        switch (c)
        {
        case '|':
            current_state = S_OR;
            return true;
        default:
            return false;
        }
    case S_OR:
        return false;

    case S_AMPERSAND:
        switch (c)
        {
        case '&':
            current_state = S_AND;
            return true;
        default:
            return false;
        }
    case S_AND:
        return false;

    case S_INIT:
        return false;

    case S_NOT:
        switch (c)
        {
        case '=':
            current_state = S_NOT_EQUAL;
            return true;
        default:
            return false;
        }
    case S_NOT_EQUAL:
        return false;

    case S_PARO:
    case S_PARF:
    case S_PLUS:
    case S_MINUS:
    case S_MUL:
    case S_DIV:
        return false;

    case S_IF:
        return set_name_if_needed(c);

    case S_E:
        switch (c)
        {
        case 'l':
            current_state = S_EL;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_EL:
        switch (c)
        {
        case 's':
            current_state = S_ELS;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_ELS:
        switch (c)
        {
        case 'e':
            current_state = S_ELSE;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_ELSE:
        return set_name_if_needed(c);
    case S_BRACE_OPEN:
        return false;
    case S_BRACE_CLOSE:
        return false;
    case S_F:
        switch (c)
        {
        case 'u':
            current_state = S_FU;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_FU:
        switch (c)
        {
        case 'n':
            current_state = S_FUN;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_FUN:
        return set_name_if_needed(c);

    case S_COLON:
        return false;

    case S_R:
        switch (c)
        {
        case 'e':
            current_state = S_RE;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_RE:
        switch (c)
        {
        case 't':
            current_state = S_RET;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_RET:
        switch (c)
        {
        case 'u':
            current_state = S_RETU;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_RETU:
        switch (c)
        {
        case 'r':
            current_state = S_RETUR;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_RETUR:
        switch (c)
        {
        case 'n':
            current_state = S_RETURN;
            return true;
        default:
            return set_name_if_needed(c);
        }
    case S_RETURN:
        return set_name_if_needed(c);
    
    case S_END_INSTRUCTION:
        return false;

    default:
        printf("internal error: transition, you forgot a state %d\n", current_state);
        exit(1);
    }
}

void proccess_end()
{

    switch (current_state)
    {

    case S_START:
        current_lexeme.nature = END_FILE;
        break;
    case S_INT:
        current_lexeme.nature = INT;
        break;
    case S_CHAR:
        current_lexeme.nature = CHAR;
        break;
    case S_NUMBER:
        current_lexeme.nature = NUMBER;
        break;
    case S_STRING:
        current_lexeme.nature = STRING;
        break;
    case S_EGALE:
        current_lexeme.nature = ASSIGN;
        break;
    case S_EQUAL:
        current_lexeme.nature = EQUAL;
        break;
    case S_LESS:
        current_lexeme.nature = LESS;
        break;
    case S_LESS_EQUAL:
        current_lexeme.nature = LESS_EQUAL;
        break;
    case S_MORE:
        current_lexeme.nature = MORE;
        break;
    case S_MORE_EQUAL:
        current_lexeme.nature = MORE_EQUAL;
        break;
    case S_OR:
        current_lexeme.nature = OR;
        break;
    case S_AND:
        current_lexeme.nature = AND;
        break;
    case S_INIT:
        current_lexeme.nature = INIT;
        break;
    case S_NOT:
        current_lexeme.nature = NOT;
        break;
    case S_NOT_EQUAL:
        current_lexeme.nature = NOT_EQUAL;
        break;
    case S_PARO:
        current_lexeme.nature = PARO;
        break;
    case S_PARF:
        current_lexeme.nature = PARF;
        break;
    case S_PLUS:
        current_lexeme.nature = PLUS;
        break;
    case S_MINUS:
        current_lexeme.nature = MINUS;
        break;
    case S_MUL:
        current_lexeme.nature = MUL;
        break;
    case S_DIV:
        current_lexeme.nature = DIV;
        break;
    case S_IF:
        current_lexeme.nature = IF;
        break;
    case S_ELSE:
        current_lexeme.nature = ELSE;
        break;
    case S_BRACE_OPEN:
        current_lexeme.nature = BRACE_OPEN;
        break;
    case S_BRACE_CLOSE:
        current_lexeme.nature = BRACE_CLOSE;
        break;
    case S_FUN:
        current_lexeme.nature = FUN;
        break;
    case S_COLON:
        current_lexeme.nature = COLON;
        break;
    case S_RETURN:
        current_lexeme.nature = RETURN;
        break;
    case S_END_INSTRUCTION:
        current_lexeme.nature = END_INSTRUCTION;
        break;

    case S_I:
    case S_IN:
    case S_C:
    case S_CH:
    case S_CHA:
    case S_NAME:
    case S_E:
    case S_EL:
    case S_ELS:
    case S_F:
    case S_FU:
    case S_R:
    case S_RE:
    case S_RET:
    case S_RETU:
    case S_RETUR:
        current_lexeme.nature = NAME;
        break;

    default:
        handle_error("");
    }
}
bool is_number(char c) { return c >= '0' && c <= '9'; }
bool is_letter(char c) { return c >= 'A' && c <= 'z'; }

bool set_name_if_needed(char c) {
    if (is_letter(c) || is_number(c))
    {
        current_state = S_NAME;
        return true;
    }
    return false;
}

bool is_separator(char c)
{
    return c == '\n' || c == ' ' || c == EOF || c == '\t';
}

void handle_error(char *message)
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
