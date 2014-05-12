#include <stdio.h>

#define NMEMBERS 256

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Too few arguments!");
    }

    FILE *f = fopen(argv[1], "r");
    char data[NMEMBERS];


    size_t amount_read;
    char result;
    int i;
    while (1) {
        amount_read = fread(data, 1, NMEMBERS, f);
        if (amount_read == 0) {
            break;
        }
        for (i = 0; i < amount_read; i++) {
            result += data[i];
        }
    }
    printf("The answer is: %d\n", result);
    return 0;
}

