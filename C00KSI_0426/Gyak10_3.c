#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

int main() {
    int child = 0;

    if ((child = fork()) == 0) {
        int shmid;
        key_t key;
        int size=512;
        int shmflag;

        key = SHMKEY;
        shmflag = 0;
        if ((shmid=shmget( key, size, shmflag)) < 0) 
        {
            printf("Szegmens letrehozas\n");
            shmflag = 00666 | IPC_CREAT;
            if ((shmid=shmget( key, size, shmflag)) < 0) 
            {
                perror("shmget meghivasa sikertelen\n");
                exit(-1);
            }
        } 
        else 
        {
            printf("a szegmens mar letrejott\n");
        }

        printf("shmid azonosito: %d:\n", shmid);

        exit (0);
    }

    else
    {
        if (child = fork() == 0) {
            int shmid;
            key_t key;
            int size=512;
            int shmflag;
            struct vmi {
                int  hossz;
                char szoveg[512-sizeof(int)];
            } *segm;
            
            key = SHMKEY;
            shmflag = 0;
            if ((shmid=shmget( key, size, shmflag)) < 0) 
            {
                perror("shmget meghivasa sikertelen\n");
                exit(-1);
            }

            shmflag = 00666 | SHM_RND;
            segm = (struct vmi *)shmat(shmid, NULL, shmflag);
            if (segm == (void *)-1) {
                perror("a csatolas nemtortent meg\n");
                exit (-1);
            }

            if (strlen(segm->szoveg) > 0)
            {
                printf("elozo sor szoveg. %s (%d hosszon)\n",segm->szoveg,segm->hossz);
            } 
        
            printf("adjon meg uj szoveget\n");
            gets(segm->szoveg);
            printf("uj szoveg %s\n",segm->szoveg);
            segm->hossz=strlen(segm->szoveg);
                
            shmdt(segm);

            exit(0);
        }

        else 
        {
            int shmid;
            key_t key;
            int size=512;
            int shmflag;
            int rtn;
            int cmd;
            struct shmid_ds shmid_ds, *buf;
            buf = &shmid_ds;

            key = SHMKEY;
            shmflag = 0;
            if ((shmid=shmget( key, size, shmflag)) < 0) 
            {
                perror("shmget meghivasa sikertelen\n");
                exit(-1);
            }

        do {
            printf("adjon meg egy parancsot\n");
            printf("0 IPC_STAT (status)\n");
            printf("1 IPC_RMID (torol)\n");
            scanf("%d",&cmd);
            } while (cmd < 0 && cmd > 1);

            switch (cmd)
            {
            case 0: rtn = shmctl(shmid, IPC_STAT, buf);
                printf("A szegmens mérete %ld\n",buf->shm_segsz);
                printf("PID %d\n ",buf->shm_lpid);
                break;
            case 1: rtn = shmctl(shmid, IPC_RMID, NULL);
                printf("szegmens letorolve\n");
            }
            
            exit(0);
        }
    }
}
