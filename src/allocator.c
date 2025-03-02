#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "allocator.h"

allocation_strategy_t current_strategy = FIRST_FIT;
block_t *head_block = NULL;

/**
 * set_allocation_strategy - Sets the allocation strategy to use
 * @strategy: The strategy to use (FIRST_FIT, BEST_FIT, or WORST_FIT)
 */
void set_allocation_strategy(allocation_strategy_t strategy) {
    current_strategy = strategy;
}

/**
 * find_free_block - Searches linked list for available memory block
 * @size: Minimum size (in bytes) of free block
 * 
 * Searches the linked list for an available block of the required size
 * based on the current allocation strategy
 * 
 * Return: A pointer to available block, NULL if no available block was found.
 */
block_t *find_free_block(size_t size) {
    block_t *current = head_block;
    block_t *best = NULL;
    block_t *worst = NULL;

    // Coalesce adjacent free blocks before searching
    block_t *temp = head_block;
    while (temp != NULL) {
        if (temp->free) {
            if ((temp->next && temp->next->free) || (temp->prev && temp->prev->free)) {
                temp = coalesce_block(temp);
            }
        }
        temp = temp->next;
    }

    // First-fit allocation strategy
    if (current_strategy == FIRST_FIT) {
        while (current != NULL) {
            if (current->free && current->size >= size) {            
                if (current->size >= size + sizeof(block_t) + 4) {
                    current = split_block(current, size);
                }
                return current;
                
            }
            current = current->next;
        }
        return NULL;
    }

    // Best-fit and Worst-fit allocation strategies
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (best == NULL || current->size < best->size) {
                best = current;
            }

            if (worst == NULL || current->size > worst->size) {
                worst = current;
            }
        }
        current = current->next;
    }

    // Return the appropriate block based on strategy
    if (current_strategy == BEST_FIT) {
        if (best && best->size >= size + sizeof(block_t) + 4) {
            best = split_block(best, size);
        }
        return best;

    } else {
        if (worst && worst->size >= size + sizeof(block_t) + 4) {
            worst = split_block(worst, size);
        }
        return worst;
    }
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
    block_t *new_block = (block_t *)((char *)(block + 2) + size);

    new_block->size = block->size - size - sizeof(block_t);
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

/**
 * coalesce_block - Merges two adjacent free memory blocks into one larger block
 * @block: Pointer to the block to be coalesced with the previous block
 * 
 * The size of the previous block is updated to reflect the combined size of both blocks.
 * The linked list is then updated to remove the merged block and connect the previous block
 * to the next block.
 * 
 * Return: A pointer to the newly coalesced block (the previous block)
 */
block_t *coalesce_block(block_t *block) {
    if (block->next && block->next->free) {
        block->size += sizeof(block_t) + block->next->size;
        block->next = block->next->next;

        if (block->next) {
            block->next->prev = block;
        }        
    }

    if (block->prev && block->prev->free) {
        block->prev->size += sizeof(block_t) + block->size;
        block->prev->next = block->next;

        if (block->next) {
            block->next->prev = block->prev;
        }
        return block->prev;
    }

    return block;
}

/**
 * get_user_blocks - Retrieves first user generated memory block
 * Return: First user generated memory block or NULL
 */
block_t *get_user_blocks() {
    if (head_block != NULL && head_block->next != NULL) {
        // Skip first two system-created blocks
        return head_block->next->next;  
    }
    return NULL;
}