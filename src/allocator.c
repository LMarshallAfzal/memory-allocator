#include <stdlib.h>
#include <unistd.h>
#include "allocator.h"

static block_t *head_block = NULL;

void init_allocator();
block_t *find_free_block(size_t);

void init_allocator() {
    size_t initial_size = 4096;
    head_block = (block_t *)sbrk(initial_size);

    if (head_block == (void *)-1) {
        return;
    }

    head_block->size = initial_size;
    head_block->free = 1;
    head_block->next = NULL;
}

block_t *find_free_block(size_t size) {
    block_t *current = head_block;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current=current->next;
    }
    return NULL;
}
