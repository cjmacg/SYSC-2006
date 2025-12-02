/* SYSC 2006 - Lab 13 - ADT dictionary/map implemented using a hashtable.
 *
 */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"

/* Helper functions. */

/* The strdup function is not part of the C standard library in C11 and C17, but will
 * be included in C2x. For earlier versions of C, some compilers provide this function 
 * as an extension to the standard library. 
 *
 * If this function causes a compilation/linking error, it's likely because your compiler
 * compiler is configured to use the C2x standard or provides extensions to C11/C17.
 *
 * SOLUTION: Comment out/delete the function. 
 *
 * Create a duplicate of s on the heap and return the pointer to it.
 * Return NULL if space can't be allocated.
 */
/*static char *strdup(char *s)
{
    char *p = malloc(strlen(s) + 1);  // +1 for '\0'
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}
*/
/* Return the hash value for string s. */
static unsigned hash(char *s)
{
    unsigned int hashvalue;

    for (hashvalue = 0; *s != '\0'; s += 1) {
        hashvalue = *s + 31 * hashvalue;
    }
    return hashvalue % TABLESIZE;
}

/* If key is found in the linked list pointed to by head, return a
 * pointer to the entry that contains key; otherwise return NULL.
 */
static entry_t *search(entry_t *head, char *key)
{
    for (entry_t *entry = head; entry != NULL; entry = entry->next) {
        if (strcmp(key, entry->key) == 0) {
            return entry;  // key found
        }
    }
    return NULL;
}

/*-----------------------------------------------------------------*/

/* Allocate a new dictionary on the heap and return a pointer to it.
 * Terminate via assert if the dictionary can't be allocated.
 */
dict_t *make_dictionary(void)
{
    dict_t *hashtable = malloc(sizeof(entry_t *) * TABLESIZE);
    assert(hashtable != NULL);

    // Each slot in the table stores the pointer to a chain
    // (a linked list). Initially, all chains are empty.
    for (int i = 0; i < TABLESIZE; i += 1) {
        hashtable[i] = NULL;
    }
    return hashtable;
}

/* If key is found in dictionary dict, return the value associated with 
 * the key; otherwise return NULL.
 */
char *get(dict_t *dict, char *key)
{
    unsigned hashvalue = hash(key);
    entry_t *entry = search(dict[hashvalue], key);
    if (entry != NULL) {
        return entry->value;  // key found
    }
    return NULL;
}

/* Insert (key, value) in dictionary dict. If key is already in the 
 * dictionary, replace the value currently associated with key.
 * Terminate via assert if memory couldn't be allocated while
 * updating the dictionary.
 */
void put(dict_t *dict, char *key, char *value)
{
    unsigned hashvalue = hash(key);
    entry_t *entry = search(dict[hashvalue], key);
    if (entry == NULL) { 
        // key not found, so add key/value in a new entry in the chain.
        entry = malloc(sizeof(entry_t));
        assert(entry != NULL);
        entry->key = strdup(key);
        assert(entry->key != NULL);

        // Insert the new entry at the front of the linked list.
        entry->next = dict[hashvalue];
        dict[hashvalue] = entry;
    } else {  
        // The key is already in the table, so just replace the
        // current value with the new one.
        free(entry->value);  // Deallocate the current value
    }

    // Put the value associated with the key in the entry.
    entry->value = strdup(value);
    assert(entry->value != NULL);
}


/* Print the dictionary pointed to by dict, using the format:
0: key_0: value_0, key_1: value_1, ...
1: key_0: value_0, key_1: value_1, ...
...
n-1: key_0: value_0, key_1: value_1, ...
*/
void print_dictionary(dict_t *dict)
{
    //methodology
    //dict is an array with buckets, each bucket holds a linked list
    //each linked list is an "entry" which has a next, key and value pair (handles overlapping hashes I think)
    for (int i = 0; i < TABLESIZE; i ++) {
        printf("%d: ", i); //first bucket index printed

        //head pointer for linked list in this bucket.
        entry_t *current = dict[i];

        if (current == NULL) {
            printf("NULL \n");
        }
        else {
            while (current != NULL) {
                //print first entry in linked list in this first bucket
                printf("%s: %s", current->key, current->value);

                //print a comma if we're going to another linked list entry in this bucket
                if (current->next != NULL) {
                    printf(", ");
                }

                //iterate over linked list
                current = current->next;
            }
            printf("\n"); //newline, done with first array index (bucket), next hashvalue
        }

    }
}//end printdictionary


/* If key is in the dictionary, replace its associated value with
* a copy of the string pointed to by value, and return true.
* If key is not in the dictionary, return false to indicate that
* the dictionary has not changed.
* Terminate via assert if memory could not be allocated while
* updating the dictionary.
*/
_Bool replace(dict_t *dict, char *key, char *value)
{
    //use their hashing method to find what it results as for a dict index (bucket index)
    unsigned hashvalue = hash(key);

    //uses the provided comparative search function to find matching entry
    entry_t *entry = search(dict[hashvalue], key);

    if (entry == NULL) {
        return 0; //key not found case
    }

    free(entry->value); // don't need this anymore if key found

    //this entry's value is newly assigned.
    entry->value = strdup(value);

    assert(entry->value != NULL); //make sure that actually worked
    return true; //if it worked and replaced
}




/* Remove all the key/value entries from the dictionary.
* The dictionary will be empty after this call returns.
*/
void clear(dict_t *dict)
{
    //iterate over full size of hashtable
    for (int i = 0; i < TABLESIZE; i += 1) {

        //start on first entry on table
        entry_t *current = dict[i];


        while (current != NULL) {
            //gotta remember the next one's address before freeing the current
            entry_t * next_entry = current->next;

            //free inside to out
            free(current->key);
            free(current->value);
            free(current);

            current = next_entry;

        }
        dict[i] = NULL; //that bucket is empty, so null pointer, on to the next.
    }

}