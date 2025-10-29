#include <stdio.h>
#include <string.h>
#include <x86intrin.h>
#include <immintrin.h>

//TODO: Adjust the frequency based on your machine.
#define MAX_FREQ 3.2
#define BASE_FREQ 2.4

//TODO: Change this to reflect the number of instructions in your chain
#define NUM_INST 625.0 

static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


// TODO: Define your macros here
//Hint: You may want to write Macros that call Macro intrinsics
#define FMA(dest, src1, src2) \
  __asm__ volatile ( \
    "vfmadd231pd %[d], %[s1], %[s2]\n\t" \
    : [d] "+x"(dest) \
    : [s1] "x"(src1), [s2] "x"(src2) \
  );

#define FMA5(acc, a, b) \
  FMA(acc, a, b) \
  FMA(acc, a, b) \
  FMA(acc, a, b) \
  FMA(acc, a, b) \
  FMA(acc, a, b)

#define FMA25(acc, a, b) \
  FMA5(acc, a, b) \
  FMA5(acc, a, b) \
  FMA5(acc, a, b) \
  FMA5(acc, a, b) \
  FMA5(acc, a, b)

#define FMA125(acc, a, b) \
  FMA25(acc, a, b) \
  FMA25(acc, a, b) \
  FMA25(acc, a, b) \
  FMA25(acc, a, b) \
  FMA25(acc, a, b)

#define FMA625(acc, a, b) \
  FMA125(acc, a, b) \
  FMA125(acc, a, b) \
  FMA125(acc, a, b) \
  FMA125(acc, a, b) \
  FMA125(acc, a, b)

int main(int argc, char **argv) {

  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;
  

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;

  // for (int j = 0; j < runs; j++) {
  __m256d v1 = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
  __m256d v2 = _mm256_set_pd(5.0, 6.0, 7.0, 8.0);
  __m256d acc = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);

    st = rdtsc();
    //TODO: Put your latency testing code here
    FMA625(acc, v1, v2);

    et = rdtsc();
    // Chain of NUM_INST simd fma instructions
    sum += (et-st);

  // }

  printf("RDTSC Base Cycles Taken for SIMD_FMA: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / NUM_INST);

  return 0;
}
