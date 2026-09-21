#include <stdio.h>
#include "add.h"
#include "max.h"

int reduce(int[], int, int (*)(int, int));

int main(void) {
    int arr[] = {2, -1, 9, 8, 5, -3, 0, 8};

    /* NOTE: By passing a pointer to a function to perform the combining
     *       operation, we can reduce code duplication, using the same function
     *       to compute different results by passing different pointers. */
    printf("reduce(%p, 8, %p): %d\n",
     (void *)arr, (void *)add, reduce(arr, 8, add));

    printf("reduce(%p, 8, %p): %d\n",
     (void *)arr, (void *)max, reduce(arr, 8, max));

    return 0;
}

int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    /* NOTE: Finding the sum of an array is very similar to finding its max
     *       element; both involve reducing the elements into a single value by
     *       repeatedly combining elements via some operation. */
    for (i = 1; i < n; i++) {
        val = fn(val, arr[i]);
    }

    return val;
}
