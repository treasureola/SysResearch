#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

// // int
// // main(){
// void 
// copy()
// {
//     uint8_t* dst;
//     uint8_t* src;
//     size_t size;
//     size_t stride = 2 * sizeof(__m256i);
//     while (size)
//     {
//         __m256i a = _mm256_load_si256((__m256i*)src + 0);
//         __m256i b = _mm256_load_si256((__m256i*)src + 1);
//         _mm256_stream_si256((__m256i*)dst + 0, a);
//         _mm256_stream_si256((__m256i*)dst + 1, b);

//         size -= stride;
//         src += stride;
//         dst += stride;
//     }
// }

// //time taken for memcpy to execute
// int
// main(){
//     __clock_t t;
//     t = clock();
//     copy();
//     t = clock() - t;
//     double time_taken = ((double)t)/CLOCKS_PER_SEC;
//     printf("copy took %f seconds to execute \n", time_taken);
// }

#include <cstring>
#include <iostream>
#include <vector>

#include "decl.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////
// This is a small program that checks if some memcpy implementation is correct.
////////////////////////////////////////////////////////////////////////////////

#define MAGIC_VALUE0 '#'
#define MAGIC_VALUE1 '='

void print_buffer(const char *start, const char *end, char val,
                  const char *ptr) {
  const char *it = start;
  while (it != end) {
    std::cout << *it;
    it++;
  }
  std::cout << "\n";
  it = start;
  while (it != ptr) {
    std::cout << " ";
    it++;
  }
  std::cout << "^\n";
  std::cout << "Filling a buffer of length " << end - start << ".";
  std::cout << " Expected \"" << val << "\" at index " << ptr - start
            << std::endl;
}

void print_buffer_match(const char *start0, const char *start1, size_t len,
                        size_t error_at) {

  for (size_t i = 0; i < len; i++) {
    std::cout << start0[i];
  }
  std::cout << "\n";
  for (size_t i = 0; i < len; i++) {
    std::cout << start1[i];
  }
  std::cout << "\n";

  for (size_t i = 0; i < error_at; i++) {
    std::cout << " ";
  }
  std::cout << "^\n";
  std::cout << "Comparing buffers of length " << len << ".";
  std::cout << " Invalid value at index " << error_at << "." << std::endl;
}

// Make sure that the whole buffer, from \p start to \p end, is set to \p val.
void assert_uniform_value(const char *start, const char *end, char val) {
  const char *ptr = start;
  while (ptr != end) {
    if (val != *ptr) {
      print_buffer(start, end, val, ptr);
      abort();
    }
    ptr++;
  }
}

// Make sure that two buffers contain the same memory content.
void assert_buffers_match(const char *buff1, const char *buff2, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (buff1[i] != buff2[i]) {
      print_buffer_match(buff1, buff2, len, i);
      abort();
    }
  }
}

void test_impl(memcpy_ty handle, const std::string &name, unsigned chunk_size) {
  std::vector<char> src(chunk_size + 512);
  std::vector<char> dest(chunk_size + 512, MAGIC_VALUE0);

  // Fill the buffer with a running counter of printable chars.
  for (unsigned i = 0; i < src.size(); i++) {
    src[i] = 'A' + (i % 26);
  }

  // Start copying memory at different offsets.
  for (int src_offset = 0; src_offset < 32; src_offset++) {
    for (int dest_offset = 0; dest_offset < 32; dest_offset++) {
      const char *dest_start = &*dest.begin();
      const char *dest_end = &*dest.end();

      const char *src_region_start = &src[src_offset];
      char *dest_region_start = &dest[dest_offset];
      char *dest_region_end = &dest[dest_offset + chunk_size];

      void *res =
          (handle)((void *)dest_region_start, src_region_start, chunk_size);
      if (res != dest_region_start) {
        std::cout << "Invalid return value." << std::endl;
        abort();
      }

      // Check the chunk.
      assert_buffers_match(dest_region_start, src_region_start, chunk_size);
      // Check before chunk.
      assert_uniform_value(dest_start, dest_region_start, MAGIC_VALUE0);
      // Check after chunk.
      assert_uniform_value(dest_region_end, dest_end, MAGIC_VALUE0);

      // Reset the dest buffer:
      std::fill(dest.begin(), dest.end(), MAGIC_VALUE0);
    }
  }
}

int main(int argc, char **argv) {
  std::cout << "Testing memcpy... \n";

#define TEST(FUNC, SIZE) test_impl(FUNC, #FUNC, SIZE);

  for (int i = 0; i < 1024; i++) {
    TEST(&memcpy, i);
    TEST(&__folly_memcpy, i);
    TEST(&local_memcpy, i);
    TEST(&asm_memcpy, i);
  }

  std::cout << "Done.\n";

  return 0;
}