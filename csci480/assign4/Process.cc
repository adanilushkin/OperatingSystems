
#include "Process.h"

struct compareP{
	bool operator()(Process const& lhs, Process const& rhs){
		return lhs.Priority < rhs.Priority;
	}
};

Process::Process(){
	ProcessName = "";
	Priority = 0;
	ProcessID = -1;
	ArrivalTime = -1;
	histIndex = 0; 
	CPUTimer = 0;
	IOTimer = 0;
	CPUTotal = 0;
	ITotal = 0;
	OTotal = 0;
	CPUCount = 0;
	ICount = 0;
	OCount = 0;
}

Process::Process(string name, int priority, int arrival){
	//Set upon Construction
	ProcessName = name;
	Priority = priority;
	ArrivalTime = arrival;
	
	//To be set later
	ProcessID = 0;
	histIndex = 0; 
	CPUTimer = 0;
	IOTimer = 0;
	CPUTotal = 0;
	ITotal = 0;
	OTotal = 0;
	CPUCount = 0;
	ICount = 0;
	OCount = 0;
}

void Process::terminate(){

	ProcessName = "";
	Priority = 0;
	ProcessID = -1;
	ArrivalTime = -1;
	histIndex = 0; 
	CPUTimer = 0;
	IOTimer = 0;
	CPUTotal = 0;
	ITotal = 0;
	OTotal = 0;
	CPUCount = 0;
	ICount = 0;
	OCount = 0;
}

Process operator<(const Process& lhs, const Process& rhs){
	if(lhs.Priority < rhs.Priority)
		return lhs; 
	else
	return rhs;
}
