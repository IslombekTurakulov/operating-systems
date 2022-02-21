#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd[2];
    // 0 - false, there is a space in the pipe, 1 - true
    int has_space = 0;
    int result = 0;
    if (pipe2(fd, O_NONBLOCK) < 0) {
        printf("Oopss... Can\'t open pipe. Try again!\n");
        exit(-1);
    }
    while (!has_space) {
        write(fd[1], "p", 1) > 0 ? ++result : (has_space = 1);
    }
    printf("Value: %d\n", result);
    // Мой OUTPUT: "Value: 65536"
    if (close(fd[0]) < 0) {
        printf("Error of closing reading side of pipe\n");
        exit(-1);
    }
    if (close(fd[1]) < 0) {
        printf("Error of closing writing side of  pipe\n");
        exit(-1);
    }
    return 0;
}