#ifndef STACK_H
#define STACK_H



void up();

void down();


void add_global(node *n);

void add_local(node *n);

char *get_char(char *name);
int get_int(char *name);

void set_char(char *name, char *value);
void set_int(char *name, int value);



#endif
