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
#define ZERO_ELEMENTS 0

#define LOGGING_LEVEL HIGH

static char* mapGetFirstInternal(Map map);
static char* mapGetNextInternal(Map map);

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
void mapDestroy(Map map)//For Shai - DONE FUNCTION!!!!
{
    if (mapClear(map) ==MAP_NULL_ARGUMENT){ // clears all data from map
       return;
    }
    else{
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
int mapGetSize(Map map)//For Shai - DONE FUNCTION!!!!
{
    if (map == NULL){
        return -1;
    }
    return map->number_of_entries;
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
static char* copyDataToString(const char* data){
    char* str_copy = malloc(sizeof(*data)*strlen(data) +1);
    strcpy(str_copy, data);
    return str_copy;
}
MapResult mapPut(Map map, const char* key, const char* data) //TODO: Implement!
{
    if ((map == NULL) || (key == NULL) || (data== NULL)){
        return MAP_NULL_ARGUMENT;
    }
    if (mapGetSize(map) == ZERO_ELEMENTS){
        map->map_tail =  malloc(sizeof(*(map->map_tail)));
        if (map->map_tail == NULL){
            return MAP_OUT_OF_MEMORY;
        }
        else{
            map->map_head = map->map_tail;
        }
    }
    if (mapContains(map,key)){
        char* str_copy = copyDataToString(data);
        free((map->iterator_internal->value)); /// ERROR HERE <------
        map->iterator_internal->value = str_copy;
    }
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

   
    mapGetFirstInternal(map); //set iterator_internal for the for the first element
    while (map->iterator_internal){ 
        //until the iterator_internal gets null addres (tails address +1)
        MapEntry to_delete = map->iterator_internal; 
        mapGetNextInternal(map); //promote the iterator_internal
        free(to_delete); 
    }

    return MAP_SUCCESS;
}
void mapPrint(Map map) // Should use iterator or internal_iterator?
{
    char* current_key = mapGetFirst(map);
    while (current_key)
    {
        printf("%s : %s\n",current_key,mapGet(map,current_key));
        current_key = mapGetNext(map);
    }
    
}

static char* mapGetFirstInternal(Map map) // These functions should be similar to mapGetFirst
{
    assert(map);

    map->iterator_internal=map->map_head;
    return map->iterator_internal->key;
}
static char* mapGetNextInternal(Map map) // These functions should be similar to mapGetNext
{
    assert(map);
    map->iterator=map->iterator->next;
    return map->iterator_internal->key;
}
//Only for debugging
int main()
{
	Map test = malloc(sizeof(*test));
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
    mapPut(test, "1234", "test");
    return 0;
}