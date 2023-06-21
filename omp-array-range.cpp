#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

  const int size = 10;
  int *array = (int*)calloc(size, sizeof(int));

  #pragma omp target data map(alloc:array[0:size])
  {
    #pragma omp target teams distribute parallel for
    for(int i = 0; i < size; i++ )
      array[i] = 1;

    #pragma omp target update from(array[5:3])
  }

  for(int i = 0; i < size; i++ )
    printf("array[%d]: %d\n",i,array[i]);

  free(array);
}
