#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

void kernel
(
  int              m,
  int              n,
  int              k,
  double* restrict a,
  double* restrict b,
  double* restrict c
){
 
  //TODO: Implement a small mxk * kxn matrix multiplication here

  // m = 10, n = 4
  __m256d vrow0 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow1 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow2 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow3 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow4 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow5 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow6 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow7 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow8 = _mm256_set_pd(0, 0, 0, 0);
  __m256d vrow9 = _mm256_set_pd(0, 0, 0, 0);

  for (int i = 0; i < k; i++) {

    // load a row of B
    __m256d vb = _mm256_loadu_pd(&b[i * 4]);

    // broadcast each element of the column of A
    __m256d va0 = _mm256_set1_pd(a[i * 10 + 0]);
    __m256d va1 = _mm256_set1_pd(a[i * 10 + 1]);
    __m256d va2 = _mm256_set1_pd(a[i * 10 + 2]);
    __m256d va3 = _mm256_set1_pd(a[i * 10 + 3]);
    __m256d va4 = _mm256_set1_pd(a[i * 10 + 4]);
    __m256d va5 = _mm256_set1_pd(a[i * 10 + 5]);
    __m256d va6 = _mm256_set1_pd(a[i * 10 + 6]);
    __m256d va7 = _mm256_set1_pd(a[i * 10 + 7]);
    __m256d va8 = _mm256_set1_pd(a[i * 10 + 8]);
    __m256d va9 = _mm256_set1_pd(a[i * 10 + 9]);

    // vrow = vb * va + vrow
    vrow0 = _mm256_fmadd_pd(vb, va0, vrow0);
    vrow1 = _mm256_fmadd_pd(vb, va1, vrow1);
    vrow2 = _mm256_fmadd_pd(vb, va2, vrow2);
    vrow3 = _mm256_fmadd_pd(vb, va3, vrow3);
    vrow4 = _mm256_fmadd_pd(vb, va4, vrow4);
    vrow5 = _mm256_fmadd_pd(vb, va5, vrow5);
    vrow6 = _mm256_fmadd_pd(vb, va6, vrow6);
    vrow7 = _mm256_fmadd_pd(vb, va7, vrow7);
    vrow8 = _mm256_fmadd_pd(vb, va8, vrow8);
    vrow9 = _mm256_fmadd_pd(vb, va9, vrow9);
  }

  _mm256_storeu_pd(&c[0], vrow0);
  _mm256_storeu_pd(&c[4], vrow1);
  _mm256_storeu_pd(&c[8], vrow2);
  _mm256_storeu_pd(&c[12], vrow3);
  _mm256_storeu_pd(&c[16], vrow4);
  _mm256_storeu_pd(&c[20], vrow5);
  _mm256_storeu_pd(&c[24], vrow6);
  _mm256_storeu_pd(&c[28], vrow7);
  _mm256_storeu_pd(&c[32], vrow8);
  _mm256_storeu_pd(&c[36], vrow9);

}
