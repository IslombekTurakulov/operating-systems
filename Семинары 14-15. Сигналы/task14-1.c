#include <signal.h>

int main(void) {
    (void) signal(SIGINT, SIG_IGN);
    (void) signal(SIGQUIT, SIG_IGN);

    // или сам while(1)
    do {

    } while (1);
    return 0;
}
