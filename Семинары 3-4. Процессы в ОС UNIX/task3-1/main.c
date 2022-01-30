#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("ID of the current process = %d\n", getpid());
    printf("ID of the parent process = %d\n", getppid());
    return 0;
}