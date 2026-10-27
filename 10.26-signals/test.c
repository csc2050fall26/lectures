#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signum) {
    /* NOTE: Since a handler responds to an asynchronous signal, it cannot take
     *       additional arguments or return any values -- it effectively has no
     *       caller... */

    if (signum == SIGINT) {
        printf("But RANDALL lets their processes stay up on the CPU as long as they want!\n");
    }
    else if (signum == SIGQUIT) {
        printf("But JOSE lets their processes eat RAM before dinner!\n");
    }
    else {
        printf("Handling signal %d...\n", signum);
    }

    /* NOTE: ...it also shouldn't call async-signal-unsafe functions such as
     *       "printf", which depend on the state of memory which cannot be
     *       predicted at the time the signal occurs. */
}

int main(void) {
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* NOTE: There are legitimate reasons to handle a SIGINT instead of
     *       immediately terminating, for example, to ensure that any open
     *       files are correctly saved and closed... */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* NOTE: ...however, SIGSTOP and SIGKILL cannot be blocked, ignored,
     *       or otherwise handled; their default actions cannot be changed. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    /* NOTE: If we were handling signals in practice, presumably we'd go off
     *       and do something useful while waiting for the signal we're hoping
     *       to handle to occur... */
    while (1);

    return EXIT_SUCCESS;
}
