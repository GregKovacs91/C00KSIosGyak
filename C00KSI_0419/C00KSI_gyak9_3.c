#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

void  SIGINT_handler(int);   
void  SIGQUIT_handler(int); 

int   ShmID;      
pid_t *ShmPTR;    

void main(void)
{
     int   i;
     pid_t pid = getpid();
     key_t MyKey;

     if (signal(SIGINT, SIGINT_handler) == SIG_ERR) {
          printf("SIGINT hiba\n");
          exit(1);
     }
     if (signal(SIGQUIT, SIGQUIT_handler) == SIG_ERR) {
          printf("SIGQUIT hiba\n");
          exit(2);
     }

     MyKey   = ftok(".", 's');    
     ShmID   = shmget(MyKey, sizeof(pid_t), IPC_CREAT | 0666);
     ShmPTR  = (pid_t *) shmat(ShmID, NULL, 0);
     *ShmPTR = pid;               

     for (i = 0; ; i++) {        
          printf("process: C00KSI, %d\n",pid);
          pause();
     }
}

void  SIGINT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("SIGINT: volt egy %d (SIGINT ^C) szignal\n", sig);
     signal(sig, SIGINT_handler);
}

void  SIGQUIT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("SIGQUIT: volt egy %d (SIGQUIT ^\\) szignal"
                          " es kilep\n", sig);
     shmdt(ShmPTR);
     shmctl(ShmID, IPC_RMID, NULL);

     exit(3);
}
