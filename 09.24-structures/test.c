#include <stdio.h>
#include "pair.h"

/* NOTE: Like an array, a structure is stored as a contiguous block of memory.
 *       Unlike an array, the value of a structure is the entire structure, so
 *       a function receives a local copy of a structure as argument. */
Pair f(Pair pair) {
    pair.first = 3;
    pair.second = 4;

    return pair;
}

/* NOTE: Of course, we always have the option of opting-in to pass-by-reference
 *       behavior using pointers; note that the "." operator has precedence
 *       over the unary "*" operator. */
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
