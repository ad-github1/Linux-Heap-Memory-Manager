#include "heap.h"
#include <stdio.h>

int main() {
    heap_init();

    int* arr = (int*)my_calloc(10, sizeof(int));
    for (int i = 0; i < 10; i++) arr[i] = i;

    my_free(arr);
    heap_dump();

    return 0;
}
