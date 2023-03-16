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


    while (!is_end())
    {
        next_lexeme();
    }

    stop_lexical_analyse();

    return 0;
}