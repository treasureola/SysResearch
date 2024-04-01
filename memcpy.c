#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>


void 
memcp()
{
    uint8_t* dst;
    uint8_t* src;
    size_t size;
    size_t stride = 2 * sizeof(__m256i);
    while (size)
    {
        __m256i a = _mm256_load_si256((__m256i*)src + 0);
        __m256i b = _mm256_load_si256((__m256i*)src + 1);
        _mm256_stream_si256((__m256i*)dst + 0, a);
        _mm256_stream_si256((__m256i*)dst + 1, b);

        size -= stride;
        src += stride;
        dst += stride;
    }
}

//time taken for memcpy to execute
int
main(){
    __clock_t t;
    t = clock();
    memcp();
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("copy took %f seconds to execute \n", time_taken); //WHY ARE YOU NOT PRINTING ?????
}