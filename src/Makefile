CC = clang
RELEASE_TAG = -02
DEBUG_FLAG = -g -Wall
EXE = Boa


all: boa_debug exec

exec:
	./Boa


# build exe

boa_release:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(RELEASE_TAG) $^ -o $(EXE)

boa_debug:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(DEBUG_FLAG) $^ -o $(EXE)

boa_debug_gdb:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(DEBUG_FLAG) $^ -o $(EXE)


# build modules

%.o:%.c
	$(CC) -c $<

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h

lexical_analyse.o: lexical_analyse.c lexical_analyse.h


ast_construction.o: ast_construction.c
ast_parcours.o: ast_parcours.c


clean:
	rm -rf *.o $(EXE)
