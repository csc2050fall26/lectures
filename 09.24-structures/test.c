#include <stdio.h>
#include "pair.h"

/* NOTE: The value of a structure is the entire structure; functions receive
 *       copies of structures as arguments, and must return those structures in
 *       order to communicate new values back to their callers. */
Pair f(Pair pair) {
    pair.first = 3;
    pair.second = 4;

    return pair;
}

/* NOTE: Of course, we always have the option of opting-in to pass-by-reference
 *       behavior in C by passing a pointer to a structure rather than the
 *       value of that structure. */
void g(Pair *pair) {
    (*pair).first = 5;
    pair->second = 6;
}

int main(void) {
    Pair pair = {1, 2};

    pair = f(pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- pair.first (%p): %d\n", (void *)&(pair.first), pair.first);
    printf(" +- pair.second (%p): %d\n", (void *)&(pair.second), pair.second);

    g(&pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- pair.first (%p): %d\n", (void *)&(pair.first), pair.first);
    printf(" +- pair.second (%p): %d\n", (void *)&(pair.second), pair.second);

    return 0;
}
