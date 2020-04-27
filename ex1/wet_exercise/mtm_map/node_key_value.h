#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>


typedef struct node_t* NodeKeyValue;

NodeKeyValue NodeCreate();

void NodeDestroy(NodeKeyValue node);

char* NodeGetKey (NodeKeyValue node);

char* NodeGetValue(NodeKeyValue node);

NodeKeyValue NodeGetNext(NodeKeyValue node);

void NodePutNext(NodeKeyValue node, NodeKeyValue new_next);

void NodePutkey(NodeKeyValue node, char* new_key);

void NodePutValue(NodeKeyValue node, char* new_value);

void NodePromoteToNext(NodeKeyValue* node);

#endif