#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} allocation_strategy_t;

typedef struct block {
    size_t size;
    int free;
    int internal;
    struct block *prev;
    struct block *next;
} block_t;

extern block_t *head_block;
extern allocation_strategy_t current_strategy;

void set_allocation_strategy(allocation_strategy_t);
block_t *find_free_block(size_t size);
block_t *split_block(block_t*, size_t);
block_t *coalesce_block(block_t*);
block_t *get_user_blocks();
void reset_allocator(void);

void *malloc(size_t size);
void free(void *ptr);

#endif