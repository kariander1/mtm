#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>

typedef struct node_t* NodeKeyValue;

typedef enum nodeResult_t {
    NODE_OUT_OF_MEMORY=1,
    NODE_NULL_ARGUEMENT,
    NODE_SUCCESS
} NodeResult;
/**
* nodeCreate: creates a new node with key and value 
* initial all nodeKeyValue attributes to NULL
*
* @return
* 	NULL - if allocation failed.
* 	else returns the pointer to the new node 
*/
NodeKeyValue nodeCreate();

/**
* nodeDestroy: deletes a given NodeKeyValue
* frees the key and the value inside (that was allocated insode the node) 
*
* @param node - The node to destroy
* @return
* 	void function - does not return anything 
*/
void nodeDestroy(NodeKeyValue node);

/**
* nodeGetKey: gets the key in NodeKeyValue
*
* @param node - The node to get the key from
* @return
* 	NULL - if node is empty
* 	else returns  the key in NodeKeyValue
*/
char* nodeGetKey (NodeKeyValue node);

/**
* nodeGetValue: gets the value in NodeKeyValue
*
* @param node - The node to get the value from
* @return
* 	NULL - if node is empty
* 	else returns the value in NodeKeyValue
*/
char* nodeGetValue(NodeKeyValue node);

/**
* nodeGetNext: gets the next NodeKeyValue in  the current NodeKeyValue
*
* @param node - The node to get the next from
* @return
* 	NULL - if node is empty
* 	else returns the next NodeKeyValue
*/
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
NodeResult nodePutkey(NodeKeyValue node,const char* new_key);
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
NodeResult nodePutValue(NodeKeyValue node,const char* new_value);
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