#include <unistd.h>
#include <stdio.h>

int main() {
    printf("User id = %d\n", getuid());
    printf("Group io = %d\n", getgid());
    return 0;
}
