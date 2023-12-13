program omptest
  use OMP_LIB
  use TARGET_MODULE
  implicit none
  !$omp requires unified_shared_memory

  integer, parameter :: size = 10
  integer, dimension(1:size) :: array
  integer :: i

  !$omp target data map(alloc:array(1:size))
    !$omp target teams distribute parallel do
      do i = 1, size
        call set_array_element(array, i)
      end do
    !$omp end target teams distribute parallel do

    !$omp target update from(array(5:7))
  !$omp end target data

  do i = 1, size
    write(*,*) 'array(', i, '): ', array(i) 
  end do

end program