#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include "allocator.h" 
#include "test_malloc.h"
#include "test_free.h"
#include "test_allocator.h"
#include "test_find_free_block.h"

int setup(void) {
    head_block = NULL;
    return 0;
}

int teardown(void) {
    block_t *current = head_block;
    block_t *next;
    while (current != NULL) {
        next = current->next;
        current = next;
    }
    head_block = NULL;
    return 0;
}

int main() {

    CU_initialize_registry();

    // Test suite for malloc
    CU_pSuite malloc_suite = CU_add_suite("malloc() Test Suite", setup, teardown);
    CU_add_test(malloc_suite, "test_malloc_basic", test_malloc_basic);
    CU_add_test(malloc_suite, "test_malloc_multiple", test_malloc_multiple);

    // Test suite for free
    CU_pSuite free_suite = CU_add_suite("free() Test Suite", setup, teardown);
    CU_add_test(free_suite, "test_free_basic", test_free_basic);
    CU_add_test(free_suite, "test_free_null", test_free_null);

    // Test suite for find free block
    CU_pSuite find_free_block_suite = CU_add_suite("find_free_block() Test Suite", setup, teardown);
    CU_add_test(find_free_block_suite, "test_split_block", test_split_block);

    // Test suite for allocator
    CU_pSuite allocator_suite = CU_add_suite("Allocator Test Suite", setup, teardown);
    CU_add_test(allocator_suite, "test_reuse_block", test_reuse_block);
    CU_add_test(allocator_suite, "test_coalesce_block", test_coalesce_block);


    CU_console_run_tests();
    int num_failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    return num_failures;
}