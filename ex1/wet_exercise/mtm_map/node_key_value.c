#ifndef NODEKEYVALUE_C_
#define NODEKEYVALUE_C_

#include "node_key_value.h"
#include <stdlib.h>
#include "../macro.h"
#include <string.h>
#include <../election_utilities.h>

struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
};

Node NodeCreate()
{
    Node new_node = xmalloc(sizeof(*new_node));
    RETURN_ON_NULL(new_node,NULL);

    return new_node;
}

#endif