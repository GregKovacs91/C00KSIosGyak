#include <stdio.h>
#include <stdlib.h>

int main(){
char command[100];

printf("Kerem adjon meg egy parancsot\n");
scanf("%s",&command);
system(command);
return 0;
}
