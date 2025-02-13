#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include "allocator.h" 
#include "test_allocator.h"


int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Allocator Suite", NULL, NULL);

    // Add your tests to the suite (from test_allocator.c)
    CU_add_test(suite, "test_malloc_basic", test_malloc_basic);
    CU_add_test(suite, "test_malloc_multiple", test_malloc_multiple);
    CU_add_test(suite, "test_free_basic", test_free_basic);
    CU_add_test(suite, "test_free_null", test_free_null);
    CU_add_test(suite, "test_reuse_block", test_reuse_block);


    CU_console_run_tests();
    int num_failures = CU_get_number_of_failures();
    CU_cleanup_registry();

    return num_failures;
}