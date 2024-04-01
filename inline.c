#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>

//passing data using inline (memcpy using inline)
void memcpy_inline(void)
{
        __m256i * dst; 
        __m256i * src; 
        __m256i size; 
        size_t stride = 2 * sizeof(__m256i); //why?
        asm volatile(
                "while:"
                "vmovntdqa %ymm0, dst;" //load destiantion
                "vmovntdqa %ymm1, src;" //load src
                "vmovntdqa %ymm2, size;" //
                "vmovntdqa %ymm3, stride;"
                "vpsubq %ymm2, %ymm2, %ymm3 "
                "JZ while;"
                ://output
                : //input
                ://clobber
        );
}

// vector operations that work for data and sizes that are general, and make assumptions about
// static sizes
void * add_array(void) //adding an array using inline assembly (learnign inline)
{
        __m256 first[8] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
        __m256 second[8] = {7.0,5.0,6.0,4.0,1.0,2.0,3.0,9.0};
        __m256 third[8];

        __asm__(
                "vmovntdqa %ymm0, first;"
                "vmovntdqa %ymm2, second;"
                "vpaddq %ymm4,%ymm0,%ymm2;"
                // :"=X" (third)
                // :"X" (first), "X" (second)
        );
        int *result = (int*)&third;
        for (int i=0; i<8; i++){
                printf("%d\n", result[i]);
        }
}

// Alignment of data to copy into (tests for overhead)
void * align(void){

} 

//Code to zero out vector registers
void zero(void){

}

// Similar to return values through vector instructions
void ret(void){
        //use ymm3
}

// Place memory into regsiters
void place_mem(void){

}

// Call another function and have the called function move data into memory
void call_and_move_data(){
        asm volatile(
                "jmp place_mem;"
        );
}
