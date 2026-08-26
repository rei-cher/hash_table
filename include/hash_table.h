/**
 * Hash table database header
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>

/**
 * @brief A function pointer to a user defined function for freeing data stored
 *        in the hash table.
 */
typedef void (*free_f)(void *);

typedef struct hash_table hash_table_t;

/**
 * @brief initializes hash table
 *
 * @param size number of buckets in the hash table
 * @param p_free a function to free data stored in the hash table
 *
 * @return pointer to a hash table, else NULL
 * @note a size of 0 should return NULL
 */
hash_table_t * hash_table_init(uint32_t size, free_f p_free);

/**
 * @brief adds an item to the hash table
 *
 * @param p_table pointer to the hash table
 * @param p_data data to be stored for that key
 * @param p_key key associated with the data
 *
 * @return 0 on success, 1 if key already exists or on error
 */
int hash_table_add(hash_table_t * p_table, void * p_data, char * p_key);

/**
 * @brief looks up an item in the hash table by key
 *
 * @param p_table pointer to the hash table
 * @param p_key key to search for
 *
 * @return pointer to the data at given key, else NULL
 */
void * hash_table_lookup(hash_table_t * p_table, char * p_key);

/**
 * @brief removes an item from the hash table
 *
 * @param p_table pointer to the hash table
 * @param p_key key to be removed
 *
 * @return 0 on success, else 1
 */
int hash_table_remove(hash_table_t * p_table, char * p_key);

/**
 * @brief clears all data from the hash table
 *
 * @param p_table pointer to the hash table
 *
 * @return 0 on success, else 1
 */
int hash_table_clear(hash_table_t * p_table);

/**
 * @brief destroys hash table
 *
 * @param pp_table the address of the hash table to be destroyed
 */
void hash_table_destroy(hash_table_t ** pp_table);

#endif

// end of hash_table.h
