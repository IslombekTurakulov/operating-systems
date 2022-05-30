#include <signal.h>
#include <stdio.h>

void my_handler(int n_sig) {
    if (n_sig == 2) {
        printf("Signal %d and ctrl-c pressed\n", n_sig);
    } else if (n_sig == 3) {
        printf("Signal %d and ctrl-4 pressed\n", n_sig);
    }
}

int main(void) {
    (void) signal(SIGINT, my_handler);
    (void) signal(SIGQUIT, my_handler);

    // или сам while(1)
    do {

    } while (1);
    return 0;
}