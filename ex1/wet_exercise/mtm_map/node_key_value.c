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
    node->key = NULL;  // the free is done outside
    node->next = NULL;
    node->value = NULL;
    free(node);
    return;
}

char * NodeGetKey (NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->key;
}

char * NodeGetValue(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->value;
}

char * NodeGetNext(NodeKeyValue node)
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

void NodePromoteToNext(NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    node = node->next;
    return;
}

#endif



int main(){
    NodeKeyValue node1 =  NodeCreate();
    NodePutNext(node1, NULL);
    NodePutkey(node1, "Shelly");
    NodePutValue(node1, "Francis");
    NodeGetKey(node1);
    NodeGetValue(node1);
    NodeKeyValue node2 =  NodeCreate();
    NodePutNext(node1, node2);
    NodeGetNext(node1);
    NodePutkey(node2, "Shai");
    NodeDestroy(node1);
    NodeDestroy(node2);
    printf("finish ! \n");
    return 0;
}