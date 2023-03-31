#include <stdio.h>
#include <stdlib.h>

#include "lexical_analyse.h"
#include "syntax_analyse.h"

/*
    list de node qui representera soit des variables,
    soit des functions, puisque qu'on en aura besoin constament,
    pour la construction de l'arbre, ainsi que pour l'evaluation
*/
list variables;

tree ast;

int main(int argc, char **argv)
{	
	char *fileName;
	switch (argc)
	{
	case 1:
		fileName = "";
		break;
	case 2:
		fileName = argv[1];
		break;
	default:
		printf("number of args incorrect\n");
		exit(1);
	}



	fill_ast(fileName, &ast);


	stop_lexical_analyse();

	return 0;
}