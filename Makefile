all: graphe

graphe: graphe.o
	gcc -o graphe graphe.o

graphe.o: graphe.c graphe.h
	gcc -c graphe.c

clean:
	rm -f graphe.o graphe *~
