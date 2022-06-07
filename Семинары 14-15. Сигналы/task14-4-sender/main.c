#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int received = 1;

void waiting() {
    received = 1;
}

int main(void) {
    (void) signal(SIGUSR1, waiting);
    int recpid, number;
    printf("[Sender] PID -> %d\n", getpid());
    printf("[Sender] Enter interlocutor\'s PID -> ");
    scanf("%d", &recpid);
    printf("[Sender] Enter any number: ");
    scanf("%d", &number);
    for (int i = 0; i < 32; ++i) {
        if ((number & (1 << i)) == 0) {
            kill(recpid, SIGUSR1);
        } else {
            kill(recpid, SIGUSR2);
        }
        received = 0;
        while (i != 31 && received == 0);
    }
    printf("Number sent -> %d\n", number);
    return 0;
}