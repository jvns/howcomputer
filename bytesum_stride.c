#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few arguments!");
        return 0;
    }
    const char *memblock;
    int fd;
    int stride_size = atoi(argv[2]);
    struct stat sb;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    uint64_t filesize = sb.st_size;
    printf("Size: %lu\n", filesize);

    memblock = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (memblock == MAP_FAILED) {
        printf("oh no it failed\n");
        return 0;
    }
    uint64_t i;
    uint64_t j;
    char result;
    for (j = 0; j < stride_size; j++) {
        for (i = 0; i + j < filesize; i  = i + stride_size) {
            result += memblock[i+j];
        }
    }
    printf("The answer is: %d\n", result);
    return 0;
}

