#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* NOTE: Since signal handlers cannot take additional arguments, the only way
 *       to communicate with them is via globals, which are typically declared
 *       as "static" so that they are only accessible in this file. */
static pid_t child = -1;

void handler(int signum) {
    (void)signum;

    kill(child, SIGKILL);
}

/* spork: Creates a new resource-limited process. */
pid_t spork(time_t timeout) {
    struct rlimit limit;
    struct sigaction action;
    struct itimerval timer;

    if ((child = fork()) == 0) {
        /* NOTE: In the child, lower the soft and hard limits on the number of
         *       processes to 1, so that the child cannot create any children
         *       of its own. */
        getrlimit(RLIMIT_NPROC, &limit);
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit);
    }
    else {
        /* NOTE: In the parent, install a handler for SIGALRM; this must be
         *       done before setting a timer, else there is theoretically a
         *       chance it could elapse before the handler is installed... */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: ...set a non-repeating timer to send a SIGALRM after the
         *       specified amount of time has elapsed... */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &timer, NULL);

        /* NOTE: ...the benefit of using timers instead of calling "sleep" is
         *       that we can go off and do other things while waiting; if we
         *       have nothing to do, we can "pause" instead of busy waiting.
         * pause(); */
    }

    return child;
}
