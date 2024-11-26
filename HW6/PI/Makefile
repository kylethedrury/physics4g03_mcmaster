CPP=g++
LINKER=g++
#FFLAGS=-O3 -openmp -std=c++11 -lomp
FFLAGS= -Wall -O3 -fopenmp -std=c++11

LFLAGS=-fopenmp
OBJECTFILES=pi1.o\

default: pi

pi: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@ 

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

pi1.o: pi1.cc

clean:
	rm *.o
