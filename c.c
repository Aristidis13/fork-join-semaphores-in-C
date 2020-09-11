#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
 int i,pid;
 i=0;
 do
 {
  pid=fork();
  if (pid > 0)
  {
   printf(" Father = %d, Id = %d, Child = %d\n", getppid(), getpid(), pid);
   wait(NULL);
   break;
  }
 i=i+1;
 } while (i<5);

 return 0;
}
