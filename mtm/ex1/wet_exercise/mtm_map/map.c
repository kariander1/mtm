
#ifndef MAP_C_
#define MAP_C_

//Should add asserts
#include <assert.h>
#include "map.h"
#include <stdlib.h>

#include <string.h>

#define ZERO_ELEMENTS 0
#define SIZE_OF_NULL_MAP -1

#ifndef RETURN_ON_NONEXISTENCE
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_NONEXISTENCE(object, return_value) \
    if (!(object))                                   \
    {                                                \
        return (return_value);                       \
    }

#endif
#ifndef EXECUTE_ON_NONEXISTENCE
/*!
* Macro for shortening returning values for non-existence of a object with an extra expression to execute.
*/
#define EXECUTE_ON_NONEXISTENCE(object, expression, return_value) \
    if (!(object))                                                \
    {                                                             \
        expression;                                               \
        return (return_value);                                    \
    }
#endif
#ifndef RETURN_ON_CONDITION_NO_VALUE
/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_CONDITION_NO_VALUE(object, comparator) \
    if ((object) == comparator)                          \
    {                                                    \
        return;                                          \
    }

#endif
typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
} * MapEntry;

struct Map_t
{
    MapEntry iterator;
    MapEntry iterator_internal;
    MapEntry map_head;
    MapEntry map_tail;
    int number_of_entries;
};
// HELPER FUNCTIONS TOKENS

/**
* initialize_attributes: Initializes all attributes of struct Map_t to be null.
*
* @param map - the map to initialize;
* @return
* 	None.
*/
static void initialize_attributes(Map map);
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
* copyEntryToString: copies const key or value to a string.
*
* @param entry - the const key / value to be copied.
* @return
* 	NULL if allocations failed.
* 	 pointer to the new string.
*/
static char *copyEntryToString(const char *entry);
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
* freeEntry: frees the key, value and MapEntry of the given MapEntry  
*                          
* @param entry - the entry to free. 
*/
static void freeEntry(MapEntry entry);

