CPP=g++
LINKER=g++
#FFLAGS=-O3 -openmp -std=c++11 -lomp
FFLAGS= -Wall -O3 -fopenmp -std=c++11

LFLAGS=-fopenmp
OBJECTFILES=hello1.o\

default: Hello

Hello: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@ 

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

hello1.o: hello1.cc

clean:
	rm *.o Hello
