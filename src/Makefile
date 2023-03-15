CC=gcc


all: essai_ast exec

exec:
	echo "Projet INF404"
	./essai_ast

essai_ast:essai_ast.o ast_construction.o ast_parcours.o analyse_lexical.o analyse_syntaxique.o lecture_caracteres.o
	gcc $^ -o $@

%.o:%.c
	$(CC) -c $<

analyse_lexical.o: analyse_lexical.c analyse_lexical.h

analyse_syntaxique.o: analyse_syntaxique.c analyse_syntaxique.h lecture_caracteres.h ast_construction.h  

ast_construction.o: ast_construction.c 

ast_parcours.o: ast_parcours.c

essai_ast.o: essai_ast.c ast_construction.h ast_parcours.h

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h
