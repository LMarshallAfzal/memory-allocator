// Header file for function declarations and structs
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

// Memory block structure
typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;

// Function declartions
void* malloc(size_t size);

#endif