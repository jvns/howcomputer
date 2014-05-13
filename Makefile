CC=gcc -Ofast
#CC=clang -O3

fast: bytesum.c
	$(CC) -o bytesum_fast bytesum.c
	time ./bytesum_fast *.mp4

slow: bytesum.c
	gcc -o bytesum_slow bytesum.c
	time ./bytesum_slow *.mp4


mmap: bytesum_mmap.c
	$(CC) -o bytesum_mmap bytesum_mmap.c
	time ./bytesum_mmap *.mp4

stride: bytesum_stride.c
	$(CC) -o bytesum_stride bytesum_stride.c

intrinsics: bytesum_intrinsics.c
	$(CC) -o bytesum_intrinsics bytesum_intrinsics.c

in_cache: bytesum_in_cache.c
	$(CC) -o bytesum_in_cache bytesum_in_cache.c

prefetch: bytesum_prefetch.c
	$(CC) -o bytesum_prefetch bytesum_prefetch.c -lrt

run: all
	./bytesum bytesum

newsroom:
	./bytesum *.mp4
