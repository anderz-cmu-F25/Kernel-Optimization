#include "stdlib.h"
#include "transposes.h"
#include <immintrin.h>

void morton(double *a, double *b,  int N){
    // base case
    if (N <= 2) {
        // printf("\n%lf\t", a[0]);
        // printf("%lf\t", a[1]);
        // printf("%lf\t", a[2]);
        // printf("%lf\n", a[3]);

        // b[0] = a[0];
        // b[1] = a[2];
        // b[2] = a[1];
        // b[3] = a[3];

        __m256d v = _mm256_loadu_pd(a);
        v = _mm256_permute4x64_pd(v, 0xD8);
        _mm256_storeu_pd(b, v);

        // printf("\n%lf\t", b[0]);
        // printf("%lf\t", b[1]);
        // printf("%lf\t", b[2]);
        // printf("%lf\n", b[3]);

        return;
    }

    // printf("will not reach here\n");
    const size_t quarter = N * N / 4;
    const size_t new_size = N / 2;

    // recursive case
    morton(a, b, new_size);
    morton(a + quarter, b + quarter, new_size);
    morton(a + 2 * quarter, b + 2 * quarter, new_size);
    morton(a + 3 * quarter, b + 3 * quarter, new_size);

    // rearrange the quadrants from 0 1 2 3 to 0 2 1 3
    for (int i = 0; i < quarter; i += 4) {

        // double temp = b[(N * N / 4) + i];
        // b[(N * N / 4) + i] = b[2*(N * N / 4) + i];
        // b[2*(N * N / 4) + i] = temp;

        __m256d vx = _mm256_loadu_pd(b + quarter + i);   // 4 doubles
        __m256d vy = _mm256_loadu_pd(b + 2 * quarter + i);
        _mm256_storeu_pd(b + quarter + i, vy);
        _mm256_storeu_pd(b + 2 * quarter + i, vx);
    }
}
