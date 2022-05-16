#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {
    int msqid;
    char pathname[] = "11-3-server.c";
    key_t key;
    int len, maxlen;
    // структура запроса клиента
    struct firstMessageBuffer {
        long mtype;
        struct {
            pid_t client_pid;
            double client_request;
        } request;
    } request_buf;

    // структура ответа сервера
    struct secondMessageBuffer {
        long mtype;
        struct {
            double server_response;
        } response;
    } response_buf;
    if ((key = ftok(pathname, 0)) < 0) {
        printf("ERROR [11-3-server.c] on generating key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("ERROR [11-3-server.c] on getting message ID\n");
        exit(-1);
    }

    while (1) {
        maxlen = sizeof(request_buf.request);
        if (len = msgrcv(msqid, (struct msgbuf *)&request_buf, maxlen, 1, 0) < 0) {
            printf("ERROR [11-3-server.c] on receiving message from queue\n");
            exit(-1);
        }

        response_buf.mtype = request_buf.request.client_pid;
        response_buf.response.server_response =
            request_buf.request.client_request * request_buf.request.client_request;
        len = sizeof(response_buf.response);

        if (msgsnd(msqid, (struct msgbuf *)&response_buf, len, 0) < 0) {
            printf("ERROR [11-3-server.c] on sending message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(-1);
        }
    }
    return 0;
}