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
            /* TODO: if current->size is >= double the size of size split the block */
            return current;
        }
        current=current->next;
    }
    return NULL;
}