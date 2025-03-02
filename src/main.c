#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

#define MAX_ALLOCATIONS 100

int main(void) {
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
        printf(" 4. Set allocation strategy\n");
        printf(" 5. Exit\n");
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
                void *available_allocs[MAX_ALLOCATIONS];
                int available_count = 0;

                for (int i = 0; i < num_allocations; i++) {
                    if (allocations[i] != NULL) {
                        available_allocs[available_count++] = allocations[i];
                    }
                }

                if (available_count == 0) {
                    printf("No allocations to free.\n");
                    break;
                }

                printf("\nAvailable allocations:\n");
                for (int i = 0; i < available_count; i++) {
                    block_t *block_header = (block_t *)((char *)available_allocs[i] - sizeof(block_t));
                    printf(" %d: address=%p, size=%zu\n", i, available_allocs[i], block_header->size);
                }

                int index;
                printf("\nEnter allocation index to free (0 to %d): ", available_count - 1);
                if (scanf("%d", &index) != 1 || index < 0 || index >= available_count) {
                    printf("Invalid index. Returning to menu.\n");
                    break;
                }
                
                void *ptr_to_free = available_allocs[index];
                printf("Freed memory at address %p\n", ptr_to_free);
                free(ptr_to_free);
                
                for (int i = 0; i < num_allocations; i++) {
                    if (allocations[i] == ptr_to_free) {
                        allocations[i] = NULL;
                        break;
                    }
                }
                break;
            }
            case 3: {
                block_t *current = get_user_blocks();
                int i = 0;
                printf("\nCurrent Memory Blocks:\n");
                printf("--------------------------------------------------\n");
                while (current != NULL) {
                    if (current->internal) {
                        current = current->next;
                        continue;
                    }
                    printf("Block %d: address=%p, size=%zu, free=%d\n", i++, current, current->size, current->free);
                    current = current->next;
                }
                printf("--------------------------------------------------\n");
                break;
            }
            case 4: {
                int strategy;
                printf("Select allocation strategy:\n");
                printf(" 1. First-Fit (allocate first block that fits)\n");
                printf(" 2. Best-Fit (allocate smallest block that fits)\n");
                printf(" 3. Worst-Fit (allocate largest block that fits)\n");
                printf(" Enter strategy (1-3): ");

                if (scanf("%d", &strategy) != 1 || strategy < 1 || strategy > 3) {
                    printf("Invalid strategy selection. Returning to menu.\n");
                    break;
                }

                switch(strategy) {
                    case 1:
                        set_allocation_strategy(FIRST_FIT);
                        printf("Strategy set to First-Fit\n");
                        break;
                    case 2:
                        set_allocation_strategy(BEST_FIT);
                        printf("Strategy set to Best-Fit\n");
                        break;
                    case 3:
                        set_allocation_strategy(WORST_FIT);
                        printf("Strategy set to Worst-Fit\n");
                        break;
                }
                break;
            }
            case 5: {
                printf("Exiting demo, Goodbye!\n");
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}