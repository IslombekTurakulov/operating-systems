#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    size_t size;
    char resstring[14];
    char name[] = "aaa.fifo";
    /*
     * Reading file start
     * Value: Hello, world!
     * Reading file exit
     */
    printf("Reading file start\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Oopss... Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = read(fd, resstring, 14);

    if (size < 0) {
        printf("Oopss... Can\'t read text from FIFO\n");
        exit(-1);
    }
    printf("Value: %s\n", resstring);
    printf("Reading file exit\n");

    if (close(fd) < 0) {
        printf("Oopss... Can\'t close FIFO\n");
        exit(-1);
    }
    return 0;
}
