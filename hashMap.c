/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}


/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    struct HashLink *temp, *nextL;
  
    //loop until end of table, checking each bucket for a linked list
    for (int i = 0; i < map->capacity; i++)
    {
        //set temp to the very beginning of the table
        temp = map->table[i];
        //loop until we reach the end of the links
        while (temp != NULL)
        {
            //set next link to the next
            nextL = temp->next;
            hashLinkDelete(temp);
            temp = nextL;
        } //end while

    }// end for

    free(map->table);
    map->size = 0;
    //map->capacity = 0;

} //end function

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    int index = HASH_FUNCTION(key) % map->capacity;
    //from the lectures, check for negative index
    if (index < 0)
    {
        index += map->capacity;
    }
    //set pointer to our current index
    struct HashLink *match = map->table[index];
    //loop through the links
    while (match != NULL)
    {
        //0 for strcmp means value is the same, also we are using strings as keys
        if(strcmp(match->key, key) == 0) {
            return &(match->value); //returns address of matched value
        }
        else {
            match = match->next;
        }
    } //end while
    //returns NULL if no link with that key is found
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{	
    // FIXME: implement
    struct HashMap *newHashMap = hashMapNew(capacity);
    struct HashLink *temp;
 
 
    for (int i = 0; i < map->capacity; i++)
    {
        temp = map->table[i];
        while (temp != 0)
        {
        hashMapPut(newHashMap, temp->key, temp->value);
        temp = temp->next;
        }
    }

    //free old table
    hashMapCleanUp(map);

    map->table = newHashMap->table;
    map->size = newHashMap->size;
    map->capacity = newHashMap->capacity;

    newHashMap->table = NULL;
    free(newHashMap);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    //takes key and finds what index the key should be at
    int index = HASH_FUNCTION(key) % map->capacity;
    if (index < 0)
        index += map->capacity;

    struct HashLink *match = map->table[index]; //point match to the found index
    struct HashLink *prev = NULL;

    //no link found, create new
    if (match == NULL)
    {
        map->table[index] = hashLinkNew(key, value, NULL);
        map->size++;
    }
    else
    {
        //link is found, loop through to the end
        while(match != NULL)
        {
            if(strcmp(match->key, key) == 0)
            {
                match->value = value;
                return;
            }

            prev = match;
            match = match->next;
        } //end hwile

        if (match == NULL)
        {
            prev->next = hashLinkNew(key, value, NULL); //new link at end of the links
            map->size++;
        }
    } //end else

    //check load factor after addition
    if(hashMapTableLoad(map) > MAX_TABLE_LOAD)
    {
        resizeTable(map, map->capacity * 2);
    } 
    
}//end if // end functin
/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    int index = HASH_FUNCTION(key) % map->capacity;
    
    if(index < 0)
    {
        index += map->capacity;
    }
    
    struct HashLink* match = map->table[index];
    struct HashLink* linkPrevious = NULL;
    
    if(match != 0)
    {
        if(strcmp(match->key, key) == 0)
        {
            map->table[index] = map->table[index]->next;
            hashLinkDelete(match);
            map->size--;
            
        }
        
        else
        {
            linkPrevious = match;
            match = match->next;
            while(match != NULL)
            {
                if(strcmp(match->key, key) == 0)
                {
                    linkPrevious->next = match->next;
                    hashLinkDelete(match);
                    map->size--;
                }
                
                linkPrevious = match;
                match = match->next;
            }  //end while
        }//end else
    }//end if
}//end func

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    if (hashMapGet(map, key) != NULL)
    {
        return 1;
    }
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    int empty = 0;

    for (int i = 0; i < map->capacity; i++)
    {
        if (map->table[i] == 0)
        {
            empty++;
        }
    }

    return empty;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    //from lectures, our load factor is the size/capacity;
    //cast to floats 
    float loadFactor = (float)hashMapSize(map) / (float)hashMapCapacity(map);
    return loadFactor;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink *link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
