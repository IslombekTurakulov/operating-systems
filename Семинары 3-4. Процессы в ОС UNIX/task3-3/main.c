#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    int i = 0;
    while (i < argc) {
        printf("{argv} %s\n", argv[i]);
        ++i;
    }
    i = 0;
    while (envp[i] != 0) {
        printf("{envp} %s\n", envp[i]);
        ++i;
    }
    return 0;
}