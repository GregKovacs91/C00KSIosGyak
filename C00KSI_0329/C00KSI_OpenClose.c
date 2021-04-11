#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int pipe, ret;
    char buf[50];

    buf[0] = 0;

    pipe = open("C00KSI.txt", O_RDWR);

    if (pipe != -1){
        printf("Sikeres Beolvasas\n");
    }
    else {
        printf("Sikertelen Beolvasas\n");
        exit(-1);
    }

    ret = read(pipe, buf, 50);
    printf("\nread() Eredmeny:\n- Byte-ok szama %d\n- tartalom: %s\n", ret, buf);

    ret = lseek(pipe, 0, SEEK_SET);
    printf("\nlseek() Eredmeny %d\n", ret);

    ret = write(pipe, buf, 6);
    printf("\nwrite() Eredmeny %d\n", ret);

    close(pipe);

    return 0;
}

