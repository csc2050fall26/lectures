#include <stdio.h>

void swap(int *, int *);
void reverse(int[], int);

int main(void) {
    int arr[] = {1, 2, 3, 4};

    reverse(arr, 4);

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
    /* NOTE: In C, arguments are always pass-by-value; the value of an array is
     *       an address, which "decays" into a pointer. Since we have a pointer
     *       to the caller's array, we can modify that array directly; we don't
     *       need to return a copy of the array. */
    int i;

    for (i = 0; i < n / 2; i++) {
        swap(&arr[i], &arr[n - 1 - i]);
        
        /* NOTE: The above is arguably slightly inefficient; indexing an array
         *       is offsetting and dereferencing its address, so the above
         *       dereferences an address just to ask for that same address
         *       back; it is equivalent to:
         * swap(arr + i, arr + (n - 1 - i)); */
    }
}
