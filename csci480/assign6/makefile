#PROGRAMMER:   ALEX DANILUSHKIN
#Z-ID:         Z1809166
#CLASS:        CSCI 480-02
#DUE DATE:     04/10/19
#ASSIGNMENT:   6

CCFLAGS = -Wall -std=c++11

assign6: assign6.o MemBlock.o
	g++ $(CCFLAGS) -o $@ assign6.o MemBlock.o

assign6.o: assign6.cc MemBlock.h
	g++ $(CCFLAGS) -c assign6.cc

MemBlock.o: MemBlock.cc MemBlock.h
	g++ $(CCFLAGS) -c MemBlock.cc

clean:
	-rm *.o assign6

