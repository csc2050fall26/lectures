#include <stdio.h>

void swap(int *, int *);
void reverse(int[], int);

int main(void) {
    int arr[] = {1, 2, 3, 4};

    /* NOTE: In C, arguments are always pass-by-value; the value of an array is
     *       its first element's address, which "decays" into a pointer when
     *       passed as argument. As a result, "reverse" can modify the array
     *       in-place rather than returning a new copy of the array. */
    reverse(arr, 4);

    /* NOTE: Arrays are simply stored as contiguous blocks of memory. Indexing
     *       an array out-of-bounds simply accesses memory outside that block,
     *       which may or may not get or set some seemingly random, unrelated
     *       value elsewhere in memory.
     * reverse(arr, 5); */

    /* NOTE: However, straying sufficiently far outside the bounds of an array
     *       will likely lead to a segmentation fault. We can then recompile
     *       with "-g" and run the program through GDB in order to provide a
     *       traceback of how that error occurred.
     * reverse(arr, 65536); */

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" |- %p: %d\n", (void *)&arr[1], arr[1]);
    printf(" |- %p: %d\n", (void *)&arr[2], arr[2]);
    printf(" +- %p: %d\n", (void *)&arr[3], arr[3]);

    return 0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void reverse(int arr[], int n) {
    int i;

    /* NOTE: Since indexing an array is offsetting and dereferencing its
     *       address, the call to "swap" below dereferences an address just to
     *       ask for that address right back. It is equivalent to:
     * swap(arr + i, arr + (n - 1 - i)); */
    for (i = 0; i < n / 2; i++) {
        swap(&arr[i], &arr[n - 1 - i]);
    }
}
