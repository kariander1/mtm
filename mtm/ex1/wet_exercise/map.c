#include "mtm_map/map.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define LOGGING_NONE 1
#define LOGGING_LOW 1
#define LOGGING_MEDIUM 2
#define LOGGING_HIGH 3

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

void logMessage(char *text, int logging_level)
{
#if LOGGING_LEVEL >= logging_level
    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);
    printf("%s : %s", asctime(time_info), text);
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
    logMessage("Allocation successfull in creating new map", LOGGING_HIGH);
    return new_map;
}
void mapDestroy(Map map) //TODO: Implement!
{
    if (map == NULL){
        return;
    }
    mapClear(map);// clears all data from map
    MapEntry map_to_free = map;
    map_to_free->iterator_internal = map_to_free->map_head;
    while (map_to_free->iterator_internal){
        MapEntry todelete = map_to_free->iterator_internal; 
        map_to_free->iterator_internal = map_to_free->iterator_internal->next;
        mapFreeCurrentElement(todelete);
        
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
int mapGetSize(Map map)// TODO Implement!
{
    return 0;
}
bool mapContains(Map map, const char *key)
{
    assert(map);
    assert(key);
    if (!map || !key)
    {
        return false;
    }
    map->iterator_internal = map->map_tail;
    while (map->iterator_internal)
    {
        if (!strcmp(map->iterator_internal->key, key))
        {
            return true;
        }
        map->iterator_internal = map->iterator_internal->next;
    }

    return false;
}
MapResult mapPut(Map map, const char* key, const char* data) //TODO: Implement!
{
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
    if (mapContains(map, key)) // Map contains will set the internal_iterator on the found Entry
    {
        return map->iterator_internal->value;
    }
    return NULL;
}
MapResult mapRemove(Map map, const char* key)//TODO: Implement!
{
    return MAP_SUCCESS;
}

char* mapGetFirst(Map map) // Shai's TEST, REMOVE THIS WHEN FUNCTION IS Implemented!
{
    map->iterator=map->map_tail;
    return map->iterator->key;
}
char* mapGetNext(Map map)// Shai's TEST, REMOVE THIS WHEN FUNCTION IS Implemented!
{
    map->iterator=map->iterator->next;
    return map->iterator->key;
}
MapResult mapClear(Map map)
{
    assert(map);
    if (!map)
    {
        return MAP_NULL_ARGUMENT;
    }
    char* current_key = mapGetFirst(map);
    while (current_key) // If first entry was NULL, then the loop won't be executed
    {
        mapRemove(map, current_key);
        current_key = mapGetNext(map);
    }
    map->map_head = map->map_tail; // Should we do this or the MapPut does that already?

    return MAP_SUCCESS;
}



//Only for debugging
int main()
{
    Map map = map = mapCreate();
    Map test = mapCreate;
    MapEntry shelly;
    shelly = malloc(sizeof(*shelly));
    shelly->key = "20202022";
    shelly->value = "Shelly Francis";
    MapEntry shai;
    shai = malloc(sizeof(*shelly));
    shai->key = "5534532";
    shai->value = "Shai Yehezkel";
    
    test->iterator_internal = shelly;
    test->iterator_internal->next = shai;
    mapDestroy(test);
    return 0;
}