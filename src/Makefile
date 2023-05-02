CC = gcc
FLAGS = -g -Wall
EXE = Boa





build: interprete.o syntax_analyse.o lexical_analyse.o \
	lecture_caracteres.o node.o tree.o \
	ast_construction.o stack.o evaluation.o
	$(CC) $(FLAGS) $^ -o $(EXE)


run: build
	./Boa ./../algorithmes/simple.boa



%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf *.o *.gch *.bin $(EXE) 