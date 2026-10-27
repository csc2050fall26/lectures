#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum) {
    /* NOTE: Since we cannot predict when a signal will occur, we also cannot
     *       predict when to call its handler; a handler effectively has no
     *       caller; it cannot take additional arguments or return values. */

    if (signum == SIGINT) {
        printf("But SOPHIA lets their processes stay up on the CPU as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But MASON lets their processes eat RAM before dinner!\n");
    }
    else {
        printf("Handling signal %d...\n", signum);
    }

    /* NOTE: The above is technically unsafe, since "printf" depends on the
     *       state of an internal buffer, whose contents cannot be predicted
     *       at the moment a signal occurs. */
}

int main(void) {
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* NOTE: This effectively ignores SIGINT (Ctrl+c) and SIGQUIT (Ctrl+\), but
     *       SIGSTOP (Ctrl+z) and SIGKILL -- not coincidentally, the signals
     *       used to stop a fork bomb -- cannot be blocked or handled. */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    /* NOTE: Installing a handler does not necessarily mean the signal will
     *       occur; in practice, we ought to go off and do something useful
     *       here, but we need to do something while waiting... */
    while (1);

    return EXIT_SUCCESS;
}
