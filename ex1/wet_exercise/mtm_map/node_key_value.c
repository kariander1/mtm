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
NodeKeyValue NodeDestroy(NodeKeyValue node);

NodeKeyValue NodeGetKey (NodeKeyValue node);

NodeKeyValue NodeGetValue(NodeKeyValue node);

NodeKeyValue NodeGetNext(NodeKeyValue node);

void NodePutNext(NodeKeyValue node, NodeKeyValue new_next){
    node->next = new_next;
    return;
}
void NodePutkey(NodeKeyValue node, NodeKeyValue new_key){
    return;
}
void NodePutValue(NodeKeyValue node, NodeKeyValue new_key){
    return;
}

#endif