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
    new_map->number_of_entries=0;
    new_map->iterator=NULL;
    new_map->iterator_internal=NULL;
    new_map->map_head=NULL;
    new_map->map_tail=NULL;
    logMessage("Allocation successfull in creating new map", LOGGING_HIGH);
    return new_map;
}
void mapDestroy(Map map)
{
    //assert(map->map_head);
    if (map == NULL){
        return; 
    }
    mapClear(map);// clears all data from map
    free(map);
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
    if ((map->map_head) == NULL){
        return ZERO_ELEMENTS;
    }
    int num_elements = 0;
    map->iterator_internal = map->map_head; //set iterator_internal for the for the first element
    while (map->iterator_internal){
        map->iterator_internal = map->iterator_internal->next;
        num_elements++;
    }
    return num_elements;
}
bool mapContains(Map map, const char *key) // If element was found, then internal_iterator is set there
{
    assert(map);
    assert(key);
    if (!map || !key)
    {
        return false;
    }
    char* current_key = mapGetFirstInternal(map);
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
        assert(map);

    map->iterator = map->map_head;
    if (!(map->iterator))
        return NULL;
    return map->iterator->key;
}
char* mapGetNext(Map map)// Shai's TEST, REMOVE THIS WHEN FUNCTION IS Implemented!
{
       assert(map);

    map->iterator = map->iterator->next;
    if (!(map->iterator))
        return NULL;
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
void mapPrint(Map map)
{
    if(!map)
    {
        return;
    }
    char* current_key = mapGetFirstInternal(map);
    while (current_key)
    {
        printf("%s : %s\n",current_key,map->iterator_internal->value);
        current_key = mapGetNextInternal(map);
    }
    
}

static char *mapGetFirstInternal(Map map) // These functions should be similar to mapGetFirst
{
    assert(map);

    map->iterator_internal = map->map_head;
    if (!(map->iterator_internal))
        return NULL;
    return map->iterator_internal->key;
}
static char* mapGetNextInternal(Map map) // These functions should be similar to mapGetNext
{
    assert(map);
    map->iterator_internal=map->iterator_internal->next;
        if (!(map->iterator_internal))
        return NULL;
    return map->iterator_internal->key;
}
//Only for debugging
/* int main()
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
    mapPrint(test);
  //  Map test2=mapCopy(test);
    
	mapDestroy(test);
	return 0;
} */