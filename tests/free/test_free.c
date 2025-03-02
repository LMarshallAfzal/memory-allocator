#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_free.h"
#include "allocator.h"
#include "../utils/test_utils.h"

void test_free_basic(void) {
    TEST_SETUP();

    void *block = malloc(10);
    block_t *block_head = (block_t *)((char *)block - sizeof(block_t));

    CU_ASSERT_PTR_NOT_NULL(block);
    CU_ASSERT_FALSE(block_head->free);

    free(block);

    CU_ASSERT_TRUE(block_head->free);
}

void test_free_null(void) {
    TEST_SETUP();

    free(NULL);
    CU_ASSERT(1);
}

void test_free_middle_block(void) {
    TEST_SETUP();
    
    void *block1 = malloc(10);
    void *block2 = malloc(20);
    void *block3 = malloc(30);

    block_t *block_head2 = (block_t *)((char *)block2 - sizeof(block_t));

    free(block2);
    
    CU_ASSERT_TRUE(block_head2->free);
    
    block_t *block_head1 = (block_t *)((char *)block1 - sizeof(block_t));
    block_t *block_head3 = (block_t *)((char *)block3 - sizeof(block_t));
    
    CU_ASSERT_EQUAL(block_head1->next, block_head2);
    CU_ASSERT_EQUAL(block_head2->next, block_head3);
    
    free(block1);
    free(block3);
}

void test_free_invalid_pointer(void) {
    TEST_SETUP();
    
    char invalid_mem[16];
    void *invalid_ptr = &invalid_mem[0];
    
    free(invalid_ptr);
    
    void *valid_block = malloc(10);
    CU_ASSERT_PTR_NOT_NULL(valid_block);
    free(valid_block);
}