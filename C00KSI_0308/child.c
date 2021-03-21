#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
int main()
{
    for(int i =0;i<5;i++)
    {
        printf("Kovacs Gergo - C00KSI\n");
        unsigned int microsecond = 1000000;
        usleep(1 * microsecond);
    }
    
    return 0;
}