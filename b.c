#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
 int i,pid;
 for (i=0;i<4;i++)
 {
  pid=fork();
  if (pid==0)
  {
   printf("I'm child with pid %d and father %d\n",getpid(),getppid());
   break;
  }
  else if (pid<0)
  {
   perror("Fork failed.\n");
  }
  else if(pid>0)
  {
   waitpid(-1,NULL,0);
  }
 }
return 0;
}
