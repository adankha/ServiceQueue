all: sq_slow.o sq.o llist.o driver fdriver

llist.o:  list.h llist.c
	gcc -c llist.c

sq_slow.o: llist.o sq.h sq_slow.c
	gcc -c sq_slow.c

driver: driver.c sq_slow.o 
	gcc driver.c sq_slow.o llist.o -lc -o driver

fdriver: driver.c sq.o
	gcc driver.c sq.o -lc -o fdriver
