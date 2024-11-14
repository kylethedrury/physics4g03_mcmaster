CPP=g++
LINKER=g++
FFLAGS=-O3 -std=c++11
LFLAGS=
OBJECTFILES=main.o\
            readin.o\
            pheader.o\
            setparams.o

default: MD

MD: $(OBJECTFILES)
	echo "Compiling"; \
	$(LINKER) $(LFLAGS) $(OBJECTFILES) -o $@

$(OBJECTFILES):
	$(CPP) $(FFLAGS) $*.cc -c

main.o: main.cc MDsim.h
readin.o: readin.cc MDsim.h
setparams.o: setparams.cc MDsim.h
pheader.o: pheader.cc MDsim.h

clean:
	rm *.o
