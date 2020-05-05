#include <stdlib.h>
#include <string.h>

#include "nodeKeyValue.h"
#include "exUtilities.h"


struct node_t
{
    char *key;
    char *value;
    struct node_t *next;
};

/**
* overrideInput: creates a copy of the given new value - in order to save inside the node
*    and replace the old value for the new value (frees the old value)
*
* @param old_val - The old value addres - if we want to replace an exsisting value , if this is a new value then old val is null
* @param new_val - the address of the new value to put inside the node (value od key)
* @return
* 	true - if allocation succeeded 
*   false - ifallocation failed 
*/
static NodeResult overrideInput(char** old_val,const char* new_val);

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
NodeResult nodePutkey(NodeKeyValue node,const char* new_key)
{
    RETURN_ON_NULL(node,NODE_NULL_ARGUEMENT);
    return overrideInput(&(node->key),(new_key));
}
NodeResult nodePutValue(NodeKeyValue node,const char* new_value)
{
    RETURN_ON_NULL(node,NODE_NULL_ARGUEMENT);
    return overrideInput(&(node->value),(new_value));
}

void nodePromoteToNext(NodeKeyValue *node)
{
    RETURN_ON_CONDITION_NO_VALUE(*node,NULL);
    (*node) = (*node)->next;
    return;
}

static NodeResult overrideInput(char** old_val,const char* new_val)
{
    char* copy_of_new_val = getCopyOfString(new_val);
    RETURN_ON_NULL(copy_of_new_val,NODE_OUT_OF_MEMORY);
    free(*old_val);
    *old_val=copy_of_new_val;
    return NODE_SUCCESS;
}

