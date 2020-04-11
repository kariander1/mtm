#include "mtm_map/map.h"
#include <stdlib.h>

typedef struct Map_t
{
    MapEntry iterator;
    MapEntry map_head;
    MapEntry map_tail;

}* Map;
typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
    struct node_t *previous;

} * MapEntry;


MapEntry mapCreate(Map map)
{
    MapEntry new_map = malloc(sizeof(*new_map));
    if(!new_map)
    {
        return NULL;
    }
    return new_map;
}

MapEntry mapCopy(Map map)
{
      MapEntry new_map = malloc(sizeof(*new_map));
    if(!new_map)
    {
        return NULL;
    }
}
//Only for debugging
int main()
{

    MapEntry shelly;
    shelly = malloc(sizeof(*shelly));
    shelly->key = "20202022";
    shelly->value = "Shelly Francis";
    return 0;
}