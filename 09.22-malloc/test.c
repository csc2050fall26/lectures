#include <stdlib.h>
#include <stdio.h>

int *pair(int, int);
void f(void);

int main(void) {
    int *arr;

    arr = pair(1, 2);
    
    /* NOTE: Since the above function returns a pointer to memory on the heap,
     *       that memory is not deallocated and reused by later function calls
     *       such as the below function. */
    f();

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return 0;
}

int *pair(int first, int second) {
    /* NOTE: This local array is stored on the runtime stack; it will be
     *       deallocated once this function returns, and returning a pointer to
     *       it is essentially returning garbage.
     * int arr[2]; */

    /* NOTE: This is instead a pointer to a contiguous block of memory on the
     *       heap, which will persist after this function returns. Recall that
     *       pointer and array syntax is largely interchangeable. */
    int *arr = (int *)malloc(sizeof(int) * 2);

    arr[0] = first;
    arr[1] = second;

    return arr;
}

void f(void) {
    int arr[2] = {0};

    (void)arr;
}

