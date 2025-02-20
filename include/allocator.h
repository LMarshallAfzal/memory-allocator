#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

typedef struct block {
    size_t size;
    int free;
    struct block *prev;
    struct block *next;
} block_t;

extern block_t *head_block;

block_t *find_free_block(size_t size);
void *malloc(size_t size);
void free(void *ptr);

#endif