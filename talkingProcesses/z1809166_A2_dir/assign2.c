/*********************************************************
CSCI 480 - ASSIGNMENT 2 - SPRING 2019

PROGRAMMER: ALEX DANILUSHKIN
Z-ID: Z1809166
SECTION: 1
TA: JOSHUA BOLEY
DUE DATE: FEBRUARY 8TH, 2019

PURPOSE: THE PURPOSE OF THIS ASSIGNMENT IS TO GET
A FUNDEMENTAL UNDERSTANDING OF PIPES AND HOW DIFFERENT
PROCESSES CAN TALK TO ONE ANOTHER
*********************************************************/

#include <sys/types.h>		/* needed to use pid_t, etc. */
#include <sys/wait.h>		/* needed to use wait() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* LINUX constants and functions (fork(), etc.) */
#include <string.h>

const int SIZE = 15;

/***************************************************************
Pwork

Use: This method initializes all the other methods. Like the
rest of the methods, the purpose is to pass along character
arrays holding the character value of an integer. It then does
some arithmetic, saves it back to the array, and passes it along.
After it passes it, it waits for the next value to come through.

Parameters: 1. writePipe: The write end of the pipe. The
               variable should be from the file descriptor.
               table.
            2. readPipe: The read end of the pipe. The
               variable should be from the file descriptor.
               table.

Returns: An integer so that the processes may end after the
         method is finished
***************************************************************/
int Pwork( int writePipe, int readPipe){

    printf("This is the parent. I am starting the process\n");
    char buffer[SIZE];
    char* ptr;

    memset(buffer, 0, sizeof(char)*SIZE);
    buffer[0] = '1';
    long int M = 1;

    write(writePipe, buffer, sizeof(char)*SIZE);
//    int COUNTER = 0;
    while(M < 99999999999){
        read(readPipe, buffer, sizeof(char)*SIZE);
        M = strtol(buffer, &ptr, 10); //char array, char pointer, base 10
        M = (3 * M) + 7;
        sprintf(buffer, "%ld", M);

        printf("Parent:                 Value = %s\n", buffer);
        write(writePipe, buffer, strlen(buffer) + 1);
    }

    return 1;
}

/***************************************************************
Cwork

Use: The purpose is to pass along character arrays holding the
character value of an integer. It then does some arithmetic,
saves it back to the array, and passes it along. After it
passes it, it waits for the next value to come through.

Parameters: 1. writePipe: The write end of the pipe. The
               variable should be from the file descriptor.
               table.
            2. readPipe: The read end of the pipe. The
               variable should be from the file descriptor.
               table.

Returns: An integer so that the processes may end after the
         method is finished
***************************************************************/
int Cwork(int writePipe, int readPipe){
    printf("Child initialized\n");
    char buffer[SIZE];
    char* ptr;
    long M = 1;

   // int COUNTER = 0;
    while(M < 99999999999){
        read(readPipe, buffer, sizeof(char)*SIZE);

        M = strtol(buffer, &ptr, 10); //char array, char pointer, base 10
        M = (3 * M) + 7;
        sprintf(buffer, "%ld", M);

        printf("Child:                  Value = %s\n", buffer);
        write(writePipe, buffer, strlen(buffer) + 1);

    }

    return 1;
}

/***************************************************************
Gwork

Use: The purpose is to pass along character arrays holding the
character value of an integer. It then does some arithmetic,
saves it back to the array, and passes it along. After it
passes it, it waits for the next value to come through.

Parameters: 1. writePipe: The write end of the pipe. The
               variable should be from the file descriptor.
               table.
            2. readPipe: The read end of the pipe. The
               variable should be from the file descriptor.
               table.

Returns: An integer so that the processes may end after the
         method is finished
***************************************************************/
int Gwork(int writePipe, int readPipe){
    printf("Grandchild initialized\n");
    char buffer[SIZE];
    char* ptr;
    long M = 1;

//    int COUNTER = 0;
    while(M < 99999999999){
        read(readPipe, buffer, sizeof(char)*SIZE);

        M = strtol(buffer, &ptr, 10); //char array, char pointer, base 10
        M = (3 * M) + 7;
        sprintf(buffer, "%ld", M);

        printf("Grandchild:             Value = %s\n", buffer);
        write(writePipe, buffer, strlen(buffer) + 1);
    }

    return 1;
}

/***************************************************************
main

Use: Instanciates all of the pipes and processes that are needed.
It then makes sure all of these processes close and terminate
correctly after they are completed.

Parameters: none

Returns: void
***************************************************************/
int main(){

    int pipeA[2];
    int pipeB[2];
    int pipeC[2];

    pid_t forkPID;

    //Testing pipes
    if (pipe(pipeA) == -1){
        fprintf(stderr, "%s", "The call to pipe() has failed.\n");
        exit(-5);
    }
    if (pipe(pipeB) == -1){
        fprintf(stderr, "%s", "The call to pipe() has failed.\n");
        exit(-5);
    }
    if (pipe(pipeC) == -1){
        fprintf(stderr, "%s", "The call to pipe() has failed.\n");
        exit(-5);
    }

    forkPID = fork();

    if(forkPID < 0){
        printf("An error occurred during fork#1\n");
        exit(-5);
    }

    if(forkPID != 0){//then we are parent
        close(pipeA[0]);
        close(pipeB[0]);
        close(pipeB[1]);
        close(pipeC[1]);
        Pwork(pipeA[1], pipeC[0]);

    }
    else{//it is the child

        forkPID = fork();

        if(forkPID < 0){
            printf("An error occured during fork#2\n");
            exit(-5);
        }

        if(forkPID != 0){ //if true then child process
            close(pipeA[1]);
            close(pipeB[0]);
            close(pipeC[0]);
            close(pipeC[1]);
            Cwork(pipeB[1], pipeA[0]);
        }
        else{
        // grandchild grandchild
            close(pipeA[0]);
            close(pipeA[1]);
            close(pipeB[1]);
            close(pipeC[0]);
            Gwork(pipeC[1], pipeB[0]);
            exit(0);
        }
        //child wating for grandchild
        exit(0);

    }

    //parent waiting for child to close
    exit(0);//parent closes


    return (0);


}

