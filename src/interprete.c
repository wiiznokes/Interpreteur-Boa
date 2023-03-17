#include <stdio.h>
#include <stdlib.h>

#include "lexical_analyse.h"

int main(int argc, char **argv)
{
	switch (argc)
	{
	case 2:
		init_lexical_analyse(argv[1]);
		break;
	default:
		printf("number of args incorrect\n");
		exit(1);
	}

	while (!check_end())
	{
		next_lexeme();

		printf("Lexeme de nature %s = \"%s\"\n",
			   nature_to_text(get_lexeme().nature), get_lexeme().char_tab);
		
		if (get_lexeme().nature == ERROR) {
			break;
		}
	}

	stop_lexical_analyse();

	return 0;
}