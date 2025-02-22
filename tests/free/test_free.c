#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "test_free.h"
#include "allocator.h"


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