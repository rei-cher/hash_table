# YOU SHOULD NOT PUSH ANY MODIFICATION TO THE FILES IN THIS DIRECTORY

- If you identify a problem with any of the tests in this directory, make an issue on your repo.

## Hash_table_tests.c
- If you remove `-fsanitize=address` from your compilation flags. You can run the entire test suite in valgrind as well to make sure that you are not leaking any memory.

Here is a breakdown of the tests in this file.

### test_init_destroy()
This test validates the initialization and destruction functions.

- p_table should be successfully created when the init function is given 10 and NULL. p_table is checked to be non NULL. p_table should then be successfully destroyed. p_table is then checked to be NULL.
- p_table2 should be successfully created when the init function is given 10 and free(). p_table2 is checked to be non NULL. p_table2 should then be successfully destroyed. p_table2 is then checked to be NULL.
- p_table3 should not be created when the init function is given 0 and NULL. p_table3 is checked to be NULL. The address of p_table3 is then passed to the destroy function. Nothing should happen, but the program should not crash or leak memory either.
- p_table4 should not be created when the init function is given 0 and free.

Note: Since the add or remove functions have not yet been validated, the destroy function when there is still data in the hash table will be validated later.

### test_add_remove()
This test validates the add and remove functions. To start, a valid hash table is created without a free function. 

#### Null Checks
- The first test makes sure that passing NULL as the hash table pointer to the add function returns `EXIT_FAILURE`.
- The second test makes sure that passing NULL as the key pointer to the add function returns `EXIT_FAILURE`.
- The third test makes sure that passing NULL as the value pointer to the add function returns `EXIT_SUCCESS`.

#### Add and Remove Keys without Data
- The next 10 checks make sure that 5 strings can be added without any data associated with them and then successfully removed.

#### Add and Remove Keys with Data
- The next 10 checks make sure that 5 strings can be added with data and then successfully removed.

#### Remove Keys that don't Exists
- The next 5 checks make sure that removing 5 strings that don't exist in the hash table results in `EXIT_FAILURE` each time.

#### Add Duplicate Keys
- The last 3 checks make sure that after key "string1" is successfully added the first time with NULL as the data, that key "string1" can't be added a second time with or without any data associated with it.

The last entry in the hash table is remove and then the hash table is destroyed.

### test_add_remove_one_bucket()
This test repeats the previous add and remove tests, but at the edge case where only one bucket is present.

### test_lookup()
This test validates the look up function. To start, a valid hash table is created with key "string" and no data for that key.

#### Null Returns
- The first test validates that given NULL for the hash table pointer a NULL is returned on lookup.
- The second test validates that given NULL for the key pointer a NULL is returned on lookup.
- The third test validates that if NULL is stored as the data for key "string" that a NULL is returned on lookup.

#### Valid Lookups
- The next 5 tests validate that after a key is added to the hash table with a non NULL data, then lookup returns a valid pointer to the data.
- The next 5 tests validate that after those same keys are removed from the hash table, then their lookups now return NULL.

The hash table is then destroyed.

### test_lookup_values()
The valid lookups from the previous test are repeated to make sure not only that the pointers exist, but that they actually reference the correct strings. The values are then removed from the table before the hash table is destroyed.

Note: strcmp() returns 0 if the strings are equal.

### test_lookup_one_bucket()
This test repeats the lookup tests, but at the edge case where only one bucket is present.

### test_destroy_nonempty()
This test validates that destroy can be called on a hash table that still has values in it.

### test_destroy_nonempty_one_bucket()
This test repeats the last test, but with one bucket.

### test_clear()
This test validates the clear function. 

#### Stack Allocated
To start, a valid hash table is created with key "string" and key "string2" with no data associated with either key.

- The first test validates that given NULL for the hash table pointer, clear returns 1.
- The second test validates that given a valid pointer for a hash table, clear returns 0.
- The next 2 tests validate that after the hash table has been cleared, that key "string" and key "string2" are no longer in the hash table.

The hash table is then destroyed.

#### Heap Allocated
To start, a valid hash table is create. Key "string" with heap allocated "str" is added to the table. Key "string2" with heap allocated "str2" is also added to the table. The hash table is then cleared.

- The next 2 tests validate that key "string" with value "str" and key "string2" with value "str2" are no longer in the hash table.
