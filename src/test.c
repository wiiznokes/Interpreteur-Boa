#include <stdio.h>
#include <stdlib.h>


int s[100];

int count = 0;


int *get() {

    return &s[count - 1];
}

int main(int argc, char **argv)
{
    s[0] = 0;
    count = 1;

    printf("%d\n", s[0]);


    *get() = 2;

    printf("%d\n", s[0]);


    return 0;
}



