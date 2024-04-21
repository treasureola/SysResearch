# compile file: gcc -c avx.S -o file.o
# compile: gcc -m32 -c pass_parameter.S


.section .data
    array1: .float 1.1,2.2,3.3,4.4,1.1,2.2,3.3,4.4
    array2: .float 5.5,6.6,7.7,8.8,5.5,6.6,7.7,8.8
    array3: .float 1.1,5.5,2.2,6.6,1.1,5.5,2.2,6.6
    array4: .float 3.3,7.7,4.4,8.8,3.3,7.7,4.4,8.8

.section .text
    .global main

# passing parameters - 4 paremeters
main:
    vmovdqa %ymm0, array1 # move first paremnter to YMMO
    vmovdqa %ymm1, array2 # move second poarmenter to YMM1
    vmovdqa %ymm2, array3 # move thrid parameter to YMM2
    vmovdqa %ymm3, array4  # move fourth parameter to YMM3
    call test    # call callee
    

test:
    vpaddq %ymm0, %ymm0, %ymm1
    vpaddq %ymm0, %ymm0, %ymm2
    vpaddq %ymm0, %ymm0, %ymm3
    ret 

# zero out the upper 128 bits of YMM registers
zeroOut:
    VZEROUPPER