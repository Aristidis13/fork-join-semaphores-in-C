#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int nothing(void)
{
 int x;
 x=0;
 x++;
}

int main()
{
 int i,p;
 pid_t child_pid,parent;
 time_t start,end;
 start = time(NULL);
 printf("Αρχική τιμή δευτερολέπτων %ld \n", start);
 i=0;
 printf("I,m the creator and my pid is %d \n",getpid());

 while (i<100)
 {
  child_pid=fork();
  if (child_pid==0)
  {
   nothing();
   printf("My pid is %d my father's is %d \n", getpid(),getppid() );
   exit(0);
  }
 i++;
 }
 for(p=0; p<100; p++)
 {
  waitpid(-1,NULL,0); //waitpid() == wait(NULL)
 }

 end = time(NULL);
 printf("Τελική τιμή δευτερολέπτων %ld \n", end); 
 printf("O μέσος όρος δευτερολέπτων είναι %f \n", (double)(end-start)/100);
 return 0;
}
