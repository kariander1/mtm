#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>


typedef struct node_t* NodeKeyValue;

NodeKeyValue nodeCreate();

void nodeDestroy(NodeKeyValue node);

char* nodeGetKey (NodeKeyValue node);

char* nodeGetValue(NodeKeyValue node);

NodeKeyValue nodeGetNext(NodeKeyValue node);
/**
* 	nodePutNext: Sets the next node of the given node to be the next node given
*
* @param node -
* 	The node which to set its next_node property
* @param new_next -
*   The next node to be set
* @return
* 	None
*/
void nodePutNext(NodeKeyValue node, NodeKeyValue new_next);
/**
* 	nodePutkey: Set the current value of the node to be the given string.
*   Allocates a new string, and releases the old one in case it existed 
*
* @param new_key -
* 	The new key to be written
* @return
* 	Boolean whether writing the new key was successfull.
*   If false - then assumed there is a memory error.
*/
bool nodePutkey(NodeKeyValue node,const char* new_key);
/**
* 	nodePutValue: Set the current value of the node to be the given string.
*   Allocates a new string, and releases the old one in case it existed 
*
* @param new_value -
* 	The new value to be written
* @return
* 	Boolean whether writing the new value was successfull.
*   If false - then assumed there is a memory error.
*/
bool nodePutValue(NodeKeyValue node,const char* new_value);
/**
* 	nodePromoteToNext: Promotes the given node to the next node. Next node can be NULL
*
* @param node -
* 	The node to promote
* @return
* 	None
*/
void nodePromoteToNext(NodeKeyValue* node);

#endif