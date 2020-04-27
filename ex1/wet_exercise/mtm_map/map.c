
#ifndef MAP_C_
#define MAP_C_

#include "map.h"
#include <stdlib.h>
#include "../macro.h"
#include <string.h>
#include "../election_utilities.h"
#include "node_key_value.h"

#define ZERO_ELEMENTS 0
#define SIZE_OF_NULL_MAP -1

/*
typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
} * MapEntry;
*/
struct Map_t
{
    NodeKeyValue iterator;
    NodeKeyValue iterator_internal;
    NodeKeyValue map_head;
    NodeKeyValue map_tail;
    int number_of_entries;
};
// HELPER FUNCTIONS TOKENS

/**
* initializeAttributes: Initializes all attributes of struct Map_t to be null.
*
* @param map - the map to initialize;
* @return
* 	None.
*/
static void initializeAttributes(Map map);
/**
* mapGetNextKeyAndPromote: Promotes the given Entry to the next entry given as the second arguement
*
* @param original_entry - Pointer to the entry desired to promote;
* @param next_entry - Pointer to the entry desired to be promoted to;
* @return
* 	char*  depicting The promoted entry's key.
*   NULL if the promoted entry is NULL
*/
static char *mapGetNextKeyAndPromote(MapEntry *original_entry, MapEntry *next_entry);
/**
* mapGetFirstInternal: Same as mapGetFirst, only for the internal_iterator
*
* @param map - The map in which the internal_iterator should be returned as first entry;
* @return
* 	char* of the key of the first entry
*   NULL if the entry is NULL
*/
static char *mapGetFirstInternal(Map map);
/**
* mapGetNextInternal: Same as mapGetNext, only for the internal_iterator
*
* @param map - The map in which the internal_iterator should be returned as next entry;
* @return
* 	char* of the key of the next entry
*   NULL if the entry is NULL
*/
static char *mapGetNextInternal(Map map);
/**
* mapGetPrevious: get the previous item on the map.
*
* @param map - target map to search previous.
* @param key - the key of the element that we want to find its previous
* @return
* 	returns NULL if we want to free the first element
* 	pointer to the previous MapEntry.
*/
static MapEntry mapGetPrevious(Map map, const char *key);
/**
* mapEntryCreateOrPromote: if the original_entry is empty - allocates it and initialize with NULL values  
*                          if the original_entry is not empty - goes to the next item allocates it and initialize with NULL values
* @param original_entry - the entry to create or promote.
* @return
* 	returns NULL if the allocation to new MapEntry failed
* 	returns a pointer to the new MapEntry 
*/
static MapEntry mapEntryCreateOrPromote(MapEntry *original_entry);
/**
* getCopyOfString: Copies a string to a new xmalloc'd area, kind of the same in election, made here  
* so that there won't be inclusion to election files that have many unused functions for map.
* @param str - the string to copy
*/
static char *getCopyOfString(const char* str);
/**
* freeEntry: frees the key, value and MapEntry of the given MapEntry  
*                          
* @param entry - the entry to free. 
*/
static void freeEntry(MapEntry entry);

// HELPER FUNCTIONS TOKENS END
Map mapCreate()
{
    Map new_map = xmalloc(sizeof(*new_map));

    RETURN_ON_NULL(new_map, NULL);

    initializeAttributes(new_map);
    return new_map;
}
void mapDestroy(Map map)
{
    RETURN_ON_CONDITION_NO_VALUE(map, NULL);
    RETURN_ON_CONDITION_NO_VALUE(mapClear(map), MAP_NULL_ARGUMENT);

    free(map);
    return;
}
Map mapCopy(Map map)
{
    Map new_map = mapCreate();

    if (!map || !new_map)
    {
        mapDestroy(new_map);
        return NULL;
    }
    MAP_FOREACH(current_key, map)
    {
        char *current_value = mapGet(map, current_key);
        if (mapPut(new_map, current_key, current_value) != MAP_SUCCESS)
        {
            mapDestroy(new_map);
            return NULL;
        }
    }

    return new_map;
}
int mapGetSize(Map map) //Done
{
    RETURN_ON_NULL(map, SIZE_OF_NULL_MAP);
    return map->number_of_entries;
}
bool mapContains(Map map, const char *key) // If element was found, then internal_iterator is set there
{
    RETURN_ON_NULL(map, false);
    RETURN_ON_NULL(key, false);
    char *current_key = mapGetFirstInternal(map);
    while (map->iterator_internal)
    {
        if (!strcmp(current_key, key))
        {
            return true;
        }
        current_key = mapGetNextInternal(map);
    }

    return false;
}
MapResult mapPut(Map map, const char *key, const char *data) //DONE
{
    RETURN_ON_NULL(map, MAP_NULL_ARGUMENT);
    RETURN_ON_NULL(key, MAP_NULL_ARGUMENT);
    RETURN_ON_NULL(data, MAP_NULL_ARGUMENT);

    char *data_copy = getCopyOfString(data); // copy the data const char
    RETURN_ON_NULL(data_copy, MAP_OUT_OF_MEMORY);


    if (mapContains(map, key))
    {                                              // if  the dictionary contains the key -> puts the iterator on the place where a match was found
        free((map->iterator_internal->value));     //free the previous value
        map->iterator_internal->value = data_copy; // replace with new data
        return MAP_SUCCESS;
    }
    // if the key does not exists in the dictionary
    char *key_copy = getCopyOfString(key);
    EXECUTE_ON_CONDITION(key_copy,NULL, free(data_copy), MAP_OUT_OF_MEMORY);
    if (!mapEntryCreateOrPromote(&(map->map_tail))){
        free(data_copy);
        free(key_copy);
        return MAP_OUT_OF_MEMORY;
    }

    map->map_tail->key = key_copy;
    map->map_tail->value = data_copy;
    if (mapGetSize(map) == ZERO_ELEMENTS)
    {
        map->map_head = map->map_tail; // if this is the first element - get the head to point on it
    }
    map->number_of_entries++; // Should only increment if key didn't exist
    return MAP_SUCCESS;
}
char *mapGet(Map map, const char *key)
{
    RETURN_ON_NULL(map, NULL);
    RETURN_ON_NULL(key, NULL);
    return (mapContains(map, key) ? map->iterator_internal->value : NULL); // Map contains will set the internal_iterator on the found Entry
}

