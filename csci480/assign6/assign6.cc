#include "MemBlock.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>

using namespace std;

const int mb = 1048576;

void firstFit(MemBlock& myBlock, ProcSeg process){

 if(myBlock.getAvalSize() < process.procSize){
      if(myBlock.next != NULL){
	firstFit(*(myBlock.next) , process);
      }
      else{
	cout << "Cannot find avaliable block" << endl;
	exit(EXIT_FAILURE);
      }
 }
 //else
 //find first index where process isn't initialized
 int count = 0;
 while(myBlock.process[count].numID != 0){
   count++;
 }
 //add process to memory block
 myBlock.process[count] = ProcSeg(process);
 myBlock.process[count].MemBlockID = myBlock.getID();

 myBlock.setAvalSize(process.procSize);//Decrement avaliable size by size of process
}


//std::list<MemBlock> avail;
//std::list<MemBlock> in_use;

int main(){

 //creating and linking blocks
 MemBlock mb1Block = MemBlock(mb);
 MemBlock mb2Block0 = MemBlock(2*mb);
 MemBlock mb2Block1 = MemBlock(2*mb);
 MemBlock mb4Block0 = MemBlock(4*mb);
 MemBlock mb4Block1 = MemBlock(4*mb);

 mb2Block0.pushBack(mb1Block);
 mb2Block1.pushBack(mb2Block0);
 mb4Block0.pushBack(mb2Block1);
 mb4Block1.pushBack(mb4Block0);

 MemBlock* pointer = &mb1Block;

 while(pointer != NULL){

 	cout << "We have created a Block with ID = " << pointer->getID();
 	cout << " size = " << pointer->getMemSize() << " and address at ";
 	cout << pointer->getAddress() << endl << endl;

	pointer = pointer->next;
 }

/*
 avail.push_back(mb2Block0);
 avail.push_back(mb2Block1);
 avail.push_back(mb4Block0);
 avail.push_back(mb4Block1);

 for (auto& block : avail) {

	if(block.front != NULL){
		block.pushBack(*(block.front));
	}
 }
 */


 char action;
 ProcSeg* proc = new ProcSeg;

 ifstream myfile( "/home/turing/t90hch1/csci480/Assign6/data6.txt");
 if(myfile.is_open()){
  myfile >> action;
  if(action == 'L'){
	myfile >> proc->numID >> proc->procSize;
	myfile >> proc->procID;
//	cout << proc->numID << " " << proc->procSize << " " << proc->procID << endl;
        firstFit(mb1Block, *proc);
  }

  if(action == 'A'){
	myfile >> proc->numID >> proc->procSize;
	myfile >> proc->procID;
        firstFit(mb1Block, *proc);
  }
 }
 myfile.close();

 cout << "Process ID is " << mb1Block.process[0].numID << endl;
 cout << "Address of " << mb1Block.getID() << " is " << mb1Block.getAddress() << endl;
 return (0);

}
