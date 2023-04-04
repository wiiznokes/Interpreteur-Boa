#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "syntax_analyse.h"
#include "evaluation.h"


int main(int argc, char **argv)
{	
	char *fileName = "";
	
	bool log = false;

	for(int count = 1; count < argc; count++ ) {
		if(!strcmp("-log", argv[count])) {
			log = true;
		}
		else {
			fileName = argv[count];
		}
	}


	fill_ast(fileName, log);
	stop_analyse();
	start_evaluation();
	stop_evaluation();

	return 0;
}