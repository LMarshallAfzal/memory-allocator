#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

void test_reuse_block(void) {
    void *block1 = malloc(5);
    free(block1);
    void *block2 = malloc(5);

    CU_ASSERT_PTR_EQUAL(block1, block2);
}