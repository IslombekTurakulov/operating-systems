// Возможно это не обязательная задача, но в примере 03-2.c было про это
// и я подумал, что это тоже надо, хотя в вики только две задачи.
// Заранее прошу прощения.
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t process_id = fork();
    if (process_id < 0) {
        printf("Failed to create a new process :( \n");
        exit(-1);
    } else if (process_id == 0) {
        printf("==== Process child ====\n");
        (void) execle("/bin/cat", "/bin/cat", "task3-2.c", 0, envp);
        printf("Failed to create a new process :( \n");
        exit(-1);
    } else {
        printf("==== Process parent ====\n");
    }
    return 0;
}