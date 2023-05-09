#include <stdio.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000000

int main(int argc, char *argv[]){

    int A[SIZE];
    int num_gpus = omp_get_num_devices();

    clock_t t_start = clock();
    for(int n = 0; n < num_gpus; n++)
    {
        omp_set_default_device(n);
        #pragma omp target teams distribute parallel for map(from:A[n * (SIZE / 4):SIZE/4]) nowait
        for (int i = n * (SIZE / 4); i < (n + 1) * (SIZE / 4); i++) {
            A[i] = i;
        }
        double t_s = (double) (clock() - t_start) / CLOCKS_PER_SEC;
        printf("  kernel #%d, time since begin: %e s\n", n, t_s);

    }

    #pragma omp taskwait
    for (int n = 0; n < num_gpus; n++)
        printf("CPU thread %d, post-loop value from GPU %d: %d\n", omp_get_thread_num(), n, A[SIZE / 4 * (n + 1) - 1]);
}
