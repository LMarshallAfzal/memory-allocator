#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "allocator.h"
#include <stdio.h>

void test_split_block(void) {
    void *ptr = malloc(60);
    block_t *block = (block_t *)ptr - 1;

    free(ptr);

    void *ptr_small = malloc(20);
    CU_ASSERT_PTR_NOT_NULL(ptr_small);

    block_t *small_block = (block_t *)ptr_small - 1;

    CU_ASSERT_EQUAL(small_block->size, 20);

    CU_ASSERT_PTR_NOT_NULL(small_block->next);
    size_t expected_free_size = 60 - sizeof(block_t) - 20;
    CU_ASSERT_EQUAL(small_block->next->size, expected_free_size);

    free(ptr_small);

}