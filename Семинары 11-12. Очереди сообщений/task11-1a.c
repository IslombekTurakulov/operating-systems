#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define LAST_MESSAGE 255   // Message type

int main() {
    int msqid;
    char pathname[] = "11-1a.c";
    key_t key;
    int len;
    struct mymsgbuf {
        long mtype;
        struct {
            int sinfo;
            float finfo;
        } info;
    } mybuf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error from 11-1a.c - can't generate key\n");
        exit(-1);
    }
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Error from 11-1a.c - can't get msqid\n");
        exit(-1);
    }
    int i = 1;
    while (i <= 5) {
        mybuf.mtype = 1;
        mybuf.info.sinfo = 123;
        mybuf.info.finfo = 1.23;
        len = sizeof(mybuf.info);
        if (msgsnd(msqid, &mybuf, len, 0) < 0) {
            printf("Error from 11-1a.c - can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
        ++i;
    }
    mybuf.mtype = LAST_MESSAGE;
    len = 0;
    if (msgsnd(msqid, &mybuf, len, 0) < 0) {
        printf("Error from 11-1a.c - can't send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    return 0;
}