testLC: testLC.c biblioLC.c entreeSortieLC.c
	gcc -Wall -o testLC testLC.c biblioLC.c entreeSortieLC.c && valgrind --leak-check=yes ./testLC GdeBiblio.txt 5000

testH: testH.c biblioH.c
	gcc -Wall -o testH testH.c biblioH.c -lm && valgrind --leak-check=yes ./testH 10 10

LC: mainLC.c biblioLC.c entreeSortieLC.c
	gcc -Wall -o mainLC mainLC.c biblioLC.c entreeSortieLC.c

H: mainH.c biblioH.c entreeSortieH.c
	gcc -Wall -o mainH mainH.c biblioH.c entreeSortieH.c -lm

clean:
	rm -f {main,test}{H,LC} save.txt doublons.txt
