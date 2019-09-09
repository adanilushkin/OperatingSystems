#ifndef PROCESS_H
#define PROCESS_H

#include "history.h"
#include <stdlib.h>
#include <string>

using namespace std;


class Process{
	
	public:
	//Constructors
	Process();
	Process(string, int, int);
	//Public variables
	string ProcessName;
	int Priority;
	int ProcessID;
	int ArrivalTime;
	History *procHist[10]; //size will be initalized later as to not waste array space
	int histIndex; 
	int CPUTimer;
	int IOTimer;
	int CPUTotal;
	int ITotal;
	int OTotal;
	int CPUCount;
	int ICount;
	int OCount;
	
	//method
	void terminate();
};

#endif
