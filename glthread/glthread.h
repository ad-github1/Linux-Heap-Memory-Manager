#ifndef GLTHREAD_H
#define GLTHREAD_H

typedef struct Glthread {
    struct Glthread *next;
    struct Glthread *prev;
} Glthread;

static inline void glthread_init(Glthread *n) {
    n->next = n->prev = n;
}

static inline void glthread_add_tail(Glthread *head, Glthread *node) {
    node->prev = head->prev;
    node->next = head;
    head->prev->next = node;
    head->prev = node;
}

static inline void glthread_remove(Glthread *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = node->prev = node;
}

static inline int glthread_empty(Glthread *head) {
    return head->next == head;
}

#endif /* GLTHREAD_H */
