fast: bytesum.c
	gcc -o bytesum_fast bytesum.c -Ofast
	time ./bytesum_fast *.mp4

slow: bytesum.c
	gcc -o bytesum_slow bytesum.c
	time ./bytesum_slow *.mp4


mmap: bytesum_mmap.c
	gcc -Ofast -o bytesum_mmap bytesum_mmap.c
	time ./bytesum_mmap *.mp4

run: all
	./bytesum bytesum

newsroom:
	./bytesum *.mp4
