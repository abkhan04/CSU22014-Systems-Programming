// simple C program that contains a hash table for strings
// David Gregg, November 2023                           

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"


// compute a hash of a string using a seed value, where the result
// falls between zero and range-1
int hash_string(char *string, int range)
{
    int i;
    int hash = 0;
    const int HASH_SEED = 19;

    // simple loop for mixing the input string
    for (i = 0; string[i] != '\0'; i++)
    {
        hash = hash * HASH_SEED + string[i];
    }

    // check for unlikely case that hash is negative
    if (hash < 0)
    {
        hash = -hash;
    }

    // bring the hash within the range 0..range-1
    hash = hash % range;

    //printf("str: \'%s\', hash: %d\n", string, hash);
    return hash;
}

// create a new empty hashtable
struct hashtable * hashtable_new(int size)
{
    struct hashtable *result = malloc(sizeof(struct hashtable));
    result -> table = malloc(sizeof(struct listset *) * size);

    for (int i = 0; i < size; i++)
    {
        result -> table[i] = listset_new();
    }

    result -> size = size;

    return result;
}

// add an item to the hashtable
void hashtable_add(struct hashtable *this, char *item)
{
    int index = hash_string(item, this -> size);

    if (hashtable_lookup(this, item) == 0)
    {
        struct listset *list = this -> table[index];
        listset_add(list, item);
    }
}

// return 1 if item is in hashtable, 0 otherwise
int hashtable_lookup(struct hashtable *this, char *item)
{
    int index = hash_string(item, this -> size);
    struct listset *list = this -> table[index];
    return listset_lookup(list, item);
}

// remove an item from the hash table; if the item is in the table
// multiple times, just remove the first one that we encounter
void hashtable_remove(struct hashtable *this, char *item)
{
    int index = hash_string(item, this -> size);
    if (hashtable_lookup(this, item) == 1)
    {
        struct listset *list = this -> table[index];
        listset_remove(list, item);
    }
}

// print the elements of the hashtable set
void hashtable_print(struct hashtable *this)
{
    for (int i = 0; i < this -> size; i++)
    {
        listset_print(this -> table[i]);
    }
}
