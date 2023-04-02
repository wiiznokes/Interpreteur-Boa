CC = gcc
FLAGS = -g -Wall
EXE = Boa



build: clean clear build_boa


build_boa: interprete.o syntax_analyse.o lexical_analyse.o \
	lecture_caracteres.o node.o tree.o variable.o list.o \
	ast_construction.o stack.o evaluation.o
	$(CC) $(FLAGS) $^ -o $(EXE)


run: build
	clear
	./Boa ./../test/valid/simple.boa


test: test.o list.o node.o tree.o
	$(CC) $(FLAGS) $^ -o test.bin


%.o:%.c
	$(CC) $(FLAGS) -c $<

clear:
	clear

clean:
	rm -rf *.o *.gch *.bin $(EXE) 