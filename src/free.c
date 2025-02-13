#include "allocator.h"
#include <stdio.h>
/**
 * free - Deallocates a previously allocated memory block
 * @block: Pointer to the memory block to free
 * 
 * Marks a previously allcoated block as free for reuse.
 * The pointer must have been returned by a previous call to malloc.
 * If pointer is null not operation is returned.
 */
void free(void *block) {
    if (block == NULL) {
        return;
    }

    // Return to the block header
    block_t *block_header = (block_t *)((char *)block - sizeof(block_t));

    block_t *current = head_block;

    // Validate that block is in out list and mark as freed.
    while (current != NULL) {
        if (current == block_header) {
            if (!current->free) {
                current->free = 1;
            }
            return;
        }
        current = current->next;
    }
}