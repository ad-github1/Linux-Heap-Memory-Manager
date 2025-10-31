#include "mm.h"
#include "../glthread/glthread.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct MMBlock {
    size_t size;
    int free;
    struct MMBlock *next;
    struct Glthread node;
} MMBlock;

#define ALIGN 16
#define ALIGN_UP(n) (((n) + (ALIGN - 1)) & ~(ALIGN - 1))

static unsigned char mm_heap[MM_HEAP_SIZE];
static MMBlock *mm_head = NULL;
static Glthread free_list;
static Glthread used_list;
static int mm_inited = 0;

static size_t header_size() { return ALIGN_UP(sizeof(MMBlock)); }

void mm_init(void) {
    if (mm_inited) return;
    mm_head = (MMBlock *)mm_heap;
    size_t hdr = header_size();
    mm_head->size = MM_HEAP_SIZE - hdr;
    mm_head->free = 1;
    mm_head->next = NULL;
    glthread_init(&free_list);
    glthread_init(&used_list);
    glthread_init(&mm_head->node);
    glthread_add_tail(&free_list, &mm_head->node);
    mm_inited = 1;
    printf("mm_init: heap %zu bytes, header %zu\n", (size_t)MM_HEAP_SIZE, hdr);
}

static inline void *block_to_ptr(MMBlock *b) {
    return (void *)((unsigned char *)b + header_size());
}

static inline MMBlock *ptr_to_block(void *p) {
    return (MMBlock *)((unsigned char *)p - header_size());
}

static MMBlock *find_fit(size_t size) {
    Glthread *h = free_list.next;
    while (h != &free_list) {
        MMBlock *b = (MMBlock *)((unsigned char *)h - offsetof(MMBlock, node));
        if (b->free && b->size >= size) return b;
        h = h->next;
    }
    return NULL;
}

static void split_block(MMBlock *b, size_t want) {
    size_t hdr = header_size();
    if (b->size <= want + hdr + 16) return;
    unsigned char *newloc = (unsigned char *)b + hdr + want;
    MMBlock *nb = (MMBlock *)newloc;
    nb->size = b->size - want - hdr;
    nb->free = 1;
    nb->next = b->next;
    glthread_init(&nb->node);
    glthread_add_tail(&free_list, &nb->node);
    b->next = nb;
    b->size = want;
}

static void coalesce_all(void) {
    MMBlock *cur = mm_head;
    while (cur && cur->next) {
        if (cur->free && cur->next->free) {
            glthread_remove(&cur->next->node);
            cur->size += header_size() + cur->next->size;
            cur->next = cur->next->next;
            continue;
        }
        cur = cur->next;
    }
}

void *XMALLOC(size_t size) {
    if (!mm_inited) mm_init();
    if (size == 0) return NULL;
    size = ALIGN_UP(size);
    MMBlock *b = find_fit(size);
    if (!b) return NULL;
    glthread_remove(&b->node);
    split_block(b, size);
    b->free = 0;
    glthread_init(&b->node);
    glthread_add_tail(&used_list, &b->node);
    void *p = block_to_ptr(b);
    memset(p, 0, size);
    return p;
}

void XFREE(void *ptr) {
    if (!ptr) return;
    MMBlock *b = ptr_to_block(ptr);
    if (b->free) return;
    b->free = 1;
    glthread_remove(&b->node);
    glthread_init(&b->node);
    glthread_add_tail(&free_list, &b->node);
    coalesce_all();
}

void mm_print_block_usage(void) {
    printf("\nmm_print_block_usage:\n");
    MMBlock *cur = mm_head;
    int idx = 0;
    while (cur) {
        printf(" Block %d @%p  size=%zu  %s\n",
               idx++, (void*)cur, cur->size, cur->free ? "FREE" : "ALLOC");
        cur = cur->next;
    }
}

void mm_print_memory_usage(int verbose) {
    size_t total_used = 0, total_free = 0;
    MMBlock *cur = mm_head;
    int blocks = 0;
    while (cur) {
        if (cur->free) total_free += cur->size;
        else total_used += cur->size;
        blocks++;
        cur = cur->next;
    }
    printf("\nmm_print_memory_usage: blocks=%d used=%zu free=%zu\n",
           blocks, total_used, total_free);
    if (verbose) mm_print_block_usage();
}

void mm_destroy(void) {
    mm_head = NULL;
    mm_inited = 0;
    glthread_init(&free_list);
    glthread_init(&used_list);
}
