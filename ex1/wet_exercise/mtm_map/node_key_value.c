#include <stdlib.h>
#include <string.h>

#include "node_key_value.h"
#include "../macro.h"
#include "../election_utilities.h"
struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
};

static bool overrideInput(char** old_val,const char* new_val);

NodeKeyValue nodeCreate()
{
    NodeKeyValue new_node = malloc(sizeof(*new_node));
    RETURN_ON_NULL(new_node,NULL);
    // initialize node 
    new_node->key = NULL;
    new_node->next = NULL;
    new_node->value = NULL;
    return new_node;
}
void nodeDestroy(NodeKeyValue node)
{
    RETURN_ON_CONDITION_NO_VALUE(node,NULL);
    free(node->key); // Worst case scenario it will free NULL
    free(node->value);
    free(node);
    return;
}

char* nodeGetKey (NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->key;
}

char* nodeGetValue(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->value;
}

NodeKeyValue nodeGetNext(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->next;
}

void nodePutNext(NodeKeyValue node, NodeKeyValue new_next)
{
    RETURN_ON_CONDITION_NO_VALUE(node,NULL);
    node->next = new_next;
    return;
}
bool nodePutkey(NodeKeyValue node,const char* new_key)
{
    RETURN_ON_NULL(node,false);
    return overrideInput(&(node->key),(new_key));
}
bool nodePutValue(NodeKeyValue node,const char* new_value)
{
    RETURN_ON_NULL(node,false);
    return overrideInput(&(node->value),(new_value));
}

void nodePromoteToNext(NodeKeyValue *node)
{
    RETURN_ON_CONDITION_NO_VALUE(*node,NULL);
    (*node) = (*node)->next;
    return;
}

static bool overrideInput(char** old_val,const char* new_val)
{
    char* copy_of_new_val = getCopyOfString(new_val);
    RETURN_ON_NULL(copy_of_new_val,false);
    free(*old_val);
    *old_val=copy_of_new_val;
    return true;
}


