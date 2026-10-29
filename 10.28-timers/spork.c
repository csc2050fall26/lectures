#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* NOTE: Since a handler cannot take additional arguments, often the only way
 *       to communicate with it is to pass information via globals, typically
 *       declared as "static" so they are only accessible in this file. */
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
         *       processes so that the child cannot create any children of
         *       its own. */
        getrlimit(RLIMIT_NPROC, &limit);
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit);
    }
    else {
        /* NOTE: In the parent, install a handler for SIGALRM; this must be
         *       done before setting a timer, else there is theoritically a
         *       chance that it elapses before the handler is installed. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: Set a timer to send a SIGALRM after the specified number of
         *       seconds. This timer only needs to go off once without
         *       repeating. */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &timer, NULL);

        /* NOTE: The benefit of using timers instead of "sleep" is that we can
         *       go off and do something else during that time; if we have
         *       nothing to do, we can "pause" rather than busy waiting.
         * pause(); */
    }

    return child;
}
