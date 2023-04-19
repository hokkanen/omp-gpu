#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000000

int main(int argc, char *argv[]){

    int A[SIZE];

    #pragma omp parallel for
    for(int n = 0; n < omp_get_num_devices(); n++)
    {
        omp_set_default_device(n);
        #pragma omp target teams distribute parallel for //nowait
        for (int i = n * (SIZE / 4); i < (n + 1) * (SIZE / 4); i++) {
            A[i] = i;
        }
        printf("  CPU thread %d, last value from GPU %d: %d\n", omp_get_thread_num(), n, A[SIZE / 4 * (n+1) - 1]);

    }
    //#pragma omp taskwait
    for(int n = 0; n < omp_get_num_devices(); n++)
      printf("CPU thread %d, post-loop value from GPU %d: %d\n", omp_get_thread_num(), n, A[SIZE / 4 * (n+1) - 1]);
}
