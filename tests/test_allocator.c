#include <stdio.h>
#include "allocator.h"

int main() {
    init_allocator();

    printf("Size of block_t: %zu bytes\n", sizeof(block_t));

    void *ptr1 = malloc(12);
    if (ptr1 == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("Allocated 12 bytes at %p\n", ptr1);

    void *ptr2 = malloc(8);
    if (ptr2 == NULL) {
        printf("malloc failed!\n");
        return 1;
    }
    printf("Allocated 8 bytes at %p\n", ptr2);

    block_t *current = head_block;
    int i = 0;
    while (current != NULL) {
        printf("Block %d: address=%p, size=%zu, free=%d\n", 
                i++, current, current->size, current->free);
        current = current->next;
    }

    printf("Freeing ptr1\n");
    free(ptr1);

    void *ptr3 = malloc(10);
    if (ptr3 == NULL) {
        printf("malloc failed!\n");
        return 1;
    }

    current = head_block;
    i = 0;
    while (current != NULL) {
        printf("Block %d: address=%p, size=%zu, free=%d\n", 
                i++, current, current->size, current->free);
        current = current->next;
    }

    free(ptr2);
    free(ptr3);

    return 0;

}