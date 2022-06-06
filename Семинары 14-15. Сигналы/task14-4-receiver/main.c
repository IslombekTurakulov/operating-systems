#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sendpid, shift = 0, number = 0b10000000;

void get_zero();

void get_one();

int main(void) {
    (void) signal(SIGUSR1, get_zero);
    (void) signal(SIGUSR2, get_one);
    printf("[Interlocutor] My PID -> %d\n", getpid());
    printf("[Interlocutor] Enter sender\'s PID -> ");
    scanf("%d", &sendpid);
    while (1);
}

void get_one() {
    shift++;
    if (shift == 128) {
        printf("[Interlocutor] got number -> %d\n", number);
        exit(0);
    } else {
        printf("[Interlocutor] got %d bit: %d\n", shift, 1);
        kill(sendpid, SIGUSR1);
    }
}

void get_zero() {
    number = number ^ (1 << shift);
    shift++;
    if (shift == 128) {
        printf("[Interlocutor] got number -> %d\n", number);
        exit(0);
    } else {
        printf("[Interlocutor] got %d bit: %d\n", shift, 0);
        kill(sendpid, SIGUSR1);
    }
}
