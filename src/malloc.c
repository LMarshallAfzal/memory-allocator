#include <unistd.h>
#include "allocator.h"

void* malloc(size_t size) {
    block_t *free_block = find_free_block(size);

    if (free_block != NULL) {
        free_block->free = 0;
        return (void *)(free_block + 1);
    } else {
        size_t total_size = sizeof(block_t) + size;

        block_t *new_block = sbrk(total_size);

        if (new_block == (void *)-1) {
            return NULL;
        }

        new_block->size = size;
        new_block->free = 0;

        if (head_block == NULL) {
            head_block = new_block;
            new_block->next = NULL;
        } else {
            block_t *current = head_block;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_block;
            new_block->next = NULL;
        }

        return (void *)(new_block + 1);
    }
    // linked list is being built backwards
    // reuse of freed blocks isn't working
}