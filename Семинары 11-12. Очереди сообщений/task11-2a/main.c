#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main() {
    int msqid;
    char pathname[] = "11-2a.c";
    key_t key;
    int len, maxlen;
    struct mymsgbuf {
        long mtype;
        struct {
            int sinfo;
        } info;
    } mybuf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error from 11-2a.c - can't generate key\n");
        exit(-1);
    }
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Error from 11-2a.c - can't get msqid\n");
        exit(-1);
    }
    for (int i = 1; i <= 5; ++i) {
        mybuf.mtype = 1;
        mybuf.info.sinfo = 123;
        len = sizeof(mybuf.info);
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Error from 11-2a.c - can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    int i = 1;
    while (i <= 5) {
        maxlen = sizeof(mybuf.info);
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) < 0) {
            printf("Error from 11-2a.c - can't receive message from queue\n");
            exit(-1);
        }
        printf("Success from 11-2a.c - message type = %ld, sinfo = %i\n", mybuf.mtype, mybuf.info.sinfo);
        ++i;
    }
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    return 0;
}