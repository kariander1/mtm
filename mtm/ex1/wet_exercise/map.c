#include "mtm_map/map.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define ZERO_ELEMENTS 0
#define SIZE_OF_NULL_MAP -1

/*!
* Macro for shortening returning values for non-existence of a object(object is NULL or object is false).
*/
#define RETURN_ON_NONEXISTENCE(object, return_value) \
if (!(object))\
{\
    return (return_value);\
}
/*!
* Macro for shortening returning values for non-existence of a object with an extra expression to execute.
*/
#define EXECUTE_ON_NONEXISTENCE(object, expression,return_value) \
if (!(object))\
{\
    expression;\
    return (return_value);\
}

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

static void initialize_attributes(Map map);
static char *mapGetNextKeyAndPromote(MapEntry *original_entry, MapEntry *next_entry);
static char *mapGetFirstInternal(Map map);
static char *mapGetNextInternal(Map map);
static char *copyEntryToString(const char *emtry);
static MapEntry mapGetPrevious(Map map, const char *key);
static MapEntry mapEntryCreateOrPromote(MapEntry *original_entry);
static void freeEntry(MapEntry entry);

Map mapCreate()
{
    Map new_map = malloc(sizeof(*new_map));
    assert(new_map);

    RETURN_ON_NONEXISTENCE(new_map,NULL);

    initialize_attributes(new_map);
    return new_map;
}
void mapDestroy(Map map)
{
    if (mapClear(map) == MAP_NULL_ARGUMENT)
    { // clears all data from map
        return;
    }
    else
    {
        free(map);
    }
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
    RETURN_ON_NONEXISTENCE(map,SIZE_OF_NULL_MAP);
    return map->number_of_entries;
}
bool mapContains(Map map, const char *key) // If element was found, then internal_iterator is set there
{
    assert(map);
    assert(key);
    RETURN_ON_NONEXISTENCE(map,false);
    RETURN_ON_NONEXISTENCE(key,false);
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
    RETURN_ON_NONEXISTENCE(str_copy,NULL);
    strcpy(str_copy, entry);
    return str_copy;
}
MapResult mapPut(Map map, const char *key, const char *data) //DONE
{
    RETURN_ON_NONEXISTENCE(map,MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(key,MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(data,MAP_NULL_ARGUMENT);

    char *data_copy = copyEntryToString(data); // copy the data const char
    RETURN_ON_NONEXISTENCE(data_copy,MAP_OUT_OF_MEMORY);
    if (mapContains(map, key))
    {                                              // if  the dictionary contains the key -> puts the iterator on the place where a match was found
        free((map->iterator_internal->value));     //free the previous value
        map->iterator_internal->value = data_copy; // replace with new data
        return MAP_SUCCESS;
    }
    // if the key does not exists in the dictionary
    char *key_copy = copyEntryToString(key);
    EXECUTE_ON_NONEXISTENCE(key_copy,free(data_copy),MAP_OUT_OF_MEMORY);
    RETURN_ON_NONEXISTENCE(mapEntryCreateOrPromote(&(map->map_tail)),MAP_OUT_OF_MEMORY);

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
    RETURN_ON_NONEXISTENCE(map,NULL);
    RETURN_ON_NONEXISTENCE(key,NULL);
    return (mapContains(map, key) ? map->iterator_internal->value : NULL); // Map contains will set the internal_iterator on the found Entry
}

// internal iterator - where the current entry is
// iterator - where the previous entry is
MapResult mapRemove(Map map, const char *key) //Done
{
    RETURN_ON_NONEXISTENCE(map,MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(key,MAP_NULL_ARGUMENT);
    RETURN_ON_NONEXISTENCE(mapContains(map, key),MAP_ITEM_DOES_NOT_EXIST);
    MapEntry prevoius_entry = mapGetPrevious(map, key);
    if (prevoius_entry)
    {                                                        //if previous entry is not null
        prevoius_entry->next = map->iterator_internal->next; //get the previous element to point to the next element after the current one
        if (!map->iterator_internal->next)
        { // if we want to remove the last element
            map->map_tail = map->iterator_internal;
        }
    }
    else
    {
        map->map_head = map->iterator_internal->next; // if we want to remove the first element - set new head
    }
    freeEntry(map->iterator_internal);

    map->number_of_entries--; // Added

    return MAP_SUCCESS;
}

char *mapGetFirst(Map map)
{
    RETURN_ON_NONEXISTENCE(map,NULL);
    return mapGetNextKeyAndPromote(&(map->iterator), &(map->map_head)); // Exported to function
}
char *mapGetNext(Map map)
{
       RETURN_ON_NONEXISTENCE(map,NULL);
       RETURN_ON_NONEXISTENCE(map->iterator,NULL);

    return mapGetNextKeyAndPromote(&(map->iterator), &(map->iterator->next)); // Exported to function
}

MapResult mapClear(Map map)
{
    assert(map);
     RETURN_ON_NONEXISTENCE(map,MAP_NULL_ARGUMENT);

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

/**
* 	mapGetPrevious: the functions gets the previous entry to the given key
* @param map - Map to read from.
* @return
* 	NULL if a NULL was sent to the function
*   MAP_ITEM_DOES_NOT_EXIST if an equal key item does not already exists in the map
* 	MAP_SUCCESS the paired elements had been removed successfully
*/
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
    RETURN_ON_NONEXISTENCE(map,NULL);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->map_head));
}
static char *mapGetNextInternal(Map map) //Similar to mapGetNext, only this time with internal iterator
{
    RETURN_ON_NONEXISTENCE(map,NULL);
    RETURN_ON_NONEXISTENCE(map->iterator_internal,NULL);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->iterator_internal->next));
}
static char *mapGetNextKeyAndPromote(MapEntry *original_entry, MapEntry *next_entry)
{
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
    RETURN_ON_NONEXISTENCE((*original_entry),NULL);
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
/**
* 	freeEntry: Frees 
*   Frees a given entry all attributes and then frees the struct
* @param entry
* 	The desired entry to free
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent to the function
*  MAP_ITEM_DOES_NOT_EXIST if an equal key item does not already exists in the map
* 	MAP_SUCCESS the paired elements had been removed successfully
*/
static void freeEntry(MapEntry entry)
{
    free(entry->key);   //free the key
    free(entry->value); // free the value
    free(entry);        // free the current MapEntry
}