#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t first_size;
    size_t second_size;
    int result;
    int first_fd[2];
    int second_fd[2];
    char first_arr[27];
    char second_arr[26];
    if (pipe(first_fd) < 0) {
        printf("Can\'t open first pipe\n");
        exit(-1);
    }
    if (pipe(second_fd) < 0) {
        printf("Can\'t open second pipe\n");
        exit(-1);
    }
    result = fork();
    if (result >= 0) {
        if (result > 0) {
            /* Parent process */
            if (close(first_fd[0]) < 0) {
                printf("Parent -> Can\'t close reading side of first pipe\n");
                exit(-1);
            }
            first_size = write(first_fd[1], "Hello, world, from parent!", 27);
            if (first_size != 27) {
                printf("Can\'t write all string to first pipe\n");
                exit(-1);
            }
            if (close(first_fd[1]) < 0) {
                printf("Parent -> Can\'t close writing side of first pipe\n");
                exit(-1);
            }

            if (close(second_fd[1]) < 0) {
                printf("Parent -> Can\'t close writing side of second pipe\n");
                exit(-1);
            }
            second_size = read(second_fd[0], second_arr, 26);
            if (second_size < 0) {
                printf("Can\'t read string from second pipe\n");
                exit(-1);
            }
            printf("Parent got:  %s\n", second_arr);
            if (close(second_fd[0]) < 0) {
                printf("Parent -> Can\'t close reading side of first pipe\n");
                exit(-1);
            }
        } else {
            /* Child process */
            if (close(first_fd[1]) < 0) {
                printf("Child -> Can\'t close writing side of first pipe\n");
                exit(-1);
            }
            first_size = read(first_fd[0], first_arr, 27);
            if (first_size < 0) {
                printf("Can\'t read string from first pipe\n");
                exit(-1);
            }
            printf("Child value ->  %s\n", first_arr);
            if (close(first_fd[0]) < 0) {
                printf("Child -> Can\'t close reading side of first pipe\n");
                exit(-1);
            }
            if (close(second_fd[0]) < 0) {
                printf("Child -> Can\'t close reading side of second pipe\n");
                exit(-1);
            }
            second_size = write(second_fd[1], "Hello, world, from child!", 26);
            if (second_size != 26) {
                printf("Can\'t write all string to second pipe\n");
                exit(-1);
            }
            if (close(second_fd[1]) < 0) {
                printf("Child -> Can\'t close writing side of second pipe\n");
                exit(-1);
            }
        }
    } else {
        printf("Can\'t fork child\n");
        exit(-1);
    }
    return 0;
}