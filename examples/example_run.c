#include <stdio.h>
#include "heap.h"

int main() {
    printf("=== Custom Linux Heap Manager Demo ===\n");
    heap_init();

    // Allocate some memory
    int *arr1 = (int *)my_calloc(5, sizeof(int));
    char *msg = (char *)my_calloc(20, sizeof(char));

    for (int i = 0; i < 5; i++)
        arr1[i] = i * i;

    sprintf(msg, "Heap Rocks!");

    printf("arr1 values: ");
    for (int i = 0; i < 5; i++)
        printf("%d ", arr1[i]);
    printf("\nMessage: %s\n", msg);

    // Free memory
    my_free(arr1);
    my_free(msg);

    heap_dump();   // Show heap status after operations
    heap_destroy();

    return 0;
}
