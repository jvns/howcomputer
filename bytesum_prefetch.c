#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Too few arguments!");
        return 0;
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
        return 0;
    }
    uint64_t i;
    uint64_t j;
    uint8_t result;
    for (i = 0; i < filesize; i += 8 * 16) {
        __builtin_prefetch(&memblock[i + 512]);
        for (j = 0; j < 8 * 16; j++) {
            result += memblock[i + j];
        }
    }
    printf("The answer is: %d\n", result);
    return 0;
}

