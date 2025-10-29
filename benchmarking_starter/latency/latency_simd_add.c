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


//TODO: define your macros here
//Hint: You may want to write Macros that call Macro intrinsics
#define ADD(dest, src) \
  __asm__ volatile( \
    "vaddpd %[s], %[d], %[d]" \
    : [d] "+x"(dest) \
    : [s]  "x"(src)  \
  );

#define ADD5(a, b) \
  ADD(a,b) \
  ADD(a,b) \
  ADD(a,b) \
  ADD(a,b) \
  ADD(a,b)

#define ADD25(a, b) \
  ADD5(a,b) \
  ADD5(a,b) \
  ADD5(a,b) \
  ADD5(a,b) \
  ADD5(a,b)

#define ADD125(a, b) \
  ADD25(a,b) \
  ADD25(a,b) \
  ADD25(a,b) \
  ADD25(a,b) \
  ADD25(a,b)

#define ADD625(a, b) \
  ADD125(a,b) \
  ADD125(a,b) \
  ADD125(a,b) \
  ADD125(a,b) \
  ADD125(a,b)

int main(int argc, char **argv) {

  
  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;

  // for (int j = 0; j < runs; j++) {
    double arr1[4] = {1.0, 0.0, 0.0, 0.0};
    double arr2[4] = {1.0, 0.0, 0.0, 0.0};
    __m256d v1 = _mm256_loadu_pd(arr1);
    __m256d v2 = _mm256_loadu_pd(arr2);

    st = rdtsc();
    //TODO: Put your latency testing code here
    ADD625(v1, v2);

    et = rdtsc();
    // Chain of NUM_INST simd add instructions
    sum += (et-st);
    
  // }

  printf("RDTSC Base Cycles Taken for SIMD_ADD: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / NUM_INST);

  return 0;
}
