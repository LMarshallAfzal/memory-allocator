# Memory Allocator

A basic heap memory allocator implementation, focusing on the core processes of `malloc()` and `free()`, which are the standard interfaces for dynamic memory allocation in C. It's designed to provide a foundational understanding of memory management at a lower level, similar to how the system's dynamic memory allocation works.

## Getting Started

**Dependencies**
* libgcc
* cmake
* CUnit (for running tests)

**Installing**
* Install all the dependencies
* Clone the repository

**Running**
* Compile program: `make all`
* Run program: `make run`
* Run tests: `make test`

## Functionality
### Memory Allocation `malloc()`
The `malloc()` function is responsible for allocating a block memory of a block of memory of a specified size:
1. **Size Check:** `malloc()` first checks if the requested size is valid (greater than zero). If the size is invalid it returns `NULL` to indicate an error.
2. **Block Search:** The allocator maintains a linked list of free memory blocks. `malloc()` iterates through this list to find a block that is large enough to satisfy the requested size. and returns the block to the user.
3. **Return to User:** The address of the usable portion of the allocated block is returned to the user.

### Memory Deallocation `free()`
The `free()` function is responsible for returning a previously allocated memory block to the pool of available memory:
1. **Pointer Check:** `free()` first checks if the provided pointer is valid (not `NULL`).

2. **Block Identification:**  Using the pointer, `free()` identifies the memory block to be deallocated. This is usually done by looking at the metadata associated with the block.

4. **Adding to Free List:**  The freed block is then marked as free in the linked list.

### Splitting
The `split_block()` function is responsible for splitting one large unallocated block into two smaller ones. This reduced wasted memory because only the required amount of memory is used the remainder can be used for other processes.
* Reduced internal fragmentation by only allocating the memory that's acutally needed.
* Allows the remaining memory to be used for other allocations.
* Improves overall memory utilisation.

### Coalescing
The `coalesce_block()` function is responsible for merging multiple smaller blocks to reduce fragmentation in memory.
* Reduces external fragmentation in the heap.
* Helps ensure larger allocation requests can be satisfied.
* Simplifies the free block list by reducing the number of entries.

### Allocation Strategies
The allocator support multiple strategies for find free blocks:
1. **First-Fit:** Returns the first free block that's is large enough to satisfy the request
2. **Best-Fit:** Returns the smallest free block that fits the requested size
3. **Worst-Fit:** Returns the largest free block available

## Author(s)
[Leonard Marshall Afzal](https://github.com/LMarshallAfzal)
