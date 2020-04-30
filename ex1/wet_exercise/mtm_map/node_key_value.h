#ifndef NODEKEYVALUE_H_

#include <stdbool.h>
#include <string.h>


typedef struct node_t* NodeKeyValue;

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

void nodePutNext(NodeKeyValue node, NodeKeyValue new_next);

bool nodePutkey(NodeKeyValue node,const char* new_key);

bool nodePutValue(NodeKeyValue node,const char* new_value);

void nodePromoteToNext(NodeKeyValue* node);

#endif