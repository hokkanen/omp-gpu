FC = ftn
FFLAGS = -fopenmp -hmsgs -hlist=m

all: omp-usm

omp-usm: omp-usm.o omp-usm-mod.o
	$(FC) $(FFLAGS) -o omp-usm omp-usm.o omp-usm-mod.o

omp-usm.o: omp-usm.F90 omp-usm-mod.o
	$(FC) $(FFLAGS) -c omp-usm.F90

omp-usm-mod.o: omp-usm-mod.F90
	$(FC) $(FFLAGS) -c omp-usm-mod.F90

clean:
	rm -f *.lst *.mod *.o omp-usm
