#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum) {
    /* NOTE: Since we cannot predict when an asynchronous signal will occur, we
     *       also cannot predict when to call its handler, which effectively
     *       has no caller; it can't take more arguments or return values... */

    if (signum == SIGINT) {
        printf("But SOPHIA lets their processes stay up on the CPU as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But MASON lets their processes eat RAM before dinner!\n");
    }
    else {
        printf("Handling signal %d...\n", signum);
    }

    /* NOTE: ...it also shouldn't call async-signal-unsafe functions such as
     *       "printf", which depend on the state of memory whose contents
     *       cannot be predicted at the time the signal occurs. */
}

int main(void) {
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* NOTE: There are legitimate reasons for effectively ignoring SIGINT
     *       (i.e., Ctrl+c) and SIGQUIT (i.e., Ctrl+\), for example, to ensure
     *       that any open files are correctly saved and closed. */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* NOTE: However, SIGSTOP (i.e., Ctrl+z) and SIGKILL -- not coincidentally,
     *       the two signals used to stop a fork bomb -- cannot be blocked,
     *       ignored, or otherwise handled. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    /* NOTE: Installing a handler does not necessarily mean the signal will
     *       occur; in practice, we ought to go off and do something useful
     *       here, but we need to do something while waiting... */
    while (1);

    return EXIT_SUCCESS;
}
