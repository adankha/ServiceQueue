ll_tst: llist.o ll_tst.c
	gcc ll_tst.c llist.o -o ll_tst

rev_tst: llist.o rev_tst.c
	gcc rev_tst.c llist.o -o rev_tst

llist.o: list.h llist.c
	gcc -c llist.c

msort: msort.c llist.o
	gcc msort.c llist.o -lc -o msort

qsort: qsort.c llist.o
	gcc qsort.c llist.o -lc -o qsort
