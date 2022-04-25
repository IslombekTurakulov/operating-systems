#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define LAST_MESSAGE 255

int main() {
    int msqid;
    char pathname[] = "11-1a.c";
    key_t key;
    int len, maxlen;
    struct mymsgbuf {
        long mtype;
        struct {
            int sinfo;
            float finfo;
        } info;
    } mybuf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error from 11-1b.c can't generate key\n");
        exit(-1);
    }
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Error from 11-1b.c can't get msqid\n");
        exit(-1);
    }
    // while(true)
    while (1) {
        maxlen = sizeof(mybuf.info);
        if (len = msgrcv(msqid, &mybuf, maxlen, 0, 0) < 0) {
            printf("Error from 11-1b.c can't receive message from queue\n");
            exit(-1);
        }
        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, NULL);
            exit(0);
        }
        printf("Success from 11-1b.c message type = %ld, sinfo = %i, finfo = %f\n", mybuf.mtype, mybuf.info.sinfo, mybuf.info.finfo);
    }
    return 0;
}