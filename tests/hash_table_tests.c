#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

void test_init_destroy()
{
    hash_table_t * p_table = hash_table_init(10, NULL);
    CU_ASSERT_PTR_NOT_NULL(p_table);
    hash_table_destroy(&p_table);
    CU_ASSERT_PTR_NULL(p_table);

    hash_table_t * p_table2 = hash_table_init(10, free);
    CU_ASSERT_PTR_NOT_NULL(p_table2);
    hash_table_destroy(&p_table2);
    CU_ASSERT_PTR_NULL(p_table2);

    hash_table_t * p_table3 = hash_table_init(0, NULL);
    CU_ASSERT_PTR_NULL(p_table3);
    hash_table_destroy(&p_table3);
    CU_ASSERT_PTR_NULL(p_table3);

    hash_table_t * p_table4 = hash_table_init(0, free);
    CU_ASSERT_PTR_NULL(p_table4);
}

void test_add_remove()
{
    hash_table_t * p_table = hash_table_init(4, NULL);

    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(NULL, NULL, "string"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(p_table, "data", NULL))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str1", "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str2", "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str3", "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str4", "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str5", "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string5"))

    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string1"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string2"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string3"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string4"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string1"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(p_table, NULL, "string1"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(p_table, "str1", "string1"))

    hash_table_remove(p_table, "string1");
    hash_table_destroy(&p_table);
}

void test_add_remove_one_bucket()
{
    hash_table_t * p_table = hash_table_init(1, NULL);

    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(NULL, NULL, "string"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(p_table, NULL, NULL))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str1", "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str2", "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str3", "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str4", "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, "str5", "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string1"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string2"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string3"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string4"))
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_remove(p_table, "string5"))

    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string1"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string2"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string3"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string4"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_remove(p_table, "string5"))

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_add(p_table, NULL, "string1"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(p_table, NULL, "string1"))
    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_add(p_table, "str1", "string1"))

    hash_table_remove(p_table, "string1");
    hash_table_destroy(&p_table);
}

void test_lookup()
{
    hash_table_t * p_table = hash_table_init(10, free);
    hash_table_add(p_table, NULL, "string");

    CU_ASSERT_PTR_NULL(hash_table_lookup(NULL, "string"));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, NULL));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string"));

    hash_table_add(p_table, strdup("str1"), "string1");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string1"));

    hash_table_add(p_table, strdup("str2"), "string2");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string2"));

    hash_table_add(p_table, strdup("str3"), "string3");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string3"));

    hash_table_add(p_table, strdup("str4"), "string4");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string4"));

    hash_table_add(p_table, strdup("str5"), "string5");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string5"));

    hash_table_remove(p_table, "string1");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string1"));

    hash_table_remove(p_table, "string2");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string2"));

    hash_table_remove(p_table, "string3");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string3"));

    hash_table_remove(p_table, "string4");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string4"));

    hash_table_remove(p_table, "string5");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string5"));

    hash_table_destroy(&p_table);
}

void test_lookup_values()
{
    hash_table_t * p_table = hash_table_init(10, free);
    char *         p_str   = NULL;

    hash_table_add(p_table, strdup("str1"), "string1");
    p_str = hash_table_lookup(p_table, "string1");
    CU_ASSERT_EQUAL(EXIT_SUCCESS, strcmp(p_str, "str1"));

    hash_table_add(p_table, strdup("str2"), "string2");
    p_str = hash_table_lookup(p_table, "string2");
    CU_ASSERT_EQUAL(EXIT_SUCCESS, strcmp(p_str, "str2"));

    hash_table_add(p_table, strdup("str3"), "string3");
    p_str = hash_table_lookup(p_table, "string3");
    CU_ASSERT_EQUAL(EXIT_SUCCESS, strcmp(p_str, "str3"));

    hash_table_add(p_table, strdup("str4"), "string4");
    p_str = hash_table_lookup(p_table, "string4");
    CU_ASSERT_EQUAL(EXIT_SUCCESS, strcmp(p_str, "str4"));

    hash_table_add(p_table, strdup("str5"), "string5");
    p_str = hash_table_lookup(p_table, "string5");
    CU_ASSERT_EQUAL(EXIT_SUCCESS, strcmp(p_str, "str5"));

    hash_table_remove(p_table, "string1");
    hash_table_remove(p_table, "string2");
    hash_table_remove(p_table, "string3");
    hash_table_remove(p_table, "string4");
    hash_table_remove(p_table, "string5");

    hash_table_destroy(&p_table);
}

