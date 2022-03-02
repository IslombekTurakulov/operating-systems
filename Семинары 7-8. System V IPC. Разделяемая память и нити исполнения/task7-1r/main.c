#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>


int main() {
    char file_name[] = "task7-1r.c";
    int shared_memory_id;
    int file_size = 0;
    int *file_size_ptr;
    key_t key;
    char *text;

    if ((key = ftok(file_name, 0)) < 0) {
        printf("Error on generating key\n");
        exit(-1);
    }

    if ((shared_memory_id = shmget(key, sizeof(int) + file_size * sizeof(char), 0)) < 0) {
        printf("Error on creating shared memory\n");
        exit(-1);
    }
    if ((file_size_ptr = (int *) shmat(shared_memory_id, NULL, 0)) == (int *) (-1)) {
        printf("Error on attaching shared memory\n");
        exit(-1);
    }
    file_size = *file_size_ptr;
    text = (char *) (file_size_ptr + 1);
    for (int i = 0; i < file_size; i++) {
        putchar(text[i]);
    }
    if (shmdt(file_size_ptr) < 0) {
        printf("Error on detaching shared memory\n");
        exit(-1);
    }

    if (shmctl(shared_memory_id, IPC_RMID, NULL) < 0) {
        printf("Error on deleting shared memory\n");
        exit(-1);
    }
    return 0;
}