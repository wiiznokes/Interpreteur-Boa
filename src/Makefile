CC = clang
FLAGS = -g -Wall
EXE = Boa



build:interprete.o syntax_analyse.o lexical_analyse.o lecture_caracteres.o
	$(CC) $(FLAGS) $^ -o $(EXE)

run: build
	clear
	./Boa ./../test/valid/simple.boa


test: test.o list.o node.o tree.o
	$(CC) $(FLAGS) $^ -o test.bin


%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf *.o $(EXE) test.bin