void test_lookup_one_bucket()
{
    hash_table_t * p_table = hash_table_init(1, free);
    hash_table_add(p_table, NULL, "string");

    CU_ASSERT_PTR_NULL(hash_table_lookup(NULL, "string"));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, NULL));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string"));

    hash_table_add(p_table, strdup("str1"), "string1");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string1"));

    hash_table_add(p_table, strdup("str2"), "string2");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string2"));

    hash_table_add(p_table, strdup("str3"), "string3");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string3"));

    hash_table_add(p_table, strdup("str4"), "string4");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string4"));

    hash_table_add(p_table, strdup("str5"), "string5");
    CU_ASSERT_PTR_NOT_NULL(hash_table_lookup(p_table, "string5"));

    hash_table_remove(p_table, "string1");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string1"));

    hash_table_remove(p_table, "string2");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string2"));

    hash_table_remove(p_table, "string3");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string3"));

    hash_table_remove(p_table, "string4");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string4"));

    hash_table_remove(p_table, "string5");
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string5"));

    hash_table_destroy(&p_table);
}

void test_destroy_nonempty()
{
    hash_table_t * p_table = hash_table_init(10, free);

    hash_table_add(p_table, strdup("str1"), "string1");
    hash_table_add(p_table, strdup("str2"), "string2");
    hash_table_add(p_table, strdup("str3"), "string3");
    hash_table_add(p_table, strdup("str4"), "string4");
    hash_table_add(p_table, strdup("str5"), "string5");

    hash_table_destroy(&p_table);
}

void test_destroy_nonempty_one_bucket()
{
    hash_table_t * p_table = hash_table_init(1, free);

    hash_table_add(p_table, strdup("str1"), "string1");
    hash_table_add(p_table, strdup("str2"), "string2");
    hash_table_add(p_table, strdup("str3"), "string3");
    hash_table_add(p_table, strdup("str4"), "string4");
    hash_table_add(p_table, strdup("str5"), "string5");

    hash_table_destroy(&p_table);
}

void test_clear()
{
    hash_table_t * p_table = hash_table_init(10, NULL);
    hash_table_add(p_table, NULL, "string");
    hash_table_add(p_table, NULL, "string2");

    CU_ASSERT_EQUAL(EXIT_FAILURE, hash_table_clear(NULL));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_clear(p_table));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string"));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table, "string2"));

    hash_table_destroy(&p_table);

    hash_table_t * p_table2 = hash_table_init(7, free);
    char *         p_str1   = strdup("str");
    char *         p_str2   = strdup("str2");
    hash_table_add(p_table2, p_str1, "string");
    hash_table_add(p_table2, p_str2, "string2");

    CU_ASSERT_EQUAL(EXIT_SUCCESS, hash_table_clear(p_table2));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table2, "string"));
    CU_ASSERT_PTR_NULL(hash_table_lookup(p_table2, "string2"));

    hash_table_destroy(&p_table2);
}

int main(void)
{
    CU_TestInfo suite1_tests[] = {
        { "Testing initialization and destruction:", test_init_destroy },
        { "Testing addition and removal:", test_add_remove },
        { "Testing addition and removal in one bucket:",
          test_add_remove_one_bucket },
        { "Testing look up pointers:", test_lookup },
        { "Testing look up values:", test_lookup_values },
        { "Testing look up in one bucket:", test_lookup_one_bucket },
        { "Testing destroy on non empty table:", test_destroy_nonempty },
        { "Testing destroy on non empty table in one bucket:",
          test_destroy_nonempty_one_bucket },
        { "Testing clear:", test_clear },
        CU_TEST_INFO_NULL
    };

    CU_SuiteInfo suites[] = {
        { "Suite-1:", NULL, NULL, .pTests = suite1_tests }, CU_SUITE_INFO_NULL
    };

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    if (0 != CU_register_suites(suites))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    int num_failed = CU_get_number_of_failures();
    CU_cleanup_registry();
    puts("\n");
    return num_failed;
}

// end of hash_table_tests.c
