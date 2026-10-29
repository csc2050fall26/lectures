#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* NOTE: Since a signal handler cannot take additional arguments, often the
 *       only way to communicate with them is to pass information in globals;
 *       declaring a global as "static" ensures that it is only accessible in
 *       this file. For simplicity, we'll assume there is only one child. */
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
         *       done before setting a timer, else there is a chance the signal
         *       arrives before we are prepared to handle it. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* NOTE: Set a non-repeating timer to send a SIGALRM after the given
         *       number of seconds. The parent must have the timer because the
         *       child could simply choose to ignore a SIGALRM. */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &timer, NULL);

        /* NOTE: The parent can then go off and do something else (which might
         *       just be as simple as waiting for the child); if it had nothing
         *       else to do, "pause" will avoid busy waiting.
         * pause(); */
    }

    return child;
}
