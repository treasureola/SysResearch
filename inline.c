#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>

//How to compile:  gcc -O2 -mavx2 inline.c -o inline

//passing data using inline (memcpy using inline)
void memcpy_inline(__m256i * dst, __m256i * src, __m256i size)
{
        size_t stride = 2 * sizeof(__m256i); //why?
        asm(
                "vmovntdqa %ymm2, size;" // store size in ymm2
                "vmovntdqa %ymm3, stride;" //store stride in ymm3
                "while:" //start loop
                "vmovntdqa %%ymm0, %1;" // move src into ymm0
                "vmovntdqa %0, %%ymm0" // move ymm0 into the dst
                "vpsubq %ymm2, %ymm2, %ymm3 " //ymm2 = size - stride
                "JZ while;"
                :"=r" (dst) //output %0
                : "r" (src) //input %1
                : "%ymm0" //the register housing the return value cannot be modifed outside asm
                // Question: If if store the size and stride in the input section, does it affect it in any way
        );
        //TEST?
}

void * add_array(void) //adding an array using inline assembly (learnign inline)
{
        __m256 first[8] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
        __m256 second[8] = {7.0,5.0,6.0,4.0,1.0,2.0,3.0,9.0};
        __m256 third[8];

        asm(
                "vmovntdqa %%ymm0, %0;"
                "vpaddq %%ymm1, %1;"
                "vmovntdqa %%ymm0, %ymm1;"
                :"=r" (third)
                :"r" (first), "r" (second)
                :"%ymm0"
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

}

int main(void){
        __m256i * dst; 
        __m256i * src; 
        __m256i size; 
        memcpy_inline(dst,src,size); //use assembly to call the function
}
