#include <unistd.h>
#include <signal.h>



main ()
{
int i;
	unsigned sec=1;

	signal(SIGINT, do_int);

	signal(SIGALRM, do_nothing);
	printf(" \n");
	pause();
    	printf("   \n");
}	
void do_nothing(){ ;}
