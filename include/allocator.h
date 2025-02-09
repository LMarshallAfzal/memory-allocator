#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;

static block_t *head_block;

void init_allocator();
block_t *find_free_block(size_t size);
void *malloc(size_t size);

#endif