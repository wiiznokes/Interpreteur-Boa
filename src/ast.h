
#ifndef AST_H
#define AST_H

typedef enum
{
	OPERATION,
	VALEUR
} TypeAst;


typedef enum
{
	N_PLUS,
	N_MUL,
	N_MOINS
} TypeOperateur;


typedef struct noeud
{
	TypeAst nature;
	TypeOperateur operateur;
	struct noeud *gauche, *droite;
	int valeur;
} NoeudAst;

typedef NoeudAst *Ast;

Ast creer_operation(TypeOperateur opr, Ast opde_gauche, Ast opde_droit);
// renvoie un arbre abstrait de nature OPERATEUR,  d'operateur opr
// et ayant opde_gauche et opde_droit pour fils gauche et droit

Ast creer_valeur(int val);
// renvoie un arbre abstrait "feuille", de nature OPERATION
// et de valeur val

#endif
