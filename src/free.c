#include "allocator.h"

void free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    block_t *block_ptr = (block_t *)(ptr - 1);

    block_t *current = head_block;

    while (current != NULL) {
        // What exactly is being comparied here.
        if (current == block_ptr) {
            if (!current->free) {
                current->free = 1;
            }
            return;
        }
        current = current->next;
    }
}