#include "mtm_map/map.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define LOGGING_NONE 1
#define LOGGING_LOW 1
#define LOGGING_MEDIUM 2
#define LOGGING_HIGH 3
#define ZERO_ELEMENTS 0
#define SIZE_OF_NULL_MAP -1

#define LOGGING_LEVEL HIGH

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
static char *mapGetNextKeyAndPromote(MapEntry* original_entry, MapEntry* next_entry);
static char *mapGetFirstInternal(Map map);
static char *mapGetNextInternal(Map map);
static char *copyEntryToString(const char *emtry);
static MapEntry mapGetPrevious(Map map, const char *key);
static MapEntry mapEntryCreateOrPromote(MapEntry* original_entry);
static void free_entry(MapEntry entry);

void logMessage(char *text, int logging_level)
{
#if LOGGING_LEVEL >= logging_level
    printf("%s\n", text);
#endif
}

Map mapCreate()
{
    Map new_map = malloc(sizeof(*new_map));
    assert(new_map);

    if (!new_map)
    {
        logMessage("Allocation failure in creating new map", LOGGING_LOW);
        return NULL;
    }

    initialize_attributes(new_map);
    logMessage("Allocation successfull in creating new map", LOGGING_HIGH);
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
    //  bool mapping_failure=false;

    if (!map || !new_map)
    {
        mapDestroy(new_map);
        return NULL;
    }
    char *current_key = mapGetFirst(map);
    while (current_key) // If first entry was NULL, then the loop won't be executed
    {
        char *current_value = mapGet(map, current_key);
        if (mapPut(new_map, current_key, current_value) != MAP_SUCCESS)
        {
            mapDestroy(new_map);
            return NULL;
        }
        current_key = mapGetNext(map);
    }

    return new_map;
}
int mapGetSize(Map map) //Done
{
    if (!map)
    {
        return SIZE_OF_NULL_MAP;
    }
    return map->number_of_entries;
}
bool mapContains(Map map, const char *key) // If element was found, then internal_iterator is set there
{
    assert(map);
    assert(key);
    if (!map || !key)
    {
        return false;
    }
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
    if (!str_copy)
    {
        return NULL;
    }
    strcpy(str_copy, entry);
    return str_copy;
}
MapResult mapPut(Map map, const char *key, const char *data) //DONE
{
      mapGetFirst(map); // Reset iterator;
    if (!map || !key || !data)
    { //check if NULL ARUMENT
        return MAP_NULL_ARGUMENT;
    }
  

    char *data_copy = copyEntryToString(data); // copy the data const char
    if (!data_copy)
    {
        return MAP_OUT_OF_MEMORY; // Break
    }

    if (mapContains(map, key))
    { // if  the dictionary contains the key -> puts the iterator on the place where a match was found

        free((map->iterator_internal->value));     //free the previous value
        map->iterator_internal->value = data_copy; // replace with new data
        return MAP_ITEM_ALREADY_EXISTS;
    }

    //char *data_copy = copyEntryToString(data); // First check that copy was successful
    char *key_copy = copyEntryToString(key);
    if (!key_copy)
    {
        free(data_copy);
        return MAP_OUT_OF_MEMORY;
    }
    // map->map_tail = malloc(sizeof(*(map->map_tail))); /// This will override the tail node
    if (!mapEntryCreateOrPromote(&(map->map_tail))) // Only afterwards create node, so there won't be an empty node
    {
        return MAP_OUT_OF_MEMORY; //Break
    }

    map->map_tail->key = key_copy;
    map->map_tail->value = data_copy;
    //  map->map_tail->next = NULL; // get the tail next to be NULL -----> Being set in mapEntryCreateOrPromote
    if (mapGetSize(map) == ZERO_ELEMENTS)
    {
        map->map_head = map->map_tail; // if this is the first element - get the head to point on it
    }
    map->number_of_entries++; // Should only increment if key didn't exist

    return MAP_SUCCESS;
}
char *mapGet(Map map, const char *key)
{
    assert(map);
    assert(key);
    if (!map || !key)
    {
        return NULL;
    }
    return (mapContains(map, key) ? map->iterator_internal->value : NULL); // Map contains will set the internal_iterator on the found Entry
}

