#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

void test_malloc_basic(void) {
    void *block = malloc(10);
    block_t *block_head = (block_t *)((char *)block - sizeof(block_t));

    CU_ASSERT_PTR_NOT_NULL(block);

    CU_ASSERT_FALSE(block_head->free);
    CU_ASSERT_EQUAL(block_head->size, 10);
    CU_ASSERT_PTR_NULL(block_head->next);

    free(block);
}

void test_malloc_multiple(void) {
    void *ptr1 = malloc(10);
    void *ptr2 = malloc(10);

    CU_ASSERT_PTR_NOT_NULL(ptr1);
    CU_ASSERT_PTR_NOT_NULL(ptr2);

    block_t *ptr1_head = (block_t *)((char *)ptr1 - sizeof(block_t));
    block_t *ptr2_head = (block_t *)((char *)ptr2 - sizeof(block_t));

    CU_ASSERT_FALSE(ptr1_head->free);
    CU_ASSERT_EQUAL(ptr1_head->size, 10);
    CU_ASSERT(ptr1_head->next == ptr2_head);

    CU_ASSERT_FALSE(ptr2_head->free);
    CU_ASSERT_EQUAL(ptr2_head->size, 10);
    CU_ASSERT_PTR_NULL(ptr2_head->next);

    free(ptr1);
    free(ptr2);
}

void test_free_basic(void) {
    void *block = malloc(10);
    block_t *block_head = (block_t *)((char *)block - sizeof(block_t));

    CU_ASSERT_PTR_NOT_NULL(block);
    CU_ASSERT_FALSE(block_head->free);

    free(block);

    CU_ASSERT_TRUE(block_head->free);
}

void test_free_null(void) {
    free(NULL);
    CU_ASSERT(1);
}

void test_reuse_block(void) {
    void *block1 = malloc(5);
    free(block1);
    void *block2 = malloc(5);

    CU_ASSERT_PTR_EQUAL(block1, block2);
}