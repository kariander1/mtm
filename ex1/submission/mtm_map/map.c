


#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "../exUtilities.h"
#include "../nodeKeyValue.h"

#define ZERO_ELEMENTS 0
#define SIZE_OF_NULL_MAP -1

struct Map_t
{
    NodeKeyValue iterator;
    NodeKeyValue iterator_internal; // For internal use, when iterator is already used
    NodeKeyValue map_head;
    NodeKeyValue map_tail;
    int number_of_entries; // So that returning size will be O(1) instead of cycling through nodes
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
static char *mapGetNextKeyAndPromote(NodeKeyValue *original_entry, NodeKeyValue *next_entry);
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
static NodeKeyValue mapGetPrevious(Map map, const char *key);


// HELPER FUNCTIONS TOKENS END
Map mapCreate()
{
    Map new_map = malloc(sizeof(*new_map));

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

    if (mapContains(map, key))
    {  // if  the dictionary contains the key -> puts the iterator on the place where a match was found
        RETURN_ON_CONDITION(nodePutValue(map->iterator_internal, data),false,MAP_OUT_OF_MEMORY); // Will free previous value
        return MAP_SUCCESS;
    }

    NodeKeyValue temp_node = nodeCreate();
    RETURN_ON_NULL(temp_node,MAP_OUT_OF_MEMORY)
    EXECUTE_ON_CONDITION(nodePutkey(temp_node, key),false,nodeDestroy(temp_node),MAP_OUT_OF_MEMORY);
    EXECUTE_ON_CONDITION(nodePutValue(temp_node,data),false,nodeDestroy(temp_node),MAP_OUT_OF_MEMORY);

   if(!map->map_tail)
   {
       map->map_tail=temp_node;
   }
   else
   {
        nodePutNext(map->map_tail,temp_node) ;
        nodePromoteToNext(&(map->map_tail));
   }
   

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
    return (mapContains(map, key) ? nodeGetValue(map->iterator_internal) : NULL); // Map contains will set the internal_iterator on the found Entry
}

// internal iterator - where the current entry is
// iterator - where the previous entry is
MapResult mapRemove(Map map, const char *key) //Done
{
    RETURN_ON_NULL(map, MAP_NULL_ARGUMENT);
    RETURN_ON_NULL(key, MAP_NULL_ARGUMENT);
    RETURN_ON_NULL(mapContains(map, key), MAP_ITEM_DOES_NOT_EXIST);
    NodeKeyValue prevoius_entry = mapGetPrevious(map, key);
    NodeKeyValue next_entry = nodeGetNext(map->iterator_internal);
    if (prevoius_entry)
    {   //if previous entry is not null
        nodePutNext(prevoius_entry,next_entry);  //get the previous element to point to the next element after the current one
        
    }
    else
    {
        map->map_head  = next_entry; //if first entry (no previus entry)
    }
    if (!next_entry)
    { // if we want to remove the last element. next entry is NULL
        map->map_tail = prevoius_entry;
    }
    nodeDestroy(map->iterator_internal);

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

    NodeKeyValue next_iterator =nodeGetNext(map->iterator);
    return mapGetNextKeyAndPromote(&(map->iterator), &(next_iterator));
}

MapResult mapClear(Map map)
{
    RETURN_ON_NULL(map, MAP_NULL_ARGUMENT);

    mapGetFirstInternal(map); //set iterator_internal for the for the first element, can be NULL and it's OK
    while (map->iterator_internal)
    {
        //until the iterator_internal gets null addres (tails address +1)
        NodeKeyValue to_delete = map->iterator_internal;
        mapGetNextInternal(map); //promote the iterator_internal
        nodeDestroy(to_delete);
    }
    initializeAttributes(map);
    return MAP_SUCCESS;
}

// HELPER FUNCTIONS
static NodeKeyValue mapGetPrevious(Map map, const char *key)
{
    if (strcmp(nodeGetKey(map->map_head), key) == 0)
    {
        return NULL; // returns the null if we want to free the first element
    }
    map->iterator = map->map_head;
    while (strcmp(nodeGetKey(nodeGetNext(map->iterator)), key) != 0)
    { //check if the next entry is with the entered key
       nodePromoteToNext(&(map->iterator));
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
    NodeKeyValue next_iterator = nodeGetNext(map->iterator_internal);
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(next_iterator));
}
static char *mapGetNextKeyAndPromote(NodeKeyValue *original_entry, NodeKeyValue *next_entry)
{
    RETURN_ON_NULL(original_entry, NULL);
    RETURN_ON_NULL(next_entry, NULL);
    *original_entry = *next_entry;
    return (*original_entry ? nodeGetKey((*original_entry)) : NULL);
}
static void initializeAttributes(Map map)
{
    map->number_of_entries = 0;
    map->iterator = NULL;
    map->iterator_internal = NULL;
    map->map_head = NULL;
    map->map_tail = NULL;
}
// HELPER FUNCTIONS END
