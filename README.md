	PROJECT NAME
PASSING ARGUMENTS USING VECTOR REGISTERS

	PROJECT OVERVIEW
This project focuses on passing large chunk of data as arguments using vector registers. There a different types of vector registers but in this project, i will be focusing on AVX2 vector register

	APPROACH TAKEN
Vector registers has different calling convention from general registers. This project involved manipulating the calling conventions of AVX2 regisers. These calling convention includes the different uses of the registers. To implement my code, i implemented memcpy using AVX2 intrisics and also wrtitng it in AVX2 assembly instruction. 
<br>
One register(YMM0) are used to store return values, Some are used to pass arguments(YMM0-YMM3). But if the number of arguments that need to be passed is more than 4, they are stored on the stack. Other registers are temporary registers
<br>
<br>
Here is a good source for the calling conventions: https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170 


	AVX2 Data Types
- __m128: 128-bit vector containing 4 floats (4 * 4 = 16 bytes = 128 bits)
- __m128d:	128-bit vector containing 2 doubles (2 * 8 = 16 bytes = 128 bits)
- __m128i:	128-bit vector containing integers (Can contain any type of integr from chars to shorts to diffrent length of ints)
- __m256:	256-bit vector containing 8 floats (8 * 4 = 32 bytes = 256 bits)
- __m256d:	256-bit vector containing 4 doubles​ (8 * 4 = 32 bytes = 256 bits)
- __m256i	256-bit vector containing integers (Can contain any type of integr from chars to shorts to diffrent length of ints)
