CC = clang
FLAGS = -g -Wall
EXE = Boa



build:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(FLAGS) $^ -o $(EXE)


test: test.o list.o
	$(CC) $(FLAGS) $^


%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf *.o $(EXE)
