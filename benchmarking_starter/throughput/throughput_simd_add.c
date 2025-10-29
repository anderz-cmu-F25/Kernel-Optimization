#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.2
#define BASE_FREQ 2.4

//TODO: Change number of instructions to reflect your chains
#define NUM_INST 625.0
//TODO: Change to reflect number of independent chains
#define NUM_CHAINS 1

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

//TODO: Define your Macros here
#define ADD(dest, src) \
  __asm__ volatile( \
    "vaddpd %[s], %[s], %[d]" \
    : [d] "+x"(dest) \
    : [s]  "x"(src)  \
  );

#define ADD10(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD(a,const) \
  // ADD(b,const) \
  // ADD(c,const) \
  // ADD(d,const) \
  // ADD(e,const) \
  // ADD(f,const) \
  // ADD(g,const) \
  // ADD(h,const) \
  // ADD(i,const) \
  // ADD(j,const)

#define ADD10_5(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10(a, b, c, d, e, f, g, h, i ,j, const)

#define ADD10_25(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_5(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_5(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_5(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_5(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_5(a, b, c, d, e, f, g, h, i ,j, const)

#define ADD10_125(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_25(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_25(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_25(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_25(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_25(a, b, c, d, e, f, g, h, i ,j, const)

#define ADD10_625(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_125(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_125(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_125(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_125(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_125(a, b, c, d, e, f, g, h, i ,j, const)

#define ADD10_3125(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_625(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_625(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_625(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_625(a, b, c, d, e, f, g, h, i ,j, const) \
  ADD10_625(a, b, c, d, e, f, g, h, i ,j, const)


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
    __m256d v_const = _mm256_loadu_pd(arr_const);

    // Time the add
    st = rdtsc();
    
    //TODO: Put your chains here
    //You should be computing NUM_INST*NUM_CHAINS instructions
    ADD10_625(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v_const);

    et = rdtsc();

    sum += (et-st);

  }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r",sum / runs);
  printf("TURBO Cycles Taken for SIMD_ADD: %lf\n\r",sum * ((double)MAX_FREQ)/ (BASE_FREQ * runs));
  printf("Throughput : %lf (chains: )\n\r",((double)NUM_INST * NUM_CHAINS) / (sum / runs * MAX_FREQ/BASE_FREQ));

return 0;
}
