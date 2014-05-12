#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Too few arguments!");
    }
    FILE *f = fopen(argv[1], "r");
}

