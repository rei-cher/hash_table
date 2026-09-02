/**
 * Hash table database.
 * Duplicate keys should be rejected.
 * Chaining (buckets) should be used to handle collisions.
 * If no free_f function is provided assume data is stack allocated.
 * Allow keys to be inserted without any associated data.
 */

#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define RANDOM_PREDEFINED_NUMBER 41

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
};

// TODO: static function prototypes here
static uint32_t hash_key(char * p_key, uint32_t size);

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
	node_t * p_current = NULL;

	if ((NULL == p_table) ||
		(NULL == p_key))
	{
		goto END;
	}

	uint32_t key_val = hash_key(p_key, p_table->num_buckets);

	p_current = p_table->pp_table[key_val];

	while (NULL != p_current)
	{
		if (0 == strcmp(p_current->p_key, p_key))
		{
			goto END;
		}

		p_current = p_current->p_next;
	}

	node_t * p_new_node = calloc(1, sizeof(* p_new_node));

	if (NULL == p_new_node)
	{
		goto END;
	}

	p_new_node->p_data = p_data;
	p_new_node->p_key = p_key;

	p_new_node->p_next = p_table->pp_table[key_val];
	p_table->pp_table[key_val] = p_new_node;

	p_table->num_nodes++;

	SUCCESS = 0;

END:
	return SUCCESS;
}

void * hash_table_lookup(hash_table_t * p_table, char * p_key)
{
	void * result = NULL;

	if ((NULL == p_table) ||
		(NULL == p_key))
	{
		goto END;
	}

	uint32_t key_val = hash_key(p_key, p_table->num_buckets);

	node_t * p_current = p_table->pp_table[key_val];
	
	while (NULL != p_current)
	{
		if (0 == strcmp(p_current->p_key, p_key))
		{
			result = p_current->p_data;
			goto END;
		}

		p_current = p_current->p_next;
	}

END:
	return result;
}

int hash_table_remove(hash_table_t * p_table, char * p_key)
{
	int SUCCESS = 1;
	node_t * p_prev = NULL;

	if ((NULL == p_table) ||
		(NULL == p_key))
	{
		goto END;
	}

	uint32_t key_val = hash_key(p_key, p_table->num_buckets);

	node_t * p_current = p_table->pp_table[key_val];

	while (NULL != p_current)
	{
		if (0 != strcmp(p_current->p_key, p_key))
		{
			p_prev = p_current;
			p_current = p_current->p_next;
			continue;
		}

		if (NULL == p_prev)
		{
			p_table->pp_table[key_val] = p_current->p_next;
		}

		if (NULL != p_prev)
		{
			p_prev->p_next = p_current->p_next;
		}

		if ((NULL != p_table->p_free) &&
			(NULL != p_current->p_data))
		{
			p_table->p_free(p_current->p_data);
		}

		free(p_current);
		p_current = NULL;

		p_table->num_nodes--;
		SUCCESS = 0;
		
		goto END;
	}


END:
	return SUCCESS;
}

int hash_table_clear(hash_table_t * p_table)
{
	int SUCCESS = 1;
	int index = 0;

	if (NULL == p_table)
	{
		goto END;
	}

	for(;index < p_table->num_buckets; index++)
	{
		p_table->p_free(p_table->pp_table[index]);
	}

	SUCCESS = 0;

END:
	return SUCCESS;
}

void hash_table_destroy(hash_table_t ** pp_table)
{
	if ((NULL == * pp_table) ||
		(NULL == pp_table))
	{
		goto END;
	}

	hash_table_clear(* pp_table);

	if (NULL != (* pp_table)->pp_table)
	{
		free((* pp_table)->pp_table);
		(* pp_table)->pp_table = NULL;
	}

	free(*pp_table);
	* pp_table = NULL;
	
END:
	return;

}

// TODO: static function definitions here
static uint32_t hash_key(char * p_key, uint32_t size)
{
	unsigned long long result = 0ULL;
	unsigned int index = 0;

	if (NULL == p_key)
	{
		goto END;
	}
	
	unsigned int key_len = strlen(p_key);

	for (index; index < key_len; index++)
	{
		result = result * RANDOM_PREDEFINED_NUMBER + p_key[index];
	}

	result = result % size;

END:
	return result;
}

// end of hash_table.c
