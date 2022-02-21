#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
      int fd;
    size_t size;
    char name[] = "aaa.fifo";
    /*
     *  Во время запуска
     *  Writing file start
     */
    printf("Writing file start\n");
    /*
     * После запуска программы для чтения
     * Writing file exit
     */
    (void) umask(0);
    if (mkfifo(name, __S_IFIFO | 0666) < 0) {
        printf("Oopss... Can\'t create FIFO\n");
        exit(-1);
    }

    if ((fd = open(name, O_WRONLY)) < 0) {
        printf("Oopss... Can\'t open FIFO for writing\n");
        exit(-1);
    }

    size = write(fd, "Hello, world!", 14);

    if (size != 14) {
        printf("Oopss... Can\'t write text to FIFO\n");
        exit(-1);
    }

    if (close(fd) < 0) {
        printf("Oopss... Can\'t close FIFO\n");
        exit(-1);
    }

    printf("Writing file exit\n");
    return 0;
}
