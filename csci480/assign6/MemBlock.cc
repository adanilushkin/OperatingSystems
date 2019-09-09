#include "MemBlock.h"
#include <iostream>

using namespace std;

//Methods............................................
int MemBlock::getAddress(){
 if(process[0].numID != 0){
	int curAddress = address;
	for(int i = 0; i < 5; i++){
		curAddress += process[i].procSize; 
	}
	return curAddress;
 }
 return address;
}

int MemBlock::getID(){
 return id;
}

int MemBlock::getMemSize(){
 return memSize;
}

int MemBlock::getAvalSize(){
 return avalSize;
}

void MemBlock::setAddress(){

 this->address = (this->front->getAddress() + this->front->getMemSize() );

}

void MemBlock::setAvalSize(int subtract){

 if( (avalSize - subtract) <= 0){
    cout << "Cannot decrement size" << endl;
    return;
 }
 avalSize = avalSize - subtract;

}
void MemBlock::setID(){

 this->id = (this->front->id + 1);
}

void MemBlock::pushBack(MemBlock &lastBlock){

 lastBlock.next = this;         //add block to chain
 this->front = &lastBlock;        //have block point to chain
 this->setAddress();
 this->setID();
}

//Constructors...................................
MemBlock::MemBlock(const int size){

 memSize = size;
 avalSize = size;
}

MemBlock::MemBlock(const MemBlock& copy){

 memSize = copy.memSize;
 avalSize = copy.memSize;
 next = copy.next;
 front = copy.front;
}
