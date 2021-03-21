#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pwd.h>

int main()
{
    pid_t wait(int *wstatus);
    pid_t waitpid(pid_t pid, int *wstatus, int options);
    pid_t pid = fork();
    if (pid==0)
        {
            execl("/bin/pwd","NULL");
        }
    int status;  
    waitpid(pid, &status, 0);
    printf("child process executed");
}
