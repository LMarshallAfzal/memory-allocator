#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_malloc.h"
#include "allocator.h"
#include "../utils/test_utils.h"

void test_malloc_zero_size(void) {
    TEST_SETUP();

    void *block = malloc(0);

    if (block != NULL) {
        block_t *block_head = (block_t *)((char *)block - sizeof(block_t));
        CU_ASSERT_FALSE(block_head->free);
        free(block);
    }
}

void test_malloc_basic(void) {
    TEST_SETUP();

    void *block = malloc(10);
    block_t *block_head = (block_t *)((char *)block - sizeof(block_t));

    CU_ASSERT_PTR_NOT_NULL(block);

    CU_ASSERT_FALSE(block_head->free);
    CU_ASSERT_EQUAL(block_head->size, 10);
    CU_ASSERT_PTR_NULL(block_head->next);

    free(block);
}

void test_malloc_multiple_allocations(void) {
    TEST_SETUP();

    void *block1 = malloc(100);
    void *block2 = malloc(200);
    void *block3 = malloc(300);

    CU_ASSERT_PTR_NOT_NULL(block1);
    CU_ASSERT_PTR_NOT_NULL(block2);
    CU_ASSERT_PTR_NOT_NULL(block3);

    CU_ASSERT_PTR_NOT_EQUAL(block1, block2);
    CU_ASSERT_PTR_NOT_EQUAL(block2, block3);
    CU_ASSERT_PTR_NOT_EQUAL(block1, block3);

    block_t *block_head1 = (block_t *)((char *)block1 - sizeof(block_t));
    block_t *block_head2 = (block_t *)((char *)block2 - sizeof(block_t));
    block_t *block_head3 = (block_t *)((char *)block3 - sizeof(block_t));

    CU_ASSERT_FALSE(block_head1->free);
    CU_ASSERT_FALSE(block_head2->free);
    CU_ASSERT_FALSE(block_head3->free);

    CU_ASSERT_EQUAL(block_head1->size, 100);
    CU_ASSERT_EQUAL(block_head2->size, 200);
    CU_ASSERT_EQUAL(block_head3->size, 300);

    CU_ASSERT(block_head1->next == block_head2);
    CU_ASSERT(block_head2->next == block_head3);
    CU_ASSERT(block_head3->next == NULL);

    free(block1);
    free(block2);
    free(block3);
}

void test_malloc_large_allocation(void) {
    TEST_SETUP();

    void *block = malloc(1024 * 1024);
    CU_ASSERT_PTR_NOT_NULL(block);
    
    if (block) {
        block_t *block_head = (block_t *)((char *)block - sizeof(block_t));
        CU_ASSERT_FALSE(block_head->free);
        CU_ASSERT_EQUAL(block_head->size, 1024 * 1024);
        free(block);
    }
}