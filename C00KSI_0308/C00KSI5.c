#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pwd.h>

int main()
{
    pid_t pid = fork();
    int status;
    printf("%d",pid);
    if(pid <0)
    {
        perror("Fork hiba");
    }
    if(pid==0)
    {
       exit(7);
    }
    if(wait(&status)!=pid)
    {
        perror("Wait hiba");
    }
    if(WIFEXITED(status))
    {
        printf("Normális befejeződés, visszaadott érték =%d\n", WEXITSTATUS(status));
    }
   
}

void abort(void);
void exit(int status);
