CC = clang
DEBUG_FLAGS = -g -Wall
RELEASE_FLAGS = -02
EXE = Boa




debug:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(DEBUG_FLAGS) $^ -o $(EXE)

release:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(RELEASE_FLAGS) $^ -o $(EXE)


clean:
	rm -rf *.o $(EXE)
