all: bytesum.c
	gcc -o bytesum bytesum.c

run: all
	./bytesum bytesum

newsroom:
	./bytesum *.mp4
