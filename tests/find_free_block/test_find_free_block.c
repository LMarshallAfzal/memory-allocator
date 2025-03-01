#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "allocator.h"
#include <stdio.h>

void test_split_block(void) {
    void *ptr = malloc(60);

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

void test_coalesce_block(void) {
    void *ptr1 = malloc(5);
    void *ptr2 = malloc(5);

    free(ptr1);
    free(ptr2);

    void *ptr3 = malloc(15);
    CU_ASSERT_PTR_NOT_NULL(ptr3);

    block_t *block3 = (block_t *)ptr3 - 1;

    size_t expected_block_size = 5 + sizeof(block_t) + 5;
    CU_ASSERT_EQUAL(block3->size, expected_block_size);

    free(ptr3);
}