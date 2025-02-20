#include <stdlib.h>
#include <unistd.h>
#include "allocator.h"

block_t *head_block;
block_t *find_free_block(size_t);

/**
 * find_free_block - Searches linked list for available memory block
 * @size: Minimum size (in bytes) of free block
 * 
 * Searches the linked list for an available block of the required size.
 * 
 * Return: A pointer to available block, NULL if no available block was found.
 */
block_t *find_free_block(size_t size) {
    block_t *current = head_block;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size >= size * 2) {
                split_block(current, size);
            }

            return current;
        }
        current=current->next;
    }
    return NULL;
}

/**
 * split_block - Splits a free memory block into two smaller blocks
 * @block: Pointer to the block to be split
 * @size: Size (in bytes) of the new allocated block
 * 
 * This function takes a large free memory block and splits it into two smaller blocks.
 * The newly created free block is placed immediately after the allocated block.
 * 
 * Return: A pointer to the resized block
 */
block_t *split_block(block_t *block, size_t size) {
    block_t *new_block = (block_t *)((char *)block + sizeof(block_t) + size);

    new_block->size = block->size - sizeof(block_t) - size;
    new_block->free = 1;
    new_block->prev = block;
    new_block->next = block->next;

    block->size = size;
    block->next = new_block;

    if (new_block->next) {
        new_block->next->prev = new_block;
    }

    return block;
}