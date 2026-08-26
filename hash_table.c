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
typedef struct hash_table
{
    node_t ** pp_table;    // array of pointers to node_t chains
    free_f    p_free;      // frees data stored in the hash table
    uint32_t  num_buckets; // number of buckets used in the hash table
    uint32_t  num_nodes;   // number of nodes currently in the hash table
} hash_table_t;

// TODO: static function prototypes here
static uint32_t hash_key(char * p_key);

hash_table_t * hash_table_init(uint32_t size, free_f p_free)
{
	hash_table_t * new_hash_table = NULL;

	if (0 == size)
	{
		goto END;
	}

	new_hash_table = calloc(1, sizeof(* new_hash_table));

	if (NULL == new_hash_table)
	{
		goto END;
	}

	new_hash_table->pp_table = calloc(size, sizeof(* new_hash_table->pp_table));

	if (NULL == new_hash_table->pp_table)
	{
		free(new_hash_table);
		new_hash_table = NULL;
		goto END;
	}

	new_hash_table->p_free = p_free;
	new_hash_table->num_buckets = size;
	new_hash_table->num_nodes = 0;

END:
	return new_hash_table;
}

int hash_table_add(hash_table_t * p_table, void * p_data, char * p_key)
{
	int SUCCESS = 1;

	if ((NULL == p_table) ||
		(NULL == p_data) ||
		(NULL == p_key))
	{
		goto END;
	}

	uint32_t p_key_val = hash_key(p_key);

	uint32_t bucket_index = p_key_val % p_table->num_buckets;

	if (NULL == new_node)
	{
		goto END;
	}

	node_t * new_node = calloc(1, sizeof(* new_node));

	if (NULL == new_node)
	{
		goto END;
	}

	new_node->p_data = p_data;
	new_node->p_key = p_key;

	new_node->p_next = p_table->pp_table[bucket_index];
	p_table->pp_table[bucket_index] = new_node;

	p_table->num_nodes++;

	SUCCESS = 0;

END:
	return SUCCESS;
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
static uint32_t hash_key(char * p_key)
{
	char * p_end = NULL;
	unsigned long long result = 0ULL;

	if (NULL == p_key)
	{
		goto END;
	}
	
	result = strtoul(p_key, &p_end, 10);
	if ('\0' == * p_end)
	{
		result = 0ULL;
		goto END;
	}

END:
	return result;

}

// end of hash_table.c
