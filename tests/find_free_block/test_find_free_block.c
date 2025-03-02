#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "allocator.h"
#include "../utils/test_utils.h"

void test_split_block(void) {
    TEST_SETUP();

    void *large_block = malloc(1000);
    CU_ASSERT_PTR_NOT_NULL(large_block);

    free(large_block);

    void *small_block = malloc(100);
    CU_ASSERT_PTR_NOT_NULL(small_block);
    block_t *small_head = (block_t *)((char *)small_block - sizeof(block_t));

    CU_ASSERT_EQUAL(small_head->size, 100);
    CU_ASSERT_PTR_NOT_NULL(small_head->next);
    CU_ASSERT_TRUE(small_head->next->free);

    size_t expected_free_size = 1000 - sizeof(block_t) - 100;
    CU_ASSERT_EQUAL(small_head->next->size, expected_free_size);

    free(small_block);
}

void test_split_large_block(void) {
    TEST_SETUP();
    
    void *large_block = malloc(1000);
    CU_ASSERT_PTR_NOT_NULL(large_block);
    
    free(large_block);
    
    void *small_block = malloc(50);
    
    CU_ASSERT_EQUAL(small_block, large_block);
    
    block_t *small_head = (block_t *)((char *)small_block - sizeof(block_t));
    
    CU_ASSERT_EQUAL(small_head->size, 50);
    CU_ASSERT_PTR_NOT_NULL(small_head->next);
    CU_ASSERT_TRUE(small_head->next->free);
    
    size_t expected_free_size = 1000 - 50 - sizeof(block_t);
    CU_ASSERT_EQUAL(small_head->next->size, expected_free_size);
    
    free(small_block);
}

void test_minimum_split_threshold(void) {
    TEST_SETUP();
    
    void *block = malloc(100);
    CU_ASSERT_PTR_NOT_NULL(block);
    
    free(block);
    
    void *new_block = malloc(96);
    
    // Verify new block uses sames memory space
    CU_ASSERT_EQUAL(new_block, block);
    
    block_t *new_head = (block_t *)((char *)new_block - sizeof(block_t));
    
    if (100 - 96 < sizeof(block_t) + 4) {
        // Should not have been split
        CU_ASSERT_PTR_NULL(new_head->next);
        CU_ASSERT_EQUAL(new_head->size, 100);
    } else {
        // Should have been split
        CU_ASSERT_PTR_NOT_NULL(new_head->next);
        CU_ASSERT_TRUE(new_head->next->free);
    }
    
    free(new_block);
}

void test_coalesce_adjacent_blocks(void) {
    TEST_SETUP();

    void *block1 = malloc(10);
    void *block2 = malloc(20);
    void *block3 = malloc(30);

    free(block1);
    free(block2);

    void *large_block = malloc(35);
    CU_ASSERT_PTR_NOT_NULL(large_block);

    block_t *large_head = (block_t *)((char *)large_block - sizeof(block_t));

    size_t expected_block_size = 10 + sizeof(block_t) + 20;
    CU_ASSERT_EQUAL(large_head->size, expected_block_size);

    free(block3);
}

void test_coalesce_three_blocks(void) {
    TEST_SETUP();

    void *block1 = malloc(100);
    void *block2 = malloc(100);
    void *block3 = malloc(100);
    void *block4 = malloc(100);

    free(block1);
    free(block2);
    free(block3);

    void *large_block = malloc(300);
    CU_ASSERT_PTR_NOT_NULL(large_block);

    block_t *large_head = (block_t *)((char *)large_block - sizeof(block_t));

    size_t expected_block_size = 300;
    CU_ASSERT_EQUAL(large_head->size, expected_block_size);
    
    free(block4);
    free(large_block);
}