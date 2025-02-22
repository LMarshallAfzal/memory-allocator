#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include "allocator.h" 
#include "test_malloc.h"
#include "test_free.h"
#include "test_allocator.h"



int main() {
    CU_initialize_registry();

    // Test suite for malloc
    CU_pSuite malloc_suite = CU_add_suite("Malloc Test Suite", NULL, NULL);
    CU_add_test(malloc_suite, "test_malloc_basic", test_malloc_basic);
    CU_add_test(malloc_suite, "test_malloc_multiple", test_malloc_multiple);

    // Test suite for free
    CU_pSuite free_suite = CU_add_suite("Free Test Suite", NULL, NULL);
    CU_add_test(free_suite, "test_free_basic", test_free_basic);
    CU_add_test(free_suite, "test_free_null", test_free_null);

    // Test suite for allocator
    CU_pSuite allocator_suite = CU_add_suite("Free Test Suite", NULL, NULL);
    CU_add_test(allocator_suite, "test_reuse_block", test_reuse_block);


    CU_console_run_tests();
    int num_failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    return num_failures;
}