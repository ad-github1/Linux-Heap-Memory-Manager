#ifndef MM_H
#define MM_H

#include <stddef.h>

#define MM_HEAP_SIZE (1024 * 1024) /* 1 MB heap */

/* Public API */
void mm_init(void);
void *XMALLOC(size_t size);
void XFREE(void *ptr);
void mm_print_memory_usage(int verbose);
void mm_print_block_usage(void);
void mm_destroy(void);

/* For tests: helper macros */
#define XMALLOC_T(count, type) ((type *)XMALLOC((count) * sizeof(type)))
#define XFREE_PTR(p) XFREE((void*)(p))

#endif /* MM_H */
