program omptest
  use omp_lib
  implicit none

  integer, parameter :: size = 10
  integer, dimension(0:size-1) :: array
  integer :: i

  !$omp target data map(alloc:array(0:size-1))
    !$omp target teams distribute parallel do
      do i = 0, size - 1
        array(i) = 1
      end do
    !$omp end target teams distribute parallel do

    !$omp target update from(array(5:7))
  !$omp end target data

  do i = 0, size - 1
    write(*,*) 'array(', i, '): ', array(i) 
  end do

end program
