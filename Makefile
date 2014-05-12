
all:
	gcc -o bytesum bytesum.c

run: all
	./bytesum bytesum
