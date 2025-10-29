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
#define MULTIPLY(dest, src) \
  __asm__ volatile( \
    "imul %[rsrc], %[rdest]" \
    : [rdest] "+r"(dest) \
    : [rsrc] "r"(src) \
  );

#define MULTIPLY5(x, a) \
  MULTIPLY(x, a) \
  MULTIPLY(x, a) \
  MULTIPLY(x, a) \
  MULTIPLY(x, a) \
  MULTIPLY(x, a)

#define MULTIPLY25(x, a) \
  MULTIPLY5(x, a) \
  MULTIPLY5(x, a) \
  MULTIPLY5(x, a) \
  MULTIPLY5(x, a) \
  MULTIPLY5(x, a)

#define MULTIPLY125(x, a) \
  MULTIPLY25(x, a) \
  MULTIPLY25(x, a) \
  MULTIPLY25(x, a) \
  MULTIPLY25(x, a) \
  MULTIPLY25(x, a)

#define MULTIPLY625(x, a) \
  MULTIPLY125(x, a) \
  MULTIPLY125(x, a) \
  MULTIPLY125(x, a) \
  MULTIPLY125(x, a) \
  MULTIPLY125(x, a)

int main(int argc, char **argv) {

  
  // int runs = atoi(argv[1]);
  // You might want to use the above code to control number of runs.
  int runs = 100;

  unsigned long long st;
  unsigned long long et;
  unsigned long long sum = 0;

  int x = 2;
  // for (int j = 0; j < runs; j++) {
    st = rdtsc();
    //TODO: Put your latency testing code here
    MULTIPLY625(x, 2);

    et = rdtsc();
    // Chain of NUM_INST simd add instructions
    sum += (et-st);

  // }
  printf("the value of x is %i", x);

  printf("RDTSC Base Cycles Taken for int_mul: %llu\n\r",sum);
  printf("Latency: %lf\n\r", MAX_FREQ/BASE_FREQ * sum / NUM_INST);

  return 0;
}
