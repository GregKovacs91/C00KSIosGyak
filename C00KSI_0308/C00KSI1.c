#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
  
// Driver code 
int main(void) 
{ 
    char command[100];
    printf("Kerem adjon meg egy parancsot amit vizsgalni szeretne\n");
    scanf("%s",&command);
       system(command);
    
  
    int status; 
   
  
    WIFEXITED(status);
        int exit_status = WEXITSTATUS(status);         
        printf("Exit status of the child was %d\n",  
                                     exit_status); 
   
    return 0;
    
}
