#PROGRAMMER:    ALEX DANILUSHKIN
#DUE DATE:      04/24/2019
#ZID:           Z1809166
#ASSIGNMENT:    7

CC = g++
CCFLAGS = -Wall -std=c++11

assign7: assign7.o
	$(CC) $(CCFLAGS) -o assign7 assign7.o

assign7.o: assign7.cc
	$(CC) $(CCFLAGS) -c assign7.cc

clean:
	rm *.o assign7
