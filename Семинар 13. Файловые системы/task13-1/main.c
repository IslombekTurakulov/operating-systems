#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd, counter = 0;
    char path_name[1024] = "a.txt";
    char prev_name[1024] = "a.txt";
    char new_name[1024] = "a0";
    char file_name[1024];
    if ((fd = open(path_name, O_CREAT | O_EXCL, 0666)) < 0) {
        printf("ERROR [task13-1] while creating a file");
        exit(-1);
    }
    while ((fd = open(file_name, O_RDONLY, 0666)) >= 0) {
        char buffer[4];
        strcpy(file_name, new_name);
        if (symlink(prev_name, file_name) >= 0) {
            size_t destination_size = sizeof(new_name);
            strncpy(prev_name, new_name, destination_size);
            prev_name[destination_size - 1] = '\0';
            strcpy(new_name, "a");
            ++counter;
            sprintf(buffer, "%d", counter);
            strcat(new_name, buffer);
            new_name[sizeof(new_name) - 1] = '\0';
            if (close(fd) < 0) {
                exit(-1);
            }
        } else {
            printf("ERROR [task13-1] while creating a link\n");
            exit(-1);
        }
    }
    printf("Total depth is %d\n", counter);
    return 0;
}
