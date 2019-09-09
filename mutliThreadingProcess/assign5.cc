/***************************************************************
*PROGRAMMER:  ALEX DANILLUSHKIN
*Z-ID:        Z1809166
*CLASS:       CSCI480-02
*DUE DATE:    03/24/2019
*ASSIGNMENT:  5
*
*PURPOSE:     THE PURPOSE OF THIS ASSIGNMENT WAS TO GET US USING
*             AND EXPERIMENTING WITH MUTEX, THREADS, AND ANOTHER
*             EXAMPLE OF THE USE OF SEMAPHORES.
****************************************************************/

//....................INCLUDE STATEMENTS.........................
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <queue>
#include <semaphore.h>

using namespace std;

//...............CONSTANTS & GLOBAL VARIABLES....................
const int pThreadNum = 7;
const int cThreadNum = 5;
const int pSteps = 5;
const int cSteps = 7 ;
pthread_mutex_t mutex;
sem_t notFull;
sem_t notEmpty;


/*...........................WIDGET..............................
* Use: Widget is a struct that is created and put into a queue
*      by the producer thread. It keeps track of the producer
*      that made it, and the i-th number widget it is for that
*      particular thread.
*
* Parameters: 1. A long that is the producer ID
*	      2. An int that is the i-th production for
*                that particular thread
*
* Returns: Nothing(Struct)
...............................................................*/
struct Widget{

	long proID;
	int wigID;

	Widget(long myProducer, int myWidget){
		proID = myProducer;
		wigID = myWidget;
	}

};

//Widget constants
int wigCount = 0;
queue<Widget> bufferQ;

//........................FUNCTIONS............................



/*.........................PRODUCE.............................
* Use: The use of this function is to create a widget.
*
* Parameters: 1. A long that is the Thread ID of producer
*	      2. An int that is the i-th widget from the
*                producer.
*
* Returns: A widget
..............................................................*/
Widget produce(long tID, int widgNum){
	Widget widget(tID, (widgNum + 1) );
	return widget;
}

/*.......................PRINT QUEUE...........................
* Use: The purpose of this function is to print out what is
*      our queue. The queue fills up as more producer threads
*      add widgets to it and emptys as consumer threads take
*      from it.
*
* Parameters: 1. A copy of our queue we'd like to print.
*
* Returns: void
..............................................................*/
void printQueue(queue<Widget> q){

	while(!q.empty()){
		cout << "P" << q.front().proID << "W" << q.front().wigID << " ";
		q.pop();
	}

	cout << endl << endl;;
}

/*..........................INSERT............................
* Use: The purpose of this function is to add a new widget to
*      the buffer queue. Uses the mutex to make sure nothing
*      is changing as something else is changing it.
*
* Parameters: 1. A widget to be pushed to queue
*
* Returns: void
..............................................................*/
void insert(Widget myWidget){

	pthread_mutex_lock(&mutex);   //Lock the mutex

	bufferQ.push(myWidget);       //Add the widget to the buffer
	wigCount++;                   //Increment Counter
	cout << "Producer " << myWidget.proID  << " inserted one item. Total is now " << wigCount << ". Buffer now contains:" << endl;
	printQueue(bufferQ);          //print before unlock as to not let any threads true value of bufferQ

	pthread_mutex_unlock(&mutex); //unlock mutex
	sleep(1);

}

/*.........................REMOVE.............................
* Use: The purpose of this function is to remove an item from
*      the front of the queue. Uses a mutex to make sure no
*      other thread is changing the queue as it changes it.
*
* Parameters: 1. A long that is the thread ID of the Consumer
*                thread that it is calling it.
*
* Returns: void
.............................................................*/
void remove(long conID){

	pthread_mutex_lock(&mutex);   //lock mutex to hold inserting and removing

	bufferQ.pop();                //remove a widget from the buffer
	wigCount--;                   //Decrement counter
	cout << "Consumer " << conID << " removed one item. Total is now " << wigCount << ". Buffer now contains:" << endl;
	printQueue(bufferQ);

	pthread_mutex_unlock(&mutex); //unlock mutex
	sleep(1);
}


/*.....................THREAD: PRODUCER......................
* Use: The purpose of this thread is to create and add new
*      widgets to the queue. Does this for pStep times.
*
* Parameters: 1. A void * to the long that will be its' ID
*	         number.
* Returns: void *.
...........................................................*/
void * producer(void * threadid){

	long tID = (long) threadid;

	for(int i = 0; i < pSteps; i++){
		sem_wait(&notFull);               //wait until notFull is greater than 0

		Widget newWidg = produce(tID, i); //Create a new widget
		insert(newWidg);                  //Insert the new widget into the queue

		sem_post(&notEmpty);              //Decrement notEmpty since we took away a space
	}

	//hold mutex as not to overload cout buffer
	pthread_mutex_lock(&mutex);
	cout << endl << "Closing producer thread " << tID << endl << endl;
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

/*.....................THREAD: CONSUMER.....................
* Use: The purpose of this thread is to remove things from
*      our queue of widgets a number of cStep times.
*
* Parameters: 1. A void * to the long that will be its' ID
*                number.
*
* Returns: void
...........................................................*/
void * consumer(void * threadid){

	long tID = (long) threadid;

	for(int i = 0; i < cSteps; i++){
		sem_wait(&notEmpty);
		remove(tID);
		sem_post(&notFull);
	}

	//hold mutex as not to overload cout buffer
	pthread_mutex_lock(&mutex);
	cout << endl << "Closing consumer thread " << tID << endl << endl;
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

/*.........................MAIN............................
* Use: The main function starts up and closes all our
*      threads. It also initalizes all of the semaphores
*      and the one mutex.
*
* Parameters: None
*
* Returns: 0 if everything ran properly
..........................................................*/
int main(){

	//Initalizations
	sem_init(&notFull, 0, 35);
	sem_init(&notEmpty, 0, 0);
	if(pthread_mutex_init(&mutex, NULL) != 0){
		cout << "Mutex failed to initalize" << endl;
		return -1;
	}

	pthread_t proThreads[pThreadNum];
	pthread_t conThreads[cThreadNum];
	int newThread;
	long t;

	//Create  threads
	for(t = 0; t < pThreadNum; t++){
		newThread = pthread_create(&proThreads[t], NULL, &producer, (void *) t);
		if(newThread){
			cout << "Error: Something happened while a new producer thread was being made" << endl;
			exit(-1);
		}
		if(t < cThreadNum){
			newThread = pthread_create(&conThreads[t], NULL, &consumer, (void *) t);
			if(newThread){
				cout << "Error: Something happened while a new consumer thread was being made" << endl;
			}
		}
	}

	//close threads
	for(int i = 0; i < pThreadNum; i++){
		pthread_join(proThreads[i], NULL);
	}

	for(int i = 0; i < cThreadNum; i++){
		pthread_join(conThreads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	sem_destroy(&notFull);
	sem_destroy(&notEmpty);

	cout << "All threads have been closed" << endl;

	return 0;

}