// internal iterator - where the current entry is
// iterator - where the previous entry is
MapResult mapRemove(Map map, const char *key) //Done
{
    RETURN_ON_NULL(map, MAP_NULL_ARGUMENT);
    RETURN_ON_NULL(key, MAP_NULL_ARGUMENT);
    RETURN_ON_NULL(mapContains(map, key), MAP_ITEM_DOES_NOT_EXIST);
    MapEntry prevoius_entry = mapGetPrevious(map, key);
    if (prevoius_entry)
    {                                                        //if previous entry is not null
        prevoius_entry->next = map->iterator_internal->next; //get the previous element to point to the next element after the current one
    }
    else
    {

        map->map_head = map->iterator_internal->next;
    }
    if (!(map->iterator_internal->next))
    { // if we want to remove the last element
        map->map_tail = prevoius_entry;
    }
    freeEntry(map->iterator_internal);

    map->number_of_entries--; 

    return MAP_SUCCESS;
}

char *mapGetFirst(Map map)
{
    RETURN_ON_NULL(map, NULL);
    return mapGetNextKeyAndPromote(&(map->iterator), &(map->map_head));
}
char *mapGetNext(Map map)
{
    RETURN_ON_NULL(map, NULL);
    RETURN_ON_NULL(map->iterator, NULL);

    return mapGetNextKeyAndPromote(&(map->iterator), &(map->iterator->next));
}

MapResult mapClear(Map map)
{
    RETURN_ON_NULL(map, MAP_NULL_ARGUMENT);

    mapGetFirstInternal(map); //set iterator_internal for the for the first element, can be NULL and it's OK
    while (map->iterator_internal)
    {
        //until the iterator_internal gets null addres (tails address +1)
        MapEntry to_delete = map->iterator_internal;
        mapGetNextInternal(map); //promote the iterator_internal
        freeEntry(to_delete);
    }
    initializeAttributes(map);
    return MAP_SUCCESS;
}

// HELPER FUNCTIONS
static MapEntry mapGetPrevious(Map map, const char *key)
{
    if (strcmp(map->map_head->key, key) == 0)
    {
        return NULL; // returns the null if we want to free the first element
    }
    map->iterator = map->map_head;
    while (strcmp(map->iterator->next->key, key) != 0)
    { //check if the next entry is with the entered key
        map->iterator = map->iterator->next;
    }
    return map->iterator;
}
static char *mapGetFirstInternal(Map map) // These functions should be similar to mapGetFirst
{
    RETURN_ON_NULL(map, NULL);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->map_head));
}
static char *mapGetNextInternal(Map map) //Similar to mapGetNext, only this time with internal iterator
{
    RETURN_ON_NULL(map, NULL);
    RETURN_ON_NULL(map->iterator_internal, NULL);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->iterator_internal->next));
}
static char *mapGetNextKeyAndPromote(MapEntry *original_entry, MapEntry *next_entry)
{
    RETURN_ON_NULL(original_entry, NULL);
    RETURN_ON_NULL(next_entry, NULL);
    *original_entry = *next_entry;
    return (*original_entry ? (*original_entry)->key : NULL);
}
static MapEntry mapEntryCreateOrPromote(MapEntry *original_entry)
{
    if (!(*original_entry))
    {
        (*original_entry) = xmalloc(sizeof(*(*original_entry)));
        RETURN_ON_NULL((*original_entry), NULL);
    }
    else
    {
        (*original_entry)->next = xmalloc(sizeof(*((*original_entry)->next)));
         RETURN_ON_NULL((*original_entry)->next, NULL);
        (*original_entry) = (*original_entry)->next;
    }

    (*original_entry)->key = NULL;
    (*original_entry)->value = NULL;
    (*original_entry)->next = NULL;
    return (*original_entry);
}
static void initializeAttributes(Map map)
{
    map->number_of_entries = 0;
    map->iterator = NULL;
    map->iterator_internal = NULL;
    map->map_head = NULL;
    map->map_tail = NULL;
}
static char *getCopyOfString(const char* str)
{
    RETURN_ON_NULL(str,NULL);
    char * copy_of_str = xmalloc(sizeof(char)*strlen(str)+1);
    RETURN_ON_NULL(copy_of_str,NULL);
    strcpy(copy_of_str,str);
    return copy_of_str;
}
static void freeEntry(MapEntry entry)
{
    free(entry->key);   //free the key
    free(entry->value); // free the value
    free(entry);        // free the current MapEntry
}
// HELPER FUNCTIONS END

#endif //MAP_C