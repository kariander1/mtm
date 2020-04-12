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
static char* copyEntryToString(const char* emtry);
static MapEntry mapGetPrevious(Map map, const char* key);

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
int mapGetSize(Map map)//Done
{
    if (!map){
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
static char* copyEntryToString(const char* emtry){ // copys a constant string to a new allocated place and returns the copied string
    char* str_copy = malloc(sizeof(char)*strlen(emtry) +1);
    if (!str_copy){
        return NULL;
    }
    strcpy(str_copy, emtry);
    return str_copy;
}
MapResult mapPut(Map map, const char* key, const char* data) //DONE
{
    if ( !map || !key || !data){ //check if NULL ARUMENT
        return MAP_NULL_ARGUMENT;
    }
    if (mapContains(map,key)){ // if  the dictionary contains the key -> puts th iterator on the place where a match was found
        char* data_copy = copyEntryToString(data); // copy the data const char
        if (!data_copy){
            return MAP_OUT_OF_MEMORY ;
        }
        free((map->iterator_internal->value)); //free the previous value
        map->iterator_internal->value = data_copy; // replace with new data
    }
    else{ // if the key does not exsists in the dictionary
        map->map_tail =  malloc(sizeof(*(map->map_tail))); /// OR WRITE IN THE MALLOC JUST MAPENTRY? --------------------------------<<<<<<<<<<<<<<<<<<<<<
        if (!(map->map_tail)){
            return MAP_OUT_OF_MEMORY;
        }
        char* data_copy = copyEntryToString(data);
        char* key_copy = copyEntryToString(key);
        if (!data_copy || !key_copy ){
            free(map->map_tail);
            free (data_copy); // maybe are NULL but just to check
            free(key_copy);
            return MAP_OUT_OF_MEMORY;
        }
        map->map_tail->key = key_copy;
        map->map_tail->value = data_copy;
        map->map_tail->next =NULL; // get the tail next to be NULL
        if (mapGetSize == ZERO_ELEMENTS){
            map->map_head = map->map_tail; // if this is the first element - get the head to point on it
        }
    }
    map->number_of_entries++;
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
// the functions gets the previus entry to the one with the entered key
static MapEntry mapGetPrevious(Map map, const char* key){
    assert (key);
    if(map->map_head->key == key){
        return NULL; // returns the null if we want to free the first element
    }
    map->iterator = map->map_head;
    while(map->iterator->next->key != key){//check if the next entry is with the entered key
        map->iterator = map->iterator->next;
    }
    return map->iterator;  
}
// internal iterator - where the current entry is
// iterator - where the previos entry is
MapResult mapRemove(Map map, const char* key)//Done
{
	if (!map || !key) {
		return MAP_NULL_ARGUMENT;
	}
	if (!mapContains(map, key)) { // now the internal iterator is on key element
		return MAP_ITEM_DOES_NOT_EXIST;
	}
	MapEntry prevoius_entry = mapGetPrevious(map, key);
	if (prevoius_entry) { //if previus entry is not null
		prevoius_entry->next = map->iterator_internal->next; //get the previous element to point to the next element after the current one
		if (!map->iterator_internal->next) { // if we want to remove the last element
			map->map_tail = map->iterator_internal;
		}
	}
	else {
		map->map_head = map->iterator_internal->next;// if we want to remove the first element - set new head
	}
	free(map->iterator_internal->key); //free the key
	free(map->iterator_internal->value); // free the value
	free(map->iterator_internal); // free the current MapEntry
	return MAP_SUCCESS;
}

char* mapGetFirst(Map map) // Shai's TEST, REMOVE THIS WHEN FUNCTION IS Implemented!
{
    if (!map){
        return NULL;
    }
    map->iterator = map->map_head;
    return map->iterator->key;
}
char* mapGetNext(Map map)// Shai's TEST, REMOVE THIS WHEN FUNCTION IS Implemented!
{
    if (!map){
        return NULL;
    }
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