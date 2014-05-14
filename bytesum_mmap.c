#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few arguments!");
        return 1;
    }
    const uint8_t *memblock;
    int fd;
    struct stat sb;

    fd = open(argv[1], O_RDONLY);
    fstat(fd, &sb);
    uint64_t filesize = sb.st_size;
    printf("Size: %lu\n", filesize);

    memblock = mmap(NULL, filesize, PROT_READ, MAP_SHARED | MAP_POPULATE, fd, 0);
    if (memblock == MAP_FAILED) {
        printf("oh no it failed\n");
        return 2;
    }
    uint64_t i;
    uint8_t result;
    for (i = 0; i < filesize; i++) {
        result += memblock[i];
    }
    printf("The answer is: %d\n", result);
    return 0;
}

