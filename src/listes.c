#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
    L->tete = NULL;
}

void liberer_liste(liste_t* L) {
    while(L->tete != NULL){
        cellule_t *tmp = L->tete;
        L->tete = L->tete->suivant;
        free(tmp);
    }
}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
    cellule_t* node = malloc(sizeof(cellule_t));
    node->val = c;
    node->suivant = L->tete;
    L->tete = node;
    return 1;
}

