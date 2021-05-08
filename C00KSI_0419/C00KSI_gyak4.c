#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void myhandle (int mysignal)
{
	printf("handle szignallal %d\n", mysignal);

	signal (SIGTERM, myhandle);
}


int main(int argc, char *argv[]){
	int i=10;
	signal(SIGTERM, myhandle);

	printf("a proccess piddje: %d\n",getpid());

	while(1)
	{
		printf("i = %d\n", i);
		sleep(3);
	}
	
	return 0;
}
