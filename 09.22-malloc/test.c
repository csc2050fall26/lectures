#include <stdlib.h>
#include <stdio.h>

int *pair(int, int);
void f(void);

int main(void) {
    int *arr;

    arr = pair(1, 2);
    f();

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return 0;
}

int *pair(int first, int second) {
    /* NOTE: Since the value of an array is an address, returning a local array
     *       is really just returning garbage: it's the address of local memory
     *       that is about to be popped off of the runtime stack.
     * int arr[2]; */

    /* NOTE: Instead, "malloc" returns a pointer to a dynamically allocated
     *       block on the heap; since pointer and array syntax is
     *       interchangeable, we can still index that block. */
    int *arr = (int *)malloc(sizeof(int) * 2);

    arr[0] = first;
    arr[1] = second;

    return arr;
}

void f(void) {
    /* NOTE: Since "f" contains the same locals and is called in essentially
     *       the same place as "reduce", in all likelihood, the array below
     *       will end up reusing/overwriting the memory of the array above. */
    int arr[2] = {0};

    (void)arr;
}
