#include <stdio.h>
#include <string.h>
#include "mm.h"

typedef struct emp {
    int id;
    char name[24];
} emp_t;

typedef struct student {
    int roll;
    char name[32];
    int marks;
} student_t;

int main() {
    mm_init();

    printf("\nScenario 1 : \n");
    emp_t *e1 = XMALLOC_T(1, emp_t);
    emp_t *e2 = XMALLOC_T(1, emp_t);
    student_t *s1 = XMALLOC_T(1, student_t);
    student_t *s2 = XMALLOC_T(1, student_t);
    mm_print_memory_usage(1);

    printf("\nFreeing some blocks...\n");
    XFREE(e1);
    XFREE(s2);

    mm_print_memory_usage(1);

    printf("\nAllocating more small blocks ...\n");
    for (int i = 0; i < 6; ++i) {
        emp_t *e = XMALLOC_T(1, emp_t);
        (void)e;
    }

    mm_print_memory_usage(0);
    mm_print_block_usage();

    XFREE(e2);
    XFREE(s1);

    mm_print_memory_usage(1);

    mm_destroy();
    return 0;
}
