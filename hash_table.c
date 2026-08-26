/**
 * Hash table database.
 * Duplicate keys should be rejected.
 * Chaining (buckets) should be used to handle collisions.
 * If no free_f function is provided assume data is stack allocated.
 * Allow keys to be inserted without any associated data.
 */

#include <stdlib.h>

#include "hash_table.h"

// struct that holds a key data pair and a pointer to the next node in the chain
typedef struct node_t
{
    char *          p_key;  // pointer to the saved key string
    void *          p_data; // pointer to the saved data
    struct node_t * p_next; // pointer to the next node_t
} node_t;

// struct that contains all of the hash table elements
struct hash_table
{
    node_t ** pp_table;    // array of pointers to node_t chains
    free_f    p_free;      // frees data stored in the hash table
    uint32_t  num_buckets; // number of buckets used in the hash table
    uint32_t  num_nodes;   // number of nodes currently in the hash table
};

// TODO: static function prototypes here

hash_table_t * hash_table_init(uint32_t size, free_f p_free)
{
    (void)size;
    (void)p_free;
    return NULL;
}

int hash_table_add(hash_table_t * p_table, void * p_data, char * p_key)
{
    (void)p_table;
    (void)p_data;
    (void)p_key;
    return EXIT_FAILURE;
}

void * hash_table_lookup(hash_table_t * p_table, char * p_key)
{
    (void)p_table;
    (void)p_key;
    return NULL;
}

int hash_table_remove(hash_table_t * p_table, char * p_key)
{
    (void)p_table;
    (void)p_key;
    return EXIT_FAILURE;
}

int hash_table_clear(hash_table_t * p_table)
{
    (void)p_table;
    return EXIT_FAILURE;
}

void hash_table_destroy(hash_table_t ** pp_table)
{
    (void)pp_table;
}

// TODO: static function definitions here

// end of hash_table.c
