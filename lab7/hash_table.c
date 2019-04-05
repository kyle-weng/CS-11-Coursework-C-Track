/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"

/*** Hash function. ***/

int hash(char *s)
{
    int i;
    int sumHash = 0;
    int len = strlen(s);
    for (i = 0; i < len; i++) {
        sumHash += (int)s[i];
    }
    return sumHash % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *n = malloc(sizeof (node));
    n->key = key;
    n->value = value;
    n->next = NULL;
    return n;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *tmp;
    while (list != NULL) {
        tmp = list;
        free(list->key);
        list = list->next;
        free(tmp);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    int i;
    hash_table *table = (hash_table *) malloc(sizeof (hash_table));
    node **slot = (node **) malloc(NSLOTS * sizeof(node *));
    table->slot = slot;

    /* initialize each node in the slot array to NULL */
    for (i = 0; i < NSLOTS; i++) {
        slot[i] = NULL;
    }
    return table;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    /* free hash table, slot array, each slot in the array */
    int i;
    for (i = 0; i < NSLOTS; i++) {
        free_list(ht->slot[i]);
    }
    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    int hashedKey;
    node *list;

    hashedKey = hash(key);
    list = ht->slot[hashedKey];
    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            return list->value;
        }
        list = list->next;
    }
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    int hashedKey;
    node *list;
    node *newNode;

    hashedKey = hash(key);
    list = ht->slot[hashedKey];
    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            list->value = value;
            free(key);
            return;
        }
        list = list->next;
    }
    newNode = create_node(key, value);
    newNode->next = ht->slot[hashedKey];
    ht->slot[hashedKey] = newNode;
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node *currentNode;

    for (i = 0; i < NSLOTS; i++) {
        currentNode = ht->slot[i];
        while (currentNode != NULL) {
            printf("%s %d\n", currentNode->key, currentNode->value);
            currentNode = currentNode->next;
        }
    }
}
