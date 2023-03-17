#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char **argv)
{
	list l;
    l.tete = NULL;

    add_tete(&l, "hello");
    add_tete(&l, "world");

    
    printf("%s\n", l.tete->val);
    printf("%s\n", l.tete->next->val);

	return 0;
}