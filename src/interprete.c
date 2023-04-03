#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "syntax_analyse.h"
#include "evaluation.h"


int main(int argc, char **argv)
{	
	char *fileName = "";

	if (argc > 3) {
		printf("number of args incorrect\n");
		exit(1);
	}

	
	bool log_active = false;

	for(int count = 1; count < argc; count++ ) {
		if(!strcmp("-log", argv[count])) {
			log_active = true;
		}
		else {
			fileName = argv[count];
		}
	}


	fill_ast(fileName, log_active);
	stop_analyse();
	//start_evaluation();
	stop_evaluation();

	return 0;
}