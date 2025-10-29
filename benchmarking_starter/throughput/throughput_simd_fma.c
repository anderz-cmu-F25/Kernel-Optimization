#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

#define MAX_FREQ 3.2
#define BASE_FREQ 2.4
#define NUM_INST 625.0
#define NUM_CHAINS 1
static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

//TODO: Define your Macros here
#define FMA(dest, src1, src2) \
  __asm__ volatile ( \
    "vfmadd231pd %[d], %[s1], %[s2]\n\t" \
    : [d] "+x"(dest) \
    : [s1] "x"(src1), [s2] "x"(src2) \
  );

#define FMA10(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA(a, const_1, const_2) \
  // FMA(b, const_1, const_2) \
  // FMA(c, const_1, const_2) \
  // FMA(d, const_1, const_2) \
  // FMA(e, const_1, const_2) \
  // FMA(f, const_1, const_2) \
  // FMA(g, const_1, const_2) \
  // FMA(h, const_1, const_2) \
  // FMA(i, const_1, const_2) \
  // FMA(j, const_1, const_2)

#define FMA10_5(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10(a, b, c, d, e, f, g, h, i, j, const_1, const_2)

#define FMA10_25(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_5(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_5(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_5(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_5(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_5(a, b, c, d, e, f, g, h, i, j, const_1, const_2)

#define FMA10_125(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_25(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_25(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_25(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_25(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_25(a, b, c, d, e, f, g, h, i, j, const_1, const_2)

#define FMA10_625(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_125(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_125(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_125(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_125(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_125(a, b, c, d, e, f, g, h, i, j, const_1, const_2)

#define FMA10_3125(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_625(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_625(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_625(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_625(a, b, c, d, e, f, g, h, i, j, const_1, const_2) \
  FMA10_625(a, b, c, d, e, f, g, h, i, j, const_1, const_2)


int main(int argc, char **argv) {

  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 1000;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;

  for (int j = 0; j < runs; j++) {
    double arr[4] = {1.0, 0.0, 0.0, 0.0};
    double arr_const[4] = {1.0, 0.0, 0.0, 0.0};
    __m256d v1 = _mm256_loadu_pd(arr);
    __m256d v2 = _mm256_loadu_pd(arr);
    __m256d v3 = _mm256_loadu_pd(arr);
    __m256d v4 = _mm256_loadu_pd(arr);
    __m256d v5 = _mm256_loadu_pd(arr);
    __m256d v6 = _mm256_loadu_pd(arr);
    __m256d v7 = _mm256_loadu_pd(arr);
    __m256d v8 = _mm256_loadu_pd(arr);
    __m256d v9 = _mm256_loadu_pd(arr);
    __m256d v10 = _mm256_loadu_pd(arr);
    __m256d v_const1 = _mm256_loadu_pd(arr_const);
    __m256d v_const2 = _mm256_loadu_pd(arr_const);

    // Time the add
    st = rdtsc();
    
    //TODO:Put your chains here
    FMA10_625(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v_const1, v_const2);
    
    et = rdtsc();

    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_FMA: %llu\n\r",sum / runs);
  printf("TURBO Cycles Taken for SIMD_FMA: %lf\n\r",sum * ((double)MAX_FREQ)/ (BASE_FREQ * runs));
  printf("Throughput : %lf\n\r",(double)(NUM_INST * NUM_CHAINS) / (sum / runs * MAX_FREQ/BASE_FREQ));

return 0;
}
