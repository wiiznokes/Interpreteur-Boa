#include <stdio.h>
#include <stdlib.h>


#include "syntax_analyse.h"



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



	fill_ast(fileName);

	stop_analyse();

	return 0;
}