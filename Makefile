all: run.o
run.o: conway.c
	gcc conway.c -o run.o
