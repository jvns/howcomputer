#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <emmintrin.h>
char sum_array(const uint8_t a[], int n)
{
    const __m128i vk0 = _mm_set1_epi8(0);       // constant vector of all 0s for use with _mm_unpacklo_epi8/_mm_unpackhi_epi8
    const __m128i vk1 = _mm_set1_epi16(1);      // constant vector of all 1s for use with _mm_madd_epi16
    __m128i vsum = _mm_set1_epi32(0);           // initialise vector of four partial 32 bit sums
    uint32_t sum;
    int i;

    for (i = 0; i < n; i += 16)
    {
        __m128i v = _mm_load_si128((__m128i *)&a[i]);      // load vector of 8 bit values
        __m128i vl = _mm_unpacklo_epi8(v, vk0); // unpack to two vectors of 16 bit values
        __m128i vh = _mm_unpackhi_epi8(v, vk0);
        vsum = _mm_add_epi32(vsum, _mm_madd_epi16(vl, vk1));
        vsum = _mm_add_epi32(vsum, _mm_madd_epi16(vh, vk1));
        // unpack and accumulate 16 bit values to
        // 32 bit partial sum vector

    }
    // horizontal add of four 32 bit partial sums and return result
    vsum = _mm_add_epi32(vsum, _mm_srli_si128(vsum, 8));
    vsum = _mm_add_epi32(vsum, _mm_srli_si128(vsum, 4));
    sum = _mm_cvtsi128_si32(vsum);
    return (char)sum;
}

int main(int argc, char** argv) {
    if (argc < 1) {
        printf("Too few arguments!");
        return 0;
    }
    const char *memblock;
    int fd;
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

    char result;
    printf("The answer is: %d\n", sum_array(memblock, filesize));
    return 0;
}

