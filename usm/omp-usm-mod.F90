module target_module
    implicit none
  contains
  
    subroutine set_array_element(array, index)
      !!!!$omp declare target (set_array_element)
      integer, dimension(:) :: array
      integer :: index
  
      array(index) = 1
    end subroutine set_array_element
  
  end module target_module
