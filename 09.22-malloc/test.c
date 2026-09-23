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

    /* NOTE: It is not possible to free only a portion of a block...
     * free(arr + 1); */

    /* NOTE: ...and it makes no sense to free a block that isn't on the heap...
     * free(&arr); */

    /* NOTE: ...but failing to free an allocated block is a leak... */
    free(arr);

    /* NOTE: ...so each allocated block must be freed *exactly* once...
     * free(arr); */

    /* NOTE: ...and once a block is freed, its data is not zeroed out, so it
     *       may still appear to be preserved, but in fact that block is
     *       available for anyone to reuse and overwrite.
     * printf("arr: %p\n", (void *)arr);
     * printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
     * printf(" +- %p: %d\n", (void *)&arr[1], arr[1]); */

    return 0;
}

int *pair(int first, int second) {
    /* NOTE: Since the value of an array is the address of its first element,
     *       returning an array returns the address of memory that has been
     *       deallocated and may be overwritten in the future.
     * int arr[2]; */

    /* NOTE: "malloc" returns a pointer to a contiguous block of memory of the
     *       requested size on the heap, and since pointer and array syntax is
     *       largely interchangeable, that block can then be indexed. */
    int *arr = (int *)malloc(sizeof(int) * 2);

    arr[0] = first;
    arr[1] = second;

    return arr;
}

void f(void) {
    /* NOTE: Since "f" has the same locals as "pair", and since "f" is called
     *       by the same function as "pair", in all likelihood this local array
     *       will reuse the same memory as the one above. */
    int arr[2] = {0};

    (void)arr;
}
