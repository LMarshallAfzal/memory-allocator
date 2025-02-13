#include <unistd.h>
#include "allocator.h"

/**
 * malloc - Allocates memory blocks
 * @size: Number of bytes to allocate
 * 
 * Checks for free memory blocks on the linked list. If a free block of the
 * specified size is available, it is marked as allocated and returned.
 * If no free block is available, uses sbrk() to create a new block and adds
 * it to the end of the linked list.
 * 
 * The returned pointer points the usable memory area, after the block header.
 * The actuall allocation includes additonal space for the block management header.
 * 
 * Return: Returns a pointer allocated block, or NULL new memory allocation failed.
 */
void* malloc(size_t size) {
    block_t *free_block = find_free_block(size);

    if (free_block != NULL) {
        free_block->free = 0;
        return (void *)(free_block + 1);
    } else {
        size_t total_size = sizeof(block_t) + size;

        block_t *new_block = sbrk(total_size);

        // Check that new sbrk was able to allocate memory
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
}