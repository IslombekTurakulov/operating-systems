#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    int message_id;
    char pathname[] = "11-3-server.c";
    key_t key;
    int len, maxlen;
    double input;
    scanf("%lf", &input);

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
        printf("ERROR [11-3-client.c] on generating key\n");
        exit(-1);
    }
    if ((message_id = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("ERROR [11-3-client.c] on getting message ID\n");
        exit(-1);
    }
    request_buf.mtype = 1;
    request_buf.request.client_pid = getpid();
    request_buf.request.client_request = input;
    len = sizeof(request_buf.request);
    if (msgsnd(message_id, (struct msgbuf *)&request_buf, len, 0) < 0) {
        printf("ERROR [11-3-client.c] on sending message to queue\n");
        msgctl(message_id, IPC_RMID, (struct msqid_ds *)NULL);
        exit(-1);
    }
    maxlen = sizeof(response_buf.response);
    if (len = msgrcv(message_id, (struct msgbuf *)&response_buf, maxlen, getpid(), 0) < 0) {
        printf("ERROR [11-3-client.c] on receiving message from queue\n");
        exit(-1);
    }
    printf("SUCCESS [11-3-client.c] message type = %d request = %lf response = %lf\n",
           request_buf.request.client_pid, request_buf.request.client_request,
           response_buf.response.server_response);
    return 0;
}