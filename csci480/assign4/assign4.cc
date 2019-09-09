
#include <iostream> //output stream
#include <fstream>
#include <stdio.h>  //used for file reading
#include "Process.h" //includes header files and std::String class
#include "Process.cc"
#include <queue>
#include <string>
#include <cstring>
#include <utility>

const int MAXTIME = 500;
const int AT_ONCE = 5;
const int HOW_OFTEN = 25;

int main(){

//	cout << "making a new Process " << endl;
//	Process w =  Process("BUFFYTVS", 7, 11);
//	cout << "we have made " << w.ProcessName << endl;

	queue<Process> EntryQ;

	//Reading variables
	Process* readP = NULL;
	string processToParse[3]; //Parse the Process line
	//string historyToParse[20]; //used to parse the history line
	int setPID = 100; //intial PID of incoming Processes

	//Reading File
	std:: ifstream inputFile("myFile.txt");
	if(!inputFile.is_open()) perror ("Could not open file");
	else{

		while(processToParse[0].compare("STOPHERE") != 0 ){

			//Reading in Process
			for(int i = 0; i < 3; i++){
				inputFile >> processToParse[i];
				cout << processToParse[i] << endl;
				if(processToParse[i] == "STOPHERE")
					break;
			}

			//Create new Process
			readP = new Process(processToParse[0], stoi(processToParse[1]), stoi(processToParse[2]) );

			//Incriment its PID
			readP->ProcessID = setPID;
			setPID++;

			//Reading in history struct
			for(int i = 0; i < 10; i++ ){
				inputFile >> readP->procHist[i]->letter;
				inputFile >> readP->procHist[i]->value;
			}

			//link history obj to process
			/*
			int j = 0;
			while(historyToParse[j] != "N" ){
				readP->procHist[j] = new History(*historyToParse[j].c_str(), stoi(historyToParse[j+1])); 
				j = j+2;
			}*/

			cout << "Now pushing " << readP->ProcessName << " into Entry queue" << endl;
			EntryQ.push(*readP);
		}
	}
	inputFile.close();

	cout<< "Processes read successfully" << endl << endl;

	//Creating readyQ which happens to be a priority Q
	priority_queue<Process, vector<Process>, compareP> ReadyQ;
	int timer = 0;
	int pCount = 0;//compare to At_once

	while(timer < MAXTIME && (!EntryQ.empty() || !ReadyQ.empty() ) ){//keep going while we wtill have time and processes still exist
		while(pCount < AT_ONCE){
			ReadyQ.push(EntryQ.front());
			EntryQ.pop();
			pCount++;
		}

		while(!ReadyQ.empty()){
			cout << "Processing " << ReadyQ.top().ProcessName << endl;
			cout << "Now displaying history array" << endl;

			int i = 0;
			while(ReadyQ.top().procHist[i]->letter != 'N'){
				cout << ReadyQ.top().procHist[i]->letter << ReadyQ.top().procHist[i]->value << " ";
				i++;
			}
			cout << endl;

			ReadyQ.pop();
			pCount--;
		}
		timer++;
	}

	cout << "Reading top name of pQ " << ReadyQ.top().ProcessName << endl;


	return 0;

}
