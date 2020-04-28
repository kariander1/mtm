#ifndef NODEKEYVALUE_C_
#define NODEKEYVALUE_C_

#include "node_key_value.h"
#include <stdlib.h>
#include "../macro.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../election_utilities.c"
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
    RETURN_ON_CONDITION_NO_VALUE(node,NULL);
    free(node);
    return;
}

char* NodeGetKey (NodeKeyValue node)
{
    RETURN_ON_NULL(node,NULL);
    return node->key;
}

char* NodeGetValue(NodeKeyValue node)
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
    RETURN_ON_CONDITION_NO_VALUE(node,NULL);
    node->next = new_next;
    return;
}
void NodePutkey(NodeKeyValue node, char* new_key)
{
    RETURN_ON_CONDITION_NO_VALUE(node,NULL);
    node->key = new_key;
    return;
}
void NodePutValue(NodeKeyValue node, char* new_value)
{
    RETURN_ON_CONDITION_NO_VALUE(node,NULL);
    node->value = new_value;
    return;
}

void NodePromoteToNext(NodeKeyValue *node)
{
    RETURN_ON_CONDITION_NO_VALUE(*node,NULL);
    (*node) = (*node)->next;
    return;
}

int main(){
    printf("test");
    return 0;
}
#endif


