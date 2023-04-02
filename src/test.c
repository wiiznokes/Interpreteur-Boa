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



void eval() {

    return "bonjour";
}


int main(int argc, char **argv)
{

   
    char *res = (char *)eval();

    printf("%s\n", res);


    return 0;
}



