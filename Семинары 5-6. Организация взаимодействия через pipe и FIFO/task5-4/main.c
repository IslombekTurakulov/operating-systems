#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int writeToFile();

int readFromFile();

int main() {
    int result = writeToFile();
    if (result == -1) {
        exit(-1);
    }
    int status = readFromFile();
    if (status == -1) {
        exit(-1);
    }
    return 0;
}

int readFromFile() {
    int fd;
    size_t size;
    char resstring[14];
    char name[] = "aaa.fifo";
    printf("Reading file start\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Oopss... Can\'t open FIFO for reading\n");
        return -1;
    }

    size = read(fd, resstring, 14);

    if (size < 0) {
        printf("Oopss... Can\'t read text from FIFO\n");
        return -1;
    }
    printf("Value: %s\n", resstring);
    printf("Reading program exit");

    if (close(fd) < 0) {
        printf("Oopss... Can\'t close FIFO\n");
        return -1;
    }
    return 0;
}

int writeToFile() {
    int fd;
    size_t size;
    char name[] = "aaa.fifo";
    printf("Writing file start\n");
    (void) umask(0);
    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Oopss... Can\'t create FIFO\n");
        return -1;
    }

    if ((fd = open(name, O_WRONLY)) < 0) {
        printf("Oopss... Can\'t open FIFO for writing\n");
        return -1;
    }

    size = write(fd, "Hello, world!", 14);

    if (size != 14) {
        printf("Oopss... Can\'t write text to FIFO\n");
        return -1;
    }

    if (close(fd) < 0) {
        printf("Oopss... Can\'t close FIFO\n");
        return -1;
    }

    printf("Writing file exit\n");
    return 0;
}
