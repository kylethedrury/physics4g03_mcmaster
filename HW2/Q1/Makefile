GS = -O2 -std=c++11
LFLAGS = 

main: main.o
	g++ main.o $(LFLAGS) -o main

main.o: main.cc
	g++ $(GS) -c main.cc

clean:
	rm *.o
