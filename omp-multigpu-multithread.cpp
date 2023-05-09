#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000000

int main(int argc, char *argv[]){

    int A[SIZE];
    int num_gpus = omp_get_num_devices();
    
    clock_t t_start = clock();
    #pragma omp parallel num_threads(num_gpus)
    {
        int n = omp_get_thread_num();
        #pragma omp target teams distribute parallel for map(from:A[n * (SIZE / 4):SIZE/4]) device(n)
        for (int i = n * (SIZE / 4); i < (n + 1) * (SIZE / 4); i++) {
            A[i] = i;
        }
        double t_s = (double) (clock() - t_start) / CLOCKS_PER_SEC;
        printf("  CPU thread %d, last value from GPU %d: %d (%e s)\n", omp_get_thread_num(), n, A[SIZE / 4 * (n + 1) - 1], t_s);
    }

    for(int n = 0; n < num_gpus; n++)
      printf("CPU thread %d, post-loop value from GPU %d: %d\n", omp_get_thread_num(), n, A[SIZE / 4 * (n + 1) - 1]);
}
