#include "bitset.h"

// include the standard library header files that we use in this
// program, which are denoted by angle brackets < >
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// define constant dummy values to avoid compiler warnings
static const int dummy_integer_value = -99;
static struct bitset *dummy_pointer_value = NULL;

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size)
{
    struct bitset *result = malloc(sizeof(struct bitset));
    result -> universe_size = size;
    result -> size_in_words = ceil(size / 64);
    result -> bits = malloc(sizeof(uint64_t) * (result -> size_in_words));
    // results  -> bits = calloc(result -> size_in_words, sizeof(uint64_t));
    // sets memory to zero instead of the memory containing arbitrary garbage

    for (int i = 0; i < result -> size_in_words; i++)
    {
        result -> bits[i] = 0;
    }
    
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset *this)
{
    return this -> universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset *this)
{
    int count = 0;

    for (int i = 0; i < this -> size_in_words; i++)
    {
        uint64_t mask = 1ULL;

        for (int j = 0; j < 64; j++)
        {
            if (this -> bits[i] & mask)
            {
                count++;
            }
            
            mask = mask << 1ULL;
        }
    }

    return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset *this, int item)
{
    if (item < this -> universe_size)
    {
        int index = item / 64;
        int shift = item - (index * 64);
        uint64_t mask = 1ULL << shift;

        return ((this -> bits[index] & mask) != 0);
    }
    
    return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset *this, int item)
{
    if (item < this -> universe_size)
    {
        int index = item / 64;
        int shift = item - (index * 64);
        uint64_t mask = 1ULL << shift;

        this -> bits[index] = this -> bits[index] | mask;
    }
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset *this, int item)
{
    if (item < this -> universe_size)
    {
        int index = item / 64;
        int shift = item - (index * 64);
        uint64_t mask = 1ULL << shift;

        this -> bits[index] = this -> bits[index] ^ mask;
    }
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset *dest, struct bitset *src1, struct bitset *src2)
{
    if ((dest != NULL) && (src1 != NULL) && (src2 != NULL) && (dest -> universe_size == src1 -> universe_size) && (src1 -> universe_size == src2 -> universe_size))
    {
        for (int i = 0; i < dest -> size_in_words; i++)
        {
            dest -> bits[i] = (src1 -> bits[i]) | (src2 -> bits[i]);
        }
    }
    else
    {
        dest = NULL;
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset *dest, struct bitset *src1, struct bitset *src2)
{
    if ((dest != NULL) && (src1 != NULL) && (src2 != NULL) && (dest -> universe_size == src1 -> universe_size) && (src1 -> universe_size == src2 -> universe_size))
    {
        for (int i = 0; i < dest -> size_in_words; i++)
        {
            dest -> bits[i] = (src1 -> bits[i]) & (src2 -> bits[i]);
        }
    }
    else
    {
        dest = NULL;
    }
}
