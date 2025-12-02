#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__
/* SYSC 2006 - Lab 13 - ADT dictionary/map implemented using a hashtable.
 *
 */

/* A dictionary uses a hash table as the underlying data structure.
 * The hash table is a dynamically allocated array, and each array
 * element is a pointer to the head node of a singly-linked list
 * of entry_t structures. Each entry stores one key/value pair.
 */

#define TABLESIZE 11

typedef struct entry {
    struct entry *next;  // next entry in the linked list
    char *key;
    char *value;         // value associated with the key
} entry_t;

/* A variable of type *dict_t is a pointer to a dictionary;
 * that is, a pointer to the first element in hash table.
 */
typedef entry_t *dict_t;

dict_t *make_dictionary(void);
char *get(dict_t *dict, char *key);
void put(dict_t *dict, char *key, char *value);

void print_dictionary(dict_t *dict);

_Bool replace(dict_t *dict, char *key, char *value);
void clear(dict_t *dict);

#endif
