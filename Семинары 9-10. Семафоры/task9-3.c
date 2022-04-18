// A(S, n) - увеличить значение семафора S на величину n > 0;
// D(S, n) - пока значение семафора S < n (n должно быть больше 0), процесс блокируется.
// Далее S = S - n;
// Z(S) - процесс блокируется до тех пор, пока значение семафора S не станет равным 0.
// Для родителя
// write()
// Add(S, 2)
// Zero
// read()
// Для ребёнка
// Decrease(S, 1) -> S = 2 - 1
// read()
// write()
// Decrease(S, 1) -> S = 1 - 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd[2], result;
    int curr_id, N;
    size_t size;
    char data[16];
    char path[] = "task9-3.c";
    struct sembuf mybuf;
    key_t key;
    scanf("%d", &N);
    if (pipe(fd) < 0) {
        printf("[Error 9-3.c] can\'t open pipe!\n");
        exit(-1);
    }
    if ((key = ftok(path, 0)) < 0) {
        printf("[Error 9-3.c] can\'t generate key!\n");
        exit(-1);
    }
    if ((curr_id = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("[Error 9-3.c] can\'t get semaphore!\n");
        exit(-1);
    }
    result = fork();
    if (result < 0) {
        printf("[Error 9-3.c] can\'t fork child!\n");
        exit(-1);
    }
    for (int iteration = 0; iteration < N; ++iteration) {
        if (result > 0) {
            // Parent
            size = write(fd[1], "Hi from parent!", 16);
            if (size != 16) {
                printf("[Error 9-3.c from parent] can\'t write all values to pipe\n");
                exit(-1);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = 2;
            mybuf.sem_flg = 0;
            if (semop(curr_id, &mybuf, 1) < 0) {
                printf("[Error 9-3.c from parent] can\'t wait for condition\n");
                exit(-1);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = 0;
            mybuf.sem_flg = 0;
            if (semop(curr_id, &mybuf, 1) < 0) {
                printf("[Error 9-3.c from parent] can\'t wait for condition\n");
                exit(-1);
            }
            size = read(fd[0], data, 16);
            if (size != 16) {
                printf("[Error 9-3.c from parent] can\'t read values from pipe\n");
                exit(-1);
            }
            printf("[Success from parent %d] got value from pipe: %s\n", iteration, data);
        } else {
            // Child
            mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(curr_id, &mybuf, 1) < 0) {
                printf("[Error 9-3.c from parent] can\'t wait for condition!\n");
                exit(-1);
            }
            size = read(fd[0], data, 16);
            if (size != 16) {
                printf("[Error 9-3.c from child] can\'t read values from pipe!\n");
                exit(-1);
            }
            printf("[Success from child %d] gol value from pipe: %s\n", iteration, data);
            size = write(fd[1], "Hi from chiild!", 16);
            if (size != 16) {
                printf("[Error 9-3.c from child] can\'t write all values to pipe!\n");
                exit(-1);
            }
            mybuf.sem_num = 0;
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            if (semop(curr_id, &mybuf, 1) < 0) {
                printf("[Error 9-3.c from parent] can\'t wait for condition\n!");
                exit(-1);
            }
        }
    }
    if (close(fd[0]) < 0) {
        printf("[Error 9-3.c from parent] can\'t close pipe side which is reading values!\n");
        exit(-1);
    }
    if (close(fd[1]) < 0) {
        printf("[Error 9-3.c from parent] can\'t close pipe side which is writing value!\n");
        exit(-1);
    }
    return 0;
}