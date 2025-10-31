#include "heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char heap_area[HEAP_SIZE];
static Block* free_list = NULL;

#define BLOCK_SIZE sizeof(Block)

void heap_init() {
    free_list = (Block*)heap_area;
    free_list->size = HEAP_SIZE - BLOCK_SIZE;
    free_list->free = 1;
    free_list->next = NULL;
    printf("hello custom heap!\n");
}

static Block* find_free_block(size_t size) {
    Block* current = free_list;
    while (current) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static void split_block(Block* block, size_t size) {
    if (block->size <= size + BLOCK_SIZE)
        return;

    Block* new_block = (Block*)((char*)block + BLOCK_SIZE + size);
    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->free = 1;
    new_block->next = block->next;

    block->size = size;
    block->next = new_block;
}

void* my_calloc(size_t num, size_t size) {
    size_t total = num * size;
    Block* block = find_free_block(total);
    if (!block) {
        printf("Out of memory!\n");
        return NULL;
    }

    split_block(block, total);
    block->free = 0;
    void* ptr = (char*)block + BLOCK_SIZE;
    memset(ptr, 0, total);
    return ptr;
}

void my_free(void* ptr) {
    if (!ptr) return;

    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);
    block->free = 1;

    // Coalesce adjacent free blocks
    Block* current = free_list;
    while (current && current->next) {
        if (current->free && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void heap_dump() {
    printf("=== Heap Dump ===\n");
    Block* current = free_list;
    int i = 0;
    while (current) {
        printf("[%d] %p | size=%zu | free=%d\n",
               i++, (void*)current, current->size, current->free);
        current = current->next;
    }
    printf("Arena size: %d bytes\n", HEAP_SIZE);
}

void heap_destroy(void) {
    // Static heap doesn't need freeing — just reset pointer
    free_list = NULL;
    printf("Heap destroyed!\n");
}
