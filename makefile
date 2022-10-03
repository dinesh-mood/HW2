COMPILER = gcc
EXES = search

compile: dmood_hw2.c
	${COMPILER} -o dmood_hw2 dmood_hw2.c

%.o: %.c %.h  makefile
	${COMPILER} $< -c 

remove:
	rm -f *.o *~ ${EXES} ${CFILES}
