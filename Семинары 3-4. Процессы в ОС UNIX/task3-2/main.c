#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t process_id = fork();
    if (process_id < 0) {
        printf("Failed to create a new process :( \n");
    } else if (process_id == 0) {
        printf("==== Process child ====\n");
        printf("ID of the current process = %d\n", getpid());
        printf("ID of the parent process = %d\n", getppid());
    } else {
        printf("==== Process parent ====\n");
        printf("ID of the current process = %d\n", getpid());
        printf("ID of the parent process = %d\n", getppid());
        printf("ID of the child process = %d\n", process_id);
    }
    return 0;
}