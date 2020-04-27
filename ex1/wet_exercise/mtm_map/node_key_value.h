#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>


typedef struct node_t* NodeKeyValue;

NodeKeyValue NodeCreate();
NodeKeyValue NodeDestroy(NodeKeyValue node);
NodeKeyValue NodeGetKey (NodeKeyValue node);
NodeKeyValue NodeGetValue(NodeKeyValue node);
NodeKeyValue NodeGetNext(NodeKeyValue node);




#endif