#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

#define MAX_ALLOCATIONS 100

int main(void) {
    head_block = NULL;
    void *allocations[MAX_ALLOCATIONS] = {0};
    int num_allocations = 0;
    int choice;

    printf("====================================\n");
    printf(" Welcome to the Memory Allocator!\n");
    printf("====================================\n");

    while(1) {
        printf("\nMenu:\n");
        printf(" 1. Allocate memory\n");
        printf(" 2. Free memory\n");
        printf(" 3. Display memory blocks\n");
        printf(" 4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting demo.\n");
            break;
        }

        switch (choice) {
            case 1: {
                int size;
                printf("Enter number of bytes to allocate: ");
                if (scanf("%d", &size) != 1 || size <= 0) {
                    printf("Invalid size input. Returning to menu.\n");
                    break;
                }
                void *ptr = malloc((size_t)size);
                if (ptr == NULL) {
                    printf("Memory allocation failed!\n");
                } else {
                    printf("Allocated %d bytes at address %p\n", size, ptr);
                    if (num_allocations < MAX_ALLOCATIONS) {
                        allocations[num_allocations++] = ptr;
                    } else {
                        printf("Warning: Maximum number of allocations reached.\n");
                    }
                }
                break;
            }
            case 2: {
                if (num_allocations == 0) {
                    printf("No allocations to free.\n");
                    break;
                }
                int index;
                printf("Enter allocation index to free (0 to %d):", num_allocations - 1);
                if (scanf("%d", &index) != 1 || index < 0 || index >= num_allocations) {
                    printf("Invalid index. Returning to menu.\n");
                    break;
                }
                if (allocations[index] != NULL) {
                    free(allocations[index]);
                    printf("Freed memory at index %d (address %p)\n", index, allocations[index]);
                    allocations[index] = NULL;
                } else {
                    printf("Allocation at index %d is already freed.\n", index);
                }
                break;
            }
            case 3: {
                block_t *current = head_block;
                int i = 0;
                printf("\nCurrent Memory Blocks:\n");
                printf("--------------------------------------------------\n");
                while (current != NULL) {
                    printf("Block %d: address=%p, size=%zu, free=%d\n", i++, current, current->size, current->free);
                    current = current->next;
                }
                printf("--------------------------------------------------\n");
                break;
            }
            case 4: {
                printf("Existing demo, Goodbye!\n");
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}