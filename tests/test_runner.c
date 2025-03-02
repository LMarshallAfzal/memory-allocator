#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include "allocator.h" 
#include "test_malloc.h"
#include "test_free.h"
#include "test_allocator.h"
#include "test_find_free_block.h"

int suite_setup(void) {
    head_block = NULL;
    return 0;
}

int suite_teardown(void) {
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
    CU_pSuite malloc_suite = CU_add_suite("malloc() Test Suite", suite_setup, suite_teardown);
    CU_add_test(malloc_suite, "test_malloc_zero_size", test_malloc_zero_size);
    CU_add_test(malloc_suite, "test_malloc_basic", test_malloc_basic);
    CU_add_test(malloc_suite, "test_malloc_multiple_allocations", test_malloc_multiple_allocations);
    CU_add_test(malloc_suite, "test_malloc_large_allocation", test_malloc_large_allocation);

    // Test suite for free
    CU_pSuite free_suite = CU_add_suite("free() Test Suite", suite_setup, suite_teardown);
    CU_add_test(free_suite, "test_free_basic", test_free_basic);
    CU_add_test(free_suite, "test_free_null", test_free_null);
    CU_add_test(free_suite, "test_free_middle_block", test_free_middle_block);
    CU_add_test(free_suite, "test_free_invalid_pointer", test_free_invalid_pointer);

    // Test suite for find free block
    CU_pSuite find_free_block_suite = CU_add_suite("find_free_block() Test Suite", suite_setup, suite_teardown);
    CU_add_test(find_free_block_suite, "test_split_block", test_split_block);
    CU_add_test(find_free_block_suite, "test_split_large_block", test_split_large_block);
    CU_add_test(find_free_block_suite, "test_minimum_split_threshold", test_minimum_split_threshold);
    CU_add_test(find_free_block_suite, "test_coalesce_adjacent_blocks", test_coalesce_adjacent_blocks);
    CU_add_test(find_free_block_suite, "test_coalesce_three_blocks", test_coalesce_three_blocks);

    // Test suite for allocator
    CU_pSuite allocator_suite = CU_add_suite("Allocator Test Suite", suite_setup, suite_teardown);
    CU_add_test(allocator_suite, "test_reuse_block", test_reuse_block);
    CU_add_test(allocator_suite, "test_first_fit_allocation", test_first_fit_allocation);
    CU_add_test(allocator_suite, "test_best_fit_allocation", test_best_fit_allocation);
    CU_add_test(allocator_suite, "test_worst_fit_allocation", test_worst_fit_allocation);


    CU_console_run_tests();
    int num_failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    return num_failures;
}