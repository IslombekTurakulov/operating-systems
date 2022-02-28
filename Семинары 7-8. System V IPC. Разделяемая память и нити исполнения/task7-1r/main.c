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
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Error on generating key\n");
        exit(-1);
    }
    if ((shared_memory_id = shmget(key, (2000 * sizeof(char)), 0666 | IPC_CREAT)) < 0) {
        printf("Error on finding shared memory\n");
        exit(-1);
    }
    if ((buffer = (char *) shmat(shared_memory_id, NULL, 0)) == (char *) (-1)) {
        printf("Error on attaching shared memory\n");
    }
    int current = 0;
    while (buffer[current] != '\0') {
        printf("%c", buffer[current]);
        ++current;
    }
    if (shmdt(buffer) < 0) {
        printf("Error on detaching shared memory\n");
        exit(-1);
    }
    if (shmctl(shared_memory_id, 0, NULL) < 0) {
        printf("Error on free shared memory\n");
        exit(-1);
    }
    return 0;
}