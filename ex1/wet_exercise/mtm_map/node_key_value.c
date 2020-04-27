#ifndef NODEKEYVALUE_C_
#define NODEKEYVALUE_C_

#include "node_key_value.h"
#include <stdlib.h>
#include "../macro.h"
#include <string.h>

struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
};

NodeKeyValue NodeCreate(){
    NodeKeyValue new_node = malloc(sizeof(*new_node));
}


#endif