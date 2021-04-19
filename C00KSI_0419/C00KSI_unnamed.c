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

     printf("%d: fd1: %d, fd2: %d\n",getpid(),pipefd[0],pipefd[1]);

     cpid = fork();
     if (cpid == -1) {
	   perror("fork");
	   exit(-1);
     }

     if (cpid == 0) {    
	  
	   close(pipefd[1]);    

	
	   while (read(pipefd[0], &buf, 1) > 0) {	
		write(STDOUT_FILENO, &buf, 1);

		write(STDOUT_FILENO, "\n", 1);
		close (pipifd[0]);
		_exit(EXIT_SUCCESS);	
	   }
	   

	   	

     } else {	
	

   	   close(pipefd[0]);    

	   strcpy(szoveg,"ez itt kerem egy szoveg\0");  
	   printf("%d: kuldom a szoveget: %s:%d\n",getpid(),szoveg,strlen(szoveg));

	   write(pipefd[1],argv[1], strlen(argv1));	

	   close(pipefd[1]);   

	   wait(NULL);    

	   exit(0);
     }
}
