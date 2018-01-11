all: flat-tree

clean:
	rm -f test flat-tree.o

flat-tree.o:
	clang -c -g flat-tree.c

flat-tree: flat-tree.o test.o
	clang flat-tree.o deps/*/*.c test.c -o test -I deps