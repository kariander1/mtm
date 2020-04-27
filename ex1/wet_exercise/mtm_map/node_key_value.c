#ifndef NODEKEYVALUE_C_
#define NODEKEYVALUE_C_

#include "node_key_value.h"
#include <stdlib.h>
#include "../macro.h"
#include <string.h>
#include "../election_utilities.h"

struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
};

NodeKeyValue NodeCreate()
{
    NodeKeyValue new_node = xmalloc(sizeof(*new_node));
    RETURN_ON_NULL(new_node,NULL);
    // initialize node 
    new_node->key = NULL;
    new_node->next = NULL;
    new_node->value = NULL;
    return new_node;
}
void NodeDestroy(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    node->key = NULL;  // what do you say - just in case?
    node->next = NULL;
    node->value = NULL;
    free(node);
    return;
}

NodeKeyValue NodeGetKey (NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->key;
}

NodeKeyValue NodeGetValue(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->value;
}

NodeKeyValue NodeGetNext(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->next;
}

void NodePutNext(NodeKeyValue node, NodeKeyValue new_next)
{
    RETURN_ON_NULL(node,NULL);
    node->next = new_next;
    return;
}
void NodePutkey(NodeKeyValue node, NodeKeyValue new_key)
{
    RETURN_ON_NULL(node,NULL);
    node->key = new_key;
    return;
}
void NodePutValue(NodeKeyValue node, NodeKeyValue new_value)
{
    RETURN_ON_NULL(node,NULL);
    node->value = new_value;
    return;
}

NodeKeyValue NodePromoteToNext(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->next;
}

#endif