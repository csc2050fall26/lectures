#include <stdio.h>
#include "add.h"
#include "max.h"

int reduce(int[], int, int (*)(int, int));

int main(void) {
    int arr[] = {2, -1, 9, 8, 5, -3, 0, 8};

    /* NOTE: By passing as argument a pointer to a function to perform the
     *       combining operation, the same "reduce" function will be able to
     *       compute both the max element and the sum of the elements without
     *       duplicating most of its code. */
    printf("reduce(%p, 8, %p): %d\n",
     (void *)arr, (void *)&add, reduce(arr, 8, &add));

    printf("reduce(%p, 8, %p): %d\n",
     (void *)arr, (void *)&max, reduce(arr, 8, &max));

    return 0;
}

int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    /* NOTE: Finding the max element in an array is very similar to finding the
     *       sum of the elements in an array: both involve reducing the elements
     *       into a single value by repeatedly applying some operation to
     *       combine two elements. */
    for (i = 1; i < n; i++) {
        val = (*fn)(val, arr[i]);
    }

    return val;
}
