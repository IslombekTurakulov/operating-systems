#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    int shmid;
    char file_name[] = "task7-1r.c";
    key_t key;
    char *code;
    int file_size = 0;
    int *file_size_ptr;
    FILE *file = fopen(file_name, "r");
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    if ((key = ftok(file_name, 0)) < 0) {
        printf("Error on generating key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, sizeof(int) + file_size * sizeof(char), 0666 | IPC_CREAT)) < 0) {
        printf("Error on creating shared memory\n");
        exit(-1);
    }
    if ((file_size_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Error on attaching shared memory\n");
        exit(-1);
    }
    *file_size_ptr = file_size;
    code = (char*)(file_size_ptr + 1);
    for (int i = 0; i < file_size; i++) {
        code[i] = fgetc(file);
    }
    fclose(file);
    if (shmdt(file_size_ptr) < 0) {
        printf("Error on detaching shared memory\n");
        exit(-1);
    }
    return 0;
}