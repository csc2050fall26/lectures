#include <stdio.h>
#include "pair.h"

Pair f(Pair pair) {
    pair.first = 3;
    pair.second = 4;
    
    return pair;
}

void g(Pair *pair) {
    (*pair).first = 5;
    pair->second = 6;
}

int main(void) {
    Pair pair = {1, 2};

    pair = f(pair);

    printf("pair (%p)\n", (void *)&pair);
    printf(" |- pair.first (%p): %d\n", (void *)&(pair.first), pair.first);
    printf(" +- pair.second (%p): %d\n", (void *)&(pair.second), pair.second);

    g(&pair);

    printf("pair (%p)\n", (void *)&pair);
    printf(" |- pair.first (%p): %d\n", (void *)&(pair.first), pair.first);
    printf(" +- pair.second (%p): %d\n", (void *)&(pair.second), pair.second);

    return 0;
}
