_____________ NOTE _______________________

------- Compiling iwth AVX intrinsics --------
        gcc -mavx -o file file.c

------- SIZE --------
    Float = 4 bytes = 32 bits
    Double = 8 bytes = 64 bits
    Int = 4 bytes = 32 bits


------- DATA TYPES --------
     1. ms56 f == {float f0 - f7}
     2. m256d d == {double d0 - d4}
     3. m256i i == 32 8-bit, 16-bit, 8 32-bit, or 4 64-bit
     __m128	128-bit vector containing 4 floats (4 * 4 = 16 bytes = 128 bits)
     __m128d	128-bit vector containing 2 doubles (2 * 8 = 16 bytes = 128 bits)
     __m128i	128-bit vector containing integers (Can contain any type of integr from chars to shorts to diffrent length of ints)
     __m256	256-bit vector containing 8 floats (8 * 4 = 32 bytes = 256 bits)
     __m256d	256-bit vector containing 4 doubles​ (8 * 4 = 32 bytes = 256 bits)
     __m256i	256-bit vector containing integers (Can contain any type of integr from chars to shorts to diffrent length of ints)

------- Naming Convention --------
        Data types satrt with a 2 underscores and an m
        Function satrt with an underscore and 2 ms
       _mm<bit_width>_<name>_<data_type>
        bit_width = the size fo the vector returned by the function (For 128, it is left empty and for 256, it is set to 256)
        name: Operation performed by the intrinsic
        data_type: identifies the data types of the functions primary arguments
                ------- Data tyepd for naming convnention --------
                        ps (packed single-precision) - contains floats
                        pd (packed double-precison) - contains doubles
                        epi8/epi16/epi32/epi64 - contain 8-bit/16-bit/32-bit/64-bit signed integers
                        epu18/epi16/epu32/epu64 - same as epi but contains unsigned integers
                        si128/si256 - unspecified 128-bit vector or 256-bit vector
                        m128/m128i/m128d/m256/m256i/m256d - identifies input vector types when they are different than the type of the returned vector



------- INITIALIZATION INTIRNSICS --------
        ------- INITIALIZING WITH SCALAR VALUES --------