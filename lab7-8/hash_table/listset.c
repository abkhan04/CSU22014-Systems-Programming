#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new()
{
    struct listset *result = malloc(sizeof(struct listset));
    result -> head = NULL;

    return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset *this, char *item)
{
    struct listnode *current_node = this -> head;

    while (current_node != NULL)
    {
        if (strcmp(current_node -> str, item) == 0)
        {
            return 1;
        }

        current_node = current_node -> next;
    }

    return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset *this, char *item)
{
    if (listset_lookup(this, item) == 0)
    {
        struct listnode *new_node = malloc(sizeof(struct listnode));
        new_node -> str = item;
        new_node -> next = this -> head;
        this -> head = new_node;
    }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset *this, char *item)
{
    if (this -> head != NULL)
    {
        if (strcmp(this -> head -> str, item) == 0)
        {
            struct listnode *temp = this -> head;
            this -> head = temp -> next;
            free(temp);
        }
        else
        {
            struct listnode *current_node = this -> head -> next;
            struct listnode *previous_node = this -> head;

            while (current_node != NULL)
            {
                if (strcmp(current_node -> str, item) == 0)
                {
                    struct listnode *temp = current_node;
                    previous_node -> next = current_node -> next;
                    free(temp);
                    break;
                }

                previous_node = current_node;
                current_node = current_node -> next;
            }
        }
    }
}

// place the union of src1 and src2 into dest
void listset_union(struct listset *dest, struct listset *src1, struct listset *src2)
{
    struct listnode *current_node = src1 -> head;

    while (current_node != NULL)
    {
        listset_add(dest, current_node -> str);
        current_node = current_node -> next;
    }

    current_node = src2 -> head;

    while (current_node != NULL)
    {
        listset_add(dest, current_node -> str);
        current_node = current_node -> next;
    }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset *dest, struct listset *src1, struct listset *src2)
{
    struct listnode *current_node = src1 -> head;

    while (current_node != NULL)
    {
        if (listset_lookup(src2, current_node -> str))
        {
            listset_add(dest, current_node -> str);
        }

        current_node = current_node -> next;
    }
}

// return the number of items in the listset
int listset_cardinality(struct listset *this)
{
    struct listnode *current_node = this -> head;
    int count = 0;

    while (current_node != NULL)
    {
        current_node = current_node -> next;
        count++;
    }

    return count;
}

// print the elements of the list set
void listset_print(struct listset *this)
{
    for (struct listnode *p = this -> head; p != NULL; p = p -> next)
    {
        printf("%s, ", p -> str);
    }

    printf("\n");
}
