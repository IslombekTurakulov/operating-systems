#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void handler(int n_sig) {
    int status;
    pid_t pid;
    pid = waitpid(-1, &status, WNOHANG);
    do {
        if (pid != 0) {
            if (pid >= 0) {
                if ((status & 0xff) == 0) {
                    printf("%d was closed with status %d\n", pid, status >> 8);
                } else if ((status & 0xff00) == 0) {
                    if (status & 0x80) {
                        printf("%d was killed by signal %d %s\n", pid, status & 0x7f,
                               "with core file");
                    } else {
                        printf("%d was killed by signal %d %s\n", pid, status & 0x7f,
                               "without core file");
                    }
                }
                pid = waitpid(-1, &status, WNOHANG);
            } else {
                errno == 10 ? printf("Empty list of processes to close\n") : printf("Error waitpid errno = %d\n", errno);
                return;
            }
        } else {
            break;
        }
    } while (pid != 0);
}

int main(void) {
    pid_t pid;
    int i, j;
    (void) signal(SIGCHLD, handler);
    for (i = 0; i < 10; i++) {
        if ((pid = fork()) >= 0) {
            if (pid == 0) {
                j = 1;
                while (++j < 10000000) {
                }
                exit(200 + i);
            }
        } else {
            printf("Fork child 1 handled in error\n");
            exit(1);
        }
    }
    // или сам while(1)
    do {

    } while (1);
    return 0;
}
