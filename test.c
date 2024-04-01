#include <immintrin.h>
#include <stdio.h>


void
call_functions(){

    __m256i array_a[8] = {1,2,3,4,5,6,7,8};
    __m256i array_b[8] = {7,5,6,4,1,2,3,9};
    __m256i array_c[8];

    __m256i a,b,c;
    a = _mm256_load_si256((__m256i*) array_a);
    b = _mm256_load_si256((__m256i*) array_b);
    c = _mm256_add_epi32(a,b);
    _mm256_storeu_si256((__m256i*)array_c,c);
    int * result = (int *)array_c;
    for (int i=0; i<8; i++){
        printf("%d\n", result[i]);
    }
    return;
}

int
main()
{
    call_functions(); 
    return 0;
}


