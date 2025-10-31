#ifndef HEAP_H
#define HEAP_H

#include <stddef.h> // for size_t

#define HEAP_SIZE (1024 * 1024) // 1MB heap

typedef struct Block {
    size_t size;           // Size of user memory
    int free;              // 1 = free, 0 = used
    struct Block* next;    // Next block in linked list
} Block;

void heap_init();
void* my_calloc(size_t num, size_t size);
void my_free(void* ptr);
void heap_dump();

#endif
void heap_destroy(void);

