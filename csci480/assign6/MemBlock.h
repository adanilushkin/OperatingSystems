
#ifndef MEMBLOCK_H
#define MEMBLOCK_H

#include <string>

using namespace std;

struct ProcSeg{

 int numID = 0;
 int procSize = 0;
 int MemBlockID;
 string procID;

 ProcSeg() = default;
 ProcSeg(const ProcSeg& input){
     numID = input.numID;
     procSize = input.procSize;
     procID = input.procID;
 }
};

class MemBlock{

public:

 //public methods
 int getAddress();
 int getID();
 int getMemSize();
 int getAvalSize();
 void setAvalSize(int);
 void pushBack(MemBlock&);

 //variables
 MemBlock* next = NULL;
 MemBlock* front = NULL;
 ProcSeg process[5];

 //Constructors
 MemBlock(int); //address, size
 MemBlock(const MemBlock&);//copy construtor

private:
 //static int nextId;

 //private methods
 void setAddress();
 void setID();

 //variables
 int address = 3145728;
 int memSize;
 int avalSize;
 int id = 0;

};
#endif
