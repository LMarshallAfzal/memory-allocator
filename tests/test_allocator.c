#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"
#include "utils/test_utils.h"

void test_reuse_block(void) {
    TEST_SETUP();

    void *block1 = malloc(100);
    block_t *block_head1 = (block_t *)((char *)block1 - sizeof(block_t));

    void *block1_address = block1;

    free(block1);

    void *block2 = malloc(100);
    CU_ASSERT_EQUAL(block2, block1_address);

    block_t *block_head2 = (block_t *)((char *)block2 - sizeof(block_t));

    CU_ASSERT_EQUAL(block_head1, block_head2)
    CU_ASSERT_FALSE(block_head2->free);

    free(block2);
}

void test_first_fit_allocation(void) {
    TEST_SETUP();
    
    set_allocation_strategy(FIRST_FIT);
    
    void *block1 = malloc(100);
    void *block2 = malloc(200);
    void *block3 = malloc(50);
    void *block4 = malloc(300);
    
    free(block1);
    free(block3);
    
    void *new_block = malloc(40);
    
    CU_ASSERT_EQUAL(new_block, block1);
    
    free(block2);
    free(block4);
    free(new_block);
}

void test_best_fit_allocation(void) {
    TEST_SETUP();

    set_allocation_strategy(BEST_FIT);

    void *block1 = malloc(100);
    void *block2 = malloc(200);
    void *block3 = malloc(50);
    void *block4 = malloc(300);
    
    free(block1);
    free(block3);

    void *new_block = malloc(40);

    CU_ASSERT_EQUAL(new_block, block3);

    free(block2);
    free(block4);
    free(new_block);
}

void test_worst_fit_allocation(void) {
    TEST_SETUP();

    set_allocation_strategy(WORST_FIT);
    
    void *block1 = malloc(100);
    void *block2 = malloc(200);
    void *block3 = malloc(50);
    void *block4 = malloc(20);
    void *block5 = malloc(300);

    free(block1);
    free(block3);
    free(block5);

    void *new_block = malloc(40);

    CU_ASSERT_EQUAL(new_block, block5);

    free(block2);
    free(block4);
    free(new_block);
}