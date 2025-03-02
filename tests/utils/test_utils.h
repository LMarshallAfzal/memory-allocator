#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <CUnit/CUnit.h>
#include "allocator.h"

void test_setup(void);

#define TEST_SETUP() test_setup()

#endif