// internal iterator - where the current entry is
// iterator - where the previous entry is
MapResult mapRemove(Map map, const char *key) //Done
{
    mapGetFirst(map); // Reset iterator;
    if (!map || !key)
    {
        return MAP_NULL_ARGUMENT;
    }
    if (!mapContains(map, key))
    { // now the internal iterator is on key element
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    MapEntry prevoius_entry = mapGetPrevious(map, key);  // Maybe add a previous node?
    prevoius_entry->next = map->iterator_internal->next; //get the previous element to point to the next element after the current one
    free_entry(map->iterator_internal);

    map->number_of_entries--; // Added

    return MAP_SUCCESS;
}

char *mapGetFirst(Map map)
{
    if (!map)
    {
        return NULL;
    }
    return mapGetNextKeyAndPromote(&(map->iterator), &(map->map_head)); // Exported to function
}
char *mapGetNext(Map map)
{
    if (!map)
    {
        return NULL;
    }
    return mapGetNextKeyAndPromote(&(map->iterator), &(map->iterator->next)); // Exported to function
}

MapResult mapClear(Map map)
{
    assert(map);
    if (!map)
    {
        return MAP_NULL_ARGUMENT;
    }

    mapGetFirstInternal(map); //set iterator_internal for the for the first element, can be NULL and it's OK
    while (map->iterator_internal)
    {
        //until the iterator_internal gets null addres (tails address +1)
        MapEntry to_delete = map->iterator_internal;
        mapGetNextInternal(map); //promote the iterator_internal
        free_entry(to_delete);
    }

    return MAP_SUCCESS;
}

void mapPrint(Map map)
{
    if (!map)
    {
        return;
    }
    char *current_key = mapGetFirstInternal(map);
    while (current_key)
    {
        printf("%s : %s\n", current_key, map->iterator_internal->value);
        current_key = mapGetNextInternal(map);
    }
}

// the functions gets the previous entry to the one with the entered key
static MapEntry mapGetPrevious(Map map, const char *key)
{
    assert(key);
    map->iterator = map->map_head;
    while (map->iterator->next->key != key)
    { //check if the next entry is with the entered key
        map->iterator = map->iterator->next;
    }
    return map->iterator;
}
static char *mapGetFirstInternal(Map map) // These functions should be similar to mapGetFirst
{
    if (!map)
    {
        return NULL;
    }
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->map_head)); // Exported to function
}
static char *mapGetNextInternal(Map map) // These functions should be similar to mapGetNext
{
    if (!map)
    {
        return NULL;
    }
    return mapGetNextKeyAndPromote(&(map->iterator_internal), &(map->iterator_internal->next)); // Exported to function
}
static char *mapGetNextKeyAndPromote(MapEntry* original_entry, MapEntry* next_entry)
{
    *original_entry = *next_entry;
    return (*original_entry ? (*original_entry)->key : NULL); // Added check that the node is not NULL
}
static MapEntry mapEntryCreateOrPromote(MapEntry* original_entry)
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
    if (!(*original_entry))
    {
        return NULL;
    }
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
static void free_entry(MapEntry entry)
{
    free(entry->key);   //free the key
    free(entry->value); // free the value
    free(entry);        // free the current MapEntry
}
//Only for debugging

int main()
{
    Map test = mapCreate();
    /*
    MapEntry shelly;
    shelly = malloc(sizeof(*shelly));
    shelly->key = "20202022";
    shelly->value = "Shelly Francis";
    MapEntry shai;
    shai = malloc(sizeof(*shelly));
    shai->key = "5534532";
    shai->value = "Shai Yehezkel";
    test->iterator_internal = shelly;
    test->map_head = shelly;
    test->iterator_internal->next = shai;
    test->iterator_internal->next->next = NULL;
    */
   mapPut(test,"20202022","Shelly Francis");
   mapPut(test,"5534532","Shai Yehezkel");
    mapPrint(test);
    //  Map test2=mapCopy(test);

    //	mapDestroy(test);
    char *it_string;
    MAP_FOREACH(it_string, test) // It works!
    {
        printf("%s\n", it_string);
    }
    mapPut(test, "5534532", "test"); // Tested works!
    return 0;
}
