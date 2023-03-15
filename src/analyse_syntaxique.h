#ifndef ANALYSE_SYNTAXIQUE_H
#define ANALYSE_SYNTAXIQUE_H

#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

#include "type_ast.h"


void demarrer_s(char *nom_fichier);


void analyser(Ast *a);

void arreter_s();


#endif
