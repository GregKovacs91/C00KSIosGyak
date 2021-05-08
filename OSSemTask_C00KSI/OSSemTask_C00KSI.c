#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<unistd.h>
int pipefd[2];
void handler(){
	char szoveg[32];
	strcpy(szoveg,"Kovacs Sandor Gergo, C00KSI\0");   // feltoltom a buffert a kuldeni kivant szoveggel
	  write(pipefd[1], szoveg, strlen(szoveg));
}

int main() {
     	// tomb eleme 2 lesz, mivel ket vege van a csonek, ezert csak ket valtozo kell neki
     pid_t cpid;	// gyerek pidje itt lesz tarolva
     char buf;		// ide jon a buffer
     	// masik buffer a kuldendo szovegnek
     int ret;

     if (pipe(pipefd) == -1) {	// itt keszitjuk el a csovezeteket, es a ket csoveg a pipefd-ben lesz tarolva
	   perror("pipe");
	   exit(-1);
     }

     

     cpid = fork();		//felveszi a gyerek pidjet
     if (cpid == -1) {
	   perror("fork");	//hiba eseten kilep
	   exit(-1);
     }

     if (cpid == 0) {    // itt kezdodik a gyerek processz 
	   printf("%d: gyerek vagyok\n",getpid());
	  close(pipefd[0]);    // itt az olvaso veget csukjuk le a csonek, mert csak irni fogunk bele

	   signal(SIGALRM, (void (*)()) handler);	//szignal beiktatas
	pause();
	   close(pipefd[1]);    // lecsukom a csatorna fedelet

   	   exit(0);	// kilep a gyerekbol

     } else {	// itt kezdodik a szulo processz 
	   printf("%d: szulo vagyok\n",getpid());
		close(pipefd[1]);    // az irasi veget lezarjuk a csonek 
   	   while (read(pipefd[0], &buf, 1) > 0) {	//1 byteonkent olvasunk a cso kimeneterol
		 printf("%c",buf);
	   }
	   printf("\n%d:lezartak a cso masik oldalat\n",getpid());

	   close(pipefd[0]);	//bezarjuk az olvaso veget

	   wait(NULL);    // megvarjuk a gyerek processzt 

	   exit(0);  
     }
	
}
