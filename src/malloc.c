#include <__stddef_size_t.h>
#include "allocator.c"

void* malloc(size_t size) {
    block_t *free_block = find_free_block(size);

    if (free_block != NULL) {
        free_block->free = 0;
        return (void *)(free_block + 1);
    } else {
        void *new_memory = sbrk(size);

        if (new_memory == (void *)-1) {
            return NULL;
        }

        block_t *new_block; 
        new_block->size = size;
        new_block->free = 0;
        new_block->next = head_block;

        head_block = new_block;

        return (void *)(new_block + 1);
    }
    
}