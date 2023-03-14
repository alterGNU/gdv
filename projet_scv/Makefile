all: make

tests: test.c utils.c
	gcc -Wall -o test test.c utils.c && valgrind --leak-check=yes ./test

make: main.c
	gcc -Wall -ggdb -o main main.c utils.c

clean:
	rm -f test main main256.txt file*
