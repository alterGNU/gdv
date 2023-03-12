testLC: testLC.c biblioLC.c entreeSortieLC.c utilalea.c
	gcc -Wall -o testLC testLC.c biblioLC.c entreeSortieLC.c utilalea.c && valgrind --leak-check=yes ./testLC GdeBiblio.txt 5000

testH: testH.c biblioH.c utilalea.c
	gcc -Wall -o testH testH.c biblioH.c entreeSortieH.c utilalea.c -lm && valgrind --leak-check=yes ./testH 10 10

LC: mainLC.c biblioLC.c entreeSortieLC.c utilalea.c
	gcc -Wall -o mainLC mainLC.c biblioLC.c entreeSortieLC.c utilalea.c

H: mainH.c biblioH.c entreeSortieH.c utilalea.c
	gcc -Wall -o mainH mainH.c biblioH.c entreeSortieH.c utilalea.c -lm

compTime: compareSearchTime.c entreeSortieLC.c utilalea.c biblioLC.c biblioH.c entreeSortieH.c
	gcc -Wall -o compTime compareSearchTime.c entreeSortieLC.c utilalea.c biblioLC.c biblioH.c entreeSortieH.c

clean:
	rm -f mainH mainLC testH testLC compTime

