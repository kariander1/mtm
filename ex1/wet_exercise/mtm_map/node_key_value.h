#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>


typedef struct node_t* NodeKeyValue;

NodeKeyValue nodeCreate();

void nodeDestroy(NodeKeyValue node);

char* nodeGetKey (NodeKeyValue node);

char* nodeGetValue(NodeKeyValue node);

NodeKeyValue nodeGetNext(NodeKeyValue node);

void nodePutNext(NodeKeyValue node, NodeKeyValue new_next);

bool nodePutkey(NodeKeyValue node,const char* new_key);

bool nodePutValue(NodeKeyValue node,const char* new_value);

void nodePromoteToNext(NodeKeyValue* node);

#endif