CC = gcc
FLAGS = -g -Wall
EXE = Boa



build:interprete.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(FLAGS) $^ -o $(EXE)


%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf *.o $(EXE)
