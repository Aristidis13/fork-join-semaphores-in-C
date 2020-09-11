#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef sem_t semaphore;

semaphore *synch1;
semaphore *synch2;

int main(int argc, char *argv[])
{
 int pid[5],i,sem_value1,sem_value2;

/*----------------------------------------Initializing Named Semaphores---------------------------------------------------*/
    synch1 = sem_open("sem1", O_CREAT | O_EXCL, 0644, 0);
    synch2 = sem_open("sem2", O_CREAT | O_EXCL, 0644, 0);
/*-----------------Semaphore name is sem1 and sem2 and they can be accessed by using this name----------------------------*/

    sem_getvalue(synch1,&sem_value1);
    sem_getvalue(synch2,&sem_value2);

//    printf("Number of sem1 value is %d\n",sem_value1);
//    printf("Number of sem2 value is %d\n",sem_value2);
 
/*-----------------------------------Creating 5 children to do some concurrent work----------------------------------------*/
    for (i=0; i<5; i++)
    {
        pid[i] = fork ();

        if (pid[i] == 0) 
	{
          break;
        }
    }

/*------------------------------------------------1st parallel child D1-----------------------------------------------------*/
   if (pid[0] == 0)
   {
    system("echo D1 ok");
//    printf("PID1=%d Parent's PID= %d \n",getpid(),getppid());
    sem_post(synch1);
   }

/*-----------------------------------------------Second parallel child D2---------------------------------------------------*/
   else if (pid[0]>0 && pid[1]==0)
   {
    system("echo D2 ok");
//    printf("PID2=%d Parent's PID=%d\n", getpid(),getppid());
    sem_post(synch1);
   }

/*-----------------------------------------------Third parallel child D3----------------------------------------------------*/
   else if (pid[0]>0 && pid[1]>0 && pid[2]==0)
   {
    system("echo D3 ok");
//    printf("PID3=%d Parent's PID=%d.\n",getpid(),getppid());
    sem_post(synch2);
   }

/*----------------------------------------------------Fourth child D4-------------------------------------------------------*/
   else if (pid[0]>0 && pid[1]>0 && pid[2]>0 && pid[3]==0)
   {
    sem_wait(synch1);
    sem_wait(synch1);
    system("echo D4 ok");
//    printf("PID4=%d Parent's PID=%d.\n",getpid(),getppid());
    sem_post(synch2);
   }

/*----------------------------------------------------Fifth child------------------------------------------------------------*/
   else if (pid[0]>0 && pid[1]>0 && pid[2]>0 && pid[3]>0 && pid[4]==0)
   {
    sem_wait(synch2);
    sem_wait(synch2);
    system("echo D5 ok");
//    printf("PID5=%d Parent's PID=%d.\n",getpid(),getppid());
   }

/*------------------------------------------------------Fork Error Condition--------------------------------------------------*/
   else if (pid[0]<0 || pid[1]<0 || pid[2]<0 || pid[3]<0 || pid[4]<0)
   {
    perror("Fork failed.\n");
    sem_unlink ("sem1");   
    sem_close(synch1);  
    sem_unlink ("sem2");   
    sem_close(synch2);  
    exit(1);
   }

/*---------------------------------------------------Waiting for childs to finish----------------------------------------------*/
  for(i=0;i<5;i++)
  {
   waitpid(-1,NULL,0);
  }
  sem_unlink("sem1");   
  sem_close(synch1);  
  sem_unlink("sem2");   
  sem_close(synch2);  
 return 0;
}
/*----------------------------------------------------------END----------------------------------------------------------*/
