#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
     int pipefd[2];	
     pid_t cpid;	
     char buf;		
     char szoveg[32];	
     int ret;

     if (pipe(pipefd) == -1) {	
	   perror("pipe");
	   exit(-1);
     }

     

     cpid = fork();
     if (cpid == -1) {
	   perror("fork");
	   exit(-1);
     }

     if (cpid == 0) {    
	   
	   close(pipefd[1]);    

	   strcpy(szoveg,"Kovacs Sandor Gergo C00KSI\0");   
	   printf("kuldom a szoveget: \n%s\n",szoveg);

	   write(pipefd[1], szoveg, strlen(szoveg));	

	   close(pipefd[0]); 

   	   exit(0);

     } else {	
	  

   	   close(pipefd[0]);    

	   printf(" megnezem mi van a csoben\n ");
	   while (read(pipefd[0], &buf, 1) > 0) {
		 printf("\n%c",buf);
	   }
	  

	   close(pipefd[1]);	

	   wait(NULL);   

	   exit(0);
     }
}
