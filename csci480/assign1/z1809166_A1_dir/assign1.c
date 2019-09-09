/*********************************************************
CSCI 480 - ASSIGNMENT 1 - SPRING 2019

PROGRAMMER: ALEX DANILUSHKIN
Z-ID: Z1809166
SECTION: 1
TA: JOSHUA BOLEY
DUE DATE: JANUARY 25TH, 2019

PURPOSE: THE PURPOSE OF THIS ASSIGNMENT IS TO GET
EXPOSED TO FORK, PID's, AND OTHER LINUX SYSTEM PROCESSES
*********************************************************/

#include <sys/types.h>		/* needed to use pid_t, etc. */
#include <sys/wait.h>		/* needed to use wait() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		/* LINUX constants and functions (fork(), etc.) */

int
main ()
{
  pid_t pid;//Used to check fork

  printf("\n\nI am the Original process. My PID is %d and my parents is %d", getpid(), getppid());
  printf("I will now call fork\n\n");//Calling fork
  pid = fork ();

  //ERROR CHECK
  if (pid < 0)
    {
      printf ("A fork error has occurred.\n");
      exit (-1);
    }


/*NOW RUNNING CHILD*/
  if (pid == 0)// if our PID is 0, we are running the child process
    {
      printf ("I am the child. my PID is %d and my parent's is %d", getpid(), getppid());
      printf("I am about to call fork\n\n"); //forking to grandchild
      pid_t childPID;
      childPID = fork();

      //ERROR CHECK
      if(childPID < 0)
        {
        printf ("A fork error has occurred.\n");
        exit (-1);
        }
      /*NOW RUNNING GRANDCHILD */
      if(childPID == 0){
          printf ("I am the grandchild.\n");
          printf("My PID is %d, and my parents is %d\n", getpid(), getppid());
          printf("Grandchild will now end\n\n");
          exit(0);
      }
      /*ELSE RETURN TO CHILD*/
      else{
          wait(0);//wait till it's child(overall the grandchild) ends
          printf("I am the child.\n");
          printf("My PID is %d, and my parent is %d\n", getpid(), getppid());
          printf("Child will now end\n\n");
          exit(0);
      }
    }
/*RETURN TO PARENT PROCESS */
  else //if not any other process, then we are the parent
    {
      wait (0);// Wait for the child to terminate.
      printf("I am the Original. My PID is %d\n", getpid());
      printf("My parent's PID is %d\n", getppid());
      sleep(2);
      printf("I will now call ps command\n");
      system("ps");
      printf ("I am the Original process. I will now exit.\n");
      exit (0);
    }

  return (0);
}

