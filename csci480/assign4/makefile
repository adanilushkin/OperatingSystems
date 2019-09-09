assign4.exe: assign4.o Process.o history.o
	g++ -Wall -std=c++11 -o assign4.exe assign4.o Process.o history.o

assign4.o: Process.cc Process.h history.h 
	g++ -Wall -std=c++11 -c assign4.cc

Process.o: Process.cc Process.h history.h
	g++ -Wall -std=c++11 -c Process.cc

history.o: history.h
	g++ -Wall -std=c++11 -c 
clean:
	-rm *.o *.exe
