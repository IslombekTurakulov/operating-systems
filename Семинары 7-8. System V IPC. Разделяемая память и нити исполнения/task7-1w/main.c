#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
    int shared_memory_id;
    key_t key;
    char *buffer;
    char pathname[] = "07-1a.c";
    FILE *file = fopen("test.txt", "r");
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error on generating key\n");
        exit(-1);
    }
    if ((shared_memory_id = shmget(key, (2000 * sizeof(char)), 0666 | IPC_CREAT)) < 0) {
        printf("Error on creating shared memory\n");
        exit(-1);
    }
    if ((buffer = (char *) shmat(shared_memory_id, NULL, 0)) == (char *) (-1)) {
        printf("Error on attaching shared memory\n");
        exit(-1);
    }
    int current = 0;
    while (!feof(file) & (current < 1999)) {
        buffer[current] = fgetc(file);
        ++current;
    }
    printf("Write completed\n");
    if (shmdt(buffer) < 0) {
        printf("Error on detaching shared memory\n");
        exit(-1);
    }
    fclose(file);
    return 0;
}