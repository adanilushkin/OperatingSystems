#ifndef ASSIGN7_H
#define ASSIGN7_H
#include <string>
#include <vector>

using namespace std;

/*...........................ENTRY...............................
* Use: Entry is to represent the incoming files from the text
*
* Parameters: 1. A string that is the file name
*	          2. An int that is the size of the file
*			  3. An int that is the inital cluster in the FAT
*
* Returns: Nothing(Struct)
...............................................................*/
struct Entry{
 string name = "";
 int size = 0;
 int initCluster = -1;
};

//...............CONSTANTS & GLOBAL VARIABLES....................
const int clusterBlock = 12;
const int clusterSize = 512;
int fat[4096] = {0};
list<Entry> dir;
list<Entry>::iterator entryIT;

void   add(Entry&);//Add to the directory
void   remove(string);//remove from directory
void   fileReader();//reads file

int    createInitCluster(int);//finds initial cluster and allocates to fat
vector<int> findClusters(Entry);//returns vector of used clusters for file
bool   needResize();//check if main directory needs to be resized
bool   searchList(string);//checks if the name of the file is in the directory

void   reallocate(Entry&);//reinstances the clusters
void   deallocate(string);//removes used clusters

void   printFAT();//prints the FAT table
void   print();//prints the directory

#endif

