#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum) {
    /* NOTE: Since a signal is asynchronous, we cannot predict when its handler
     *       ought to be called; a handler effectively has no caller, and thus
     *       it cannot take additional arguments or return any values. */

    if (signum == SIGINT) {
        printf("But MARIE lets their processes stay up on the CPU as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But LAURA lets their processes eat RAM before dinner!\n");
    }
    else {
        printf("Handling signal %d...\n", signum);
    }

    /* NOTE: The above is technically async-signal-unsafe; "printf" depends on
     *       the state of an internal buffer, which cannot be predicted at the
     *       time a signal occurs. */
}

int main(void) {
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* NOTE: This effectively ignores SIGINT (i.e., Ctrl+c) and SIGQUIT (i.e.,
     *       Ctrl+\)... */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* NOTE: ...but SIGSTOP (i.e., Ctrl+z) and SIGKILL -- not coincidentally,
     *       the two signals used to stop a fork bomb -- cannot be blocked,
     *       ignored, or otherwise handled. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    /* NOTE: Simply installing a signal handler does not necessarily mean that
     *       the signal will occur. In practice, we would presumably go off and
     *       do something else while waiting for a signal. */
    while (1);

    return EXIT_SUCCESS;
}
