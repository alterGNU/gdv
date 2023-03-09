all: make

test: test.c biblioLC.c entreeSortieLC.c
	gcc -Wall -o test test.c biblioLC.c entreeSortieLC.c && valgrind --leak-check=yes ./test GdeBiblio.txt 5000

make: main.c biblioLC.c entreeSortieLC.c
	gcc -Wall -o main main.c biblioLC.c entreeSortieLC.c

clean:
	rm -f main save.txt doublons.txt test