// HELPER FUNCTIONS TOKENS END
Map mapCreate()
{
    Map new_map = malloc(sizeof(*new_map));
    assert(new_map);

    RETURN_ON_NONEXISTENCE(new_map, NULL);

    initialize_attributes(new_map);
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
    assert(map);
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
    RETURN_ON_NONEXISTENCE(map, SIZE_OF_NULL_MAP);
    return map->number_of_entries;
}
bool mapContains(Map map, const char *key) // If element was found, then internal_iterator is set there
{
    assert(map);
    assert(key);
    RETURN_ON_NONEXISTENCE(map, false);
    RETURN_ON_NONEXISTENCE(key, false);
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
static char *copyEntryToString(const char *entry)
{ // copys a constant string to a new allocated place and returns the copied string
    char *str_copy = malloc(strlen(entry) + 1);
    RETURN_ON_NONEXISTENCE(str_copy, NULL);
    strcpy(str_copy, entry);
    return str_copy;
}
MapResult mapPut(Map map, const char *key, const char *data) //DONE
{
    RETURN_ON_NONEXISTENCE(data, MAP_NULL_ARGUMENT);

    char *data_copy = copyEntryToString(data); // copy the data const char
    RETURN_ON_NONEXISTENCE(data_copy, MAP_OUT_OF_MEMORY);
    RETURN_ON_NONEXISTENCE(map, MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(key, MAP_NULL_ARGUMENT);

    if (mapContains(map, key))
    {                                              // if  the dictionary contains the key -> puts the iterator on the place where a match was found
        free((map->iterator_internal->value));     //free the previous value
        map->iterator_internal->value = data_copy; // replace with new data
        return MAP_SUCCESS;
    }
    // if the key does not exists in the dictionary
    char *key_copy = copyEntryToString(key);
    EXECUTE_ON_NONEXISTENCE(key_copy, free(data_copy), MAP_OUT_OF_MEMORY);
    RETURN_ON_NONEXISTENCE(mapEntryCreateOrPromote(&(map->map_tail)), MAP_OUT_OF_MEMORY);

    map->map_tail->key = key_copy;
    map->map_tail->value = data_copy;
    if (mapGetSize(map) == ZERO_ELEMENTS)
    {
        map->map_head = map->map_tail; // if this is the first element - get the head to point on it
    }
    // map->map_tail = malloc(sizeof(*(map->map_tail))); /// This will override the tail node
    map->number_of_entries++; // Should only increment if key didn't exist
    return MAP_SUCCESS;
}
char *mapGet(Map map, const char *key)
{
    assert(map);
    assert(key);
    RETURN_ON_NONEXISTENCE(map, NULL);
    RETURN_ON_NONEXISTENCE(key, NULL);
    return (mapContains(map, key) ? map->iterator_internal->value : NULL); // Map contains will set the internal_iterator on the found Entry
}

// internal iterator - where the current entry is
// iterator - where the previous entry is
MapResult mapRemove(Map map, const char *key) //Done
{
    RETURN_ON_NONEXISTENCE(map, MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(key, MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(mapContains(map, key), MAP_ITEM_DOES_NOT_EXIST);
    MapEntry prevoius_entry = mapGetPrevious(map, key);
    if (prevoius_entry)
    {                                                        //if previous entry is not null
        prevoius_entry->next = map->iterator_internal->next; //get the previous element to point to the next element after the current one
    }
    else //What about if i want to remove an element in the middle? it should not change head or tail
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
    RETURN_ON_NONEXISTENCE(map, NULL);
    return mapGetNextKeyAndPromote(&(map->iterator), &(map->map_head)); // Exported to function
}
char *mapGetNext(Map map)
{
    RETURN_ON_NONEXISTENCE(map, NULL);
    RETURN_ON_NONEXISTENCE(map->iterator, NULL);

    return mapGetNextKeyAndPromote(&(map->iterator), &(map->iterator->next)); // Exported to function
}

MapResult mapClear(Map map)
{
    assert(map);
    RETURN_ON_NONEXISTENCE(map, MAP_NULL_ARGUMENT);

    mapGetFirstInternal(map); //set iterator_internal for the for the first element, can be NULL and it's OK
    while (map->iterator_internal)
    {
        //until the iterator_internal gets null addres (tails address +1)
        MapEntry to_delete = map->iterator_internal;
        mapGetNextInternal(map); //promote the iterator_internal
        freeEntry(to_delete);
    }
    initialize_attributes(map);
    return MAP_SUCCESS;
}

// HELPER FUNCTIONS
static MapEntry mapGetPrevious(Map map, const char *key)
{
    assert(key);
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
    RETURN_ON_NONEXISTENCE(map, NULL);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->map_head));
}
static char *mapGetNextInternal(Map map) //Similar to mapGetNext, only this time with internal iterator
{
    RETURN_ON_NONEXISTENCE(map, NULL);
    RETURN_ON_NONEXISTENCE(map->iterator_internal, NULL);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->iterator_internal->next));
}
static char *mapGetNextKeyAndPromote(MapEntry *original_entry, MapEntry *next_entry)
{
    RETURN_ON_NONEXISTENCE(original_entry, NULL); // Check pointers aren't NULL! bug found from elections
    RETURN_ON_NONEXISTENCE(next_entry, NULL);
    *original_entry = *next_entry;
    return (*original_entry ? (*original_entry)->key : NULL);
}
static MapEntry mapEntryCreateOrPromote(MapEntry *original_entry)
{
    if (!(*original_entry))
    {
        (*original_entry) = malloc(sizeof(*(*original_entry)));
    }
    else
    {
        (*original_entry)->next = malloc(sizeof(*((*original_entry)->next)));
        (*original_entry) = (*original_entry)->next;
    }
    RETURN_ON_NONEXISTENCE((*original_entry), NULL);
    (*original_entry)->key = NULL;
    (*original_entry)->value = NULL;
    (*original_entry)->next = NULL;
    return (*original_entry);
}
static void initialize_attributes(Map map)
{
    map->number_of_entries = 0;
    map->iterator = NULL;
    map->iterator_internal = NULL;
    map->map_head = NULL;
    map->map_tail = NULL;
}
static void freeEntry(MapEntry entry)
{
    free(entry->key);   //free the key
    free(entry->value); // free the value
    free(entry);        // free the current MapEntry
}
// HELPER FUNCTIONS END
#endif //MAP_C