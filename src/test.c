#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int a;
} t;



void modif(t **var) {

    *var = malloc(sizeof(t));
    
    (*var)->a = 10;
}

int main(int argc, char **argv)
{

   
    t *var;

    modif(&var);


    printf("%d\n", var->a);


    return 0;
}



