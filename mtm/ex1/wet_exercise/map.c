#include "mtm_map/map.h"
#include <stdlib.h>

typedef struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
    struct node_t *previous;

} * Entry;

int main()
{

    Entry shelly;
    shelly = malloc(sizeof(*shelly));
    shelly->key = "2020202";
    shelly->value = "Shelly Francis";

    return 0;
}