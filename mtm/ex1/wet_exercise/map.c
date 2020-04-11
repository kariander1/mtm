#include "mtm_map/map.h"
#include <stdlib.h>

typedef struct Map_t
{
    Entry iterator;
    Entry map_head;
    Entry map_tail;

}* Map;
typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
    struct node_t *previous;

} * Entry;


Map mapCreate(Map map)
{
    Map new_map = malloc(sizeof(*new_map));
    if(!new_map)
    {
        return NULL;
    }
    return new_map;
}

Map mapCopy(Map map)
{
      Map new_map = malloc(sizeof(*new_map));
    if(!new_map)
    {
        return NULL;
    }
}
//Only for debugging
int main()
{

    Entry shelly;
    shelly = malloc(sizeof(*shelly));
    shelly->key = "20202022";
    shelly->value = "Shelly Francis";
    return 0;
}