#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>


typedef struct node_t* NodeKeyValue;

NodeKeyValue NodeCreate();

void NodeDestroy(NodeKeyValue node);

NodeKeyValue NodeGetKey (NodeKeyValue node);

NodeKeyValue NodeGetValue(NodeKeyValue node);

NodeKeyValue NodeGetNext(NodeKeyValue node);

void NodePutNext(NodeKeyValue node, NodeKeyValue new_next);

void NodePutkey(NodeKeyValue node, NodeKeyValue new_key);

void NodePutValue(NodeKeyValue node, NodeKeyValue new_value);

#endif