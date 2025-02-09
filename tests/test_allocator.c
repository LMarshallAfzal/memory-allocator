#include <stdio.h>
#include "allocator.h"

int main() {
    init_allocator();

    void *ptr1 = malloc(128);
    if (ptr1 == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("Allocated 128 bytes at %p\n", ptr1);

    void *ptr2 = malloc(256);
    if (ptr2 == NULL) {
        printf("malloc failed!\n");
        return 1;
    }
    printf("Allocated 256 bytes at %p\n", ptr2);
}