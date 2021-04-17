#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void SzignalKez();

int main(){

    signal(SIGINT, SzignalKez);
    signal(SIGQUIT, SzignalKez);

    for (int i = 0; i < 10; i++){
        printf("Szignalra varok!\n");
        pause();
    }

    return 0;
}

void SzignalKez(int sig){
char tomb[60];

switch(sig){
    case 1: {
        strcpy(tomb, "megallitas\n");
        break;
	}

	case 2: {
        strcpy(tomb, "kilepo szignal\n");
        signal(SIGINT, SIG_DFL);
        printf("\nKilepes: ctrl +c!\n");
        break;
	}

	case 3: {
        strcpy(tomb, "kilepes\n");
        break;
	}

	case 4: {
        strcpy(tomb, "nem megfelelo szignal\n");
        break;
	}

	case 5: {
        strcpy(tomb, "trap szignál\n");
        break;
	}

	case 6: {
        strcpy(tomb, "visszavono szignal\n");
        break;
	}

        printf("\nA megfogott szignal neve: %s\n", tomb);
        }
}
