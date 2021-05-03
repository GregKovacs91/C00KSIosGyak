#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuff1 {
	long mtype;
	char mtext[512];
} sndbuff, *msgp;

struct msqid_ds ds, *buff;

int main()
{
	int msgid;
	key_t key;
	int msgflag;
	int rtn;
    int msgsz;

	key = MSGKEY;
	msgflag = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflag);

 	if ( msgid == -1) 
    {
        perror("msgget meghivasa sikertelenn\n");
         exit(-1);
    }


	msgp = &sndbuff;
	msgp->mtype = 1;
 	strcpy(msgp->mtext,"Kovacs Sandor Gergo, C00KSI");
	msgsz = strlen(msgp->mtext) + 1;
    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflag);

    if (msgp->mtext == "exit")
    {
        exit(0);
    }


	key_t kulcs;
	int tipus;
	int meret;

	kulcs = MSGKEY;
	msgflag = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflag);
 	if ( msgid == -1)
    {
        perror("msgget meghivasa sikertelen\n");
         exit(-1);
    }

	printf("uzenet kiirasa: %d\n",msgid);

	msgp = &sndbuff;
	buff = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buff);

	rtn = msgrcv(msgid,(struct msgbuff *)msgp, meret, tipus, msgflag);
	rtn = msgctl(msgid,IPC_STAT,buff);

    do{
        printf("valasszon az alabbiak kozul\n");
        printf("nyomja meg a 0 ha az uzenetek szamara kivancsi\n");
        printf("nyomja meg az 1 ha az elso uzenet kiolvasasa erdekli\n");
        printf("nyomja meg a 2 ha az uzenetsor megszunteteset szeretne\n");
        printf("nyomja meg a 3 ha ki szeretne lepni\n");
        scanf("%d", &msgid);
    }while(msgid < 0 || msgid > 3);

  switch(msgid)
  {
    case 0:
        printf("uzenetek mennyisege:  %ld\n",buff->msg_qnum);
        break;

    case 1:
        printf("Az uzenet:  %s\n", msgp->mtext);
        break;

    case 2:
        rtn = msgctl(msgid, IPC_RMID, NULL);
        printf("kilepes \n");
        break;

    case 3:
        exit(0);
  }
}
