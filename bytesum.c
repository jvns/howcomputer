#include <stdio.h>

#define NMEMBERS 128000000

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Too few arguments!");
    }

    FILE *f = fopen(argv[1], "r");
    char data[NMEMBERS];

    size_t amount_read = fread(data, 1, NMEMBERS, f);
    printf("Read this many bytes: %d\n", (int)amount_read);

    int i;
    char result;
    for (i = 0; i < amount_read; i++) {
        result += data[i];
    }
    printf("The answer is: %d\n", result);
    return 0;
}

