#include "stdbool.h"
#include <stdlib.h> // used for NULL

typedef struct node_t
{
	int x;
	struct node_t *next;
} * Node;

typedef enum
{
	SUCCESS = 0,
	MEMORY_ERROR,
	EMPTY_LIST,
	UNSORTED_LIST,
	NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out);
ErrorCode checkInputArguements(Node list1, Node list2, int *length1, int *length2);
int getNextValueForList(Node* node_in_list1, Node* node_in_list2);
ErrorCode allocateNextNode(Node *current_node, bool first_iteration);

int getListLength(Node list)
{
	return 2;
}
bool isListSorted(Node list)
{
	return true;
}
/*  Function checks which next value in ascending order value-wise should be added to the merged list.
	Also iterates the node from which the value was taken
 Error Codes:  None. Assumes both list are valid as they were validated already
 Returns    :  Value to add to the linked list  */
int getNextValueForList(Node* node_in_list1, Node* node_in_list2)
{
	Node* temp_ptr;
	int next_val;

	if (!(*node_in_list1))
	{
		temp_ptr = node_in_list2;
	}
	else if (!(*node_in_list2))
	{
		temp_ptr = node_in_list1;
	}

	else if ((*node_in_list1)->x < (*node_in_list2)->x)
	{
		temp_ptr = node_in_list1;
	}
	else
	{
		temp_ptr = node_in_list2;
	}
	
	next_val =(*temp_ptr)->x;
	(*temp_ptr) = (*temp_ptr)->next;
	return next_val;
}
/*  Function checks given arguement for mergeSortedlist functions, and calculates length on the way.
 Error Codes:	MEMORY_ERROR - Allocation error
 				NULL_ARGUEMENT,UNSORTED_LIST,EMPTY_LIST - See "checkInputArguements" function
 Returns    :  ErrorCode indicating successfull/unsuccessfull merging  */
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out)
{
	int length1, length2;
	ErrorCode input_check_code;
	bool first_iteration=true;
	Node node_in_list1, node_in_list2, node_merged_head;

	// Check if arguements are valid
	if ((input_check_code = checkInputArguements(list1, list2, &length1, &length2)) != SUCCESS)
	{
		return input_check_code;
	}

	node_in_list1 = list1; // Iterate on dummy nodes so original list won't be overriden
	node_in_list2 = list2;

	while ((node_in_list1 || node_in_list2))
	{
	
		if (allocateNextNode(&node_merged_head,first_iteration) == MEMORY_ERROR)
		{
			*merged_out = NULL;
			return MEMORY_ERROR;
		}
		else if(first_iteration)
		{
			first_iteration=false;
				*merged_out = node_merged_head;
		}


		node_merged_head->x = getNextValueForList(&node_in_list1, &node_in_list2);


	}

	//node_merged_head = NULL;
	return SUCCESS;
}
/*  Function allocates next node to given node, and cycles to the allocated node.
	If it is the first iteration - allocate current node.
 Error Codes:  Allocation error - MEMORY_ERROR
 Returns    :  ErrorCode indicating successfull/unsuccessfull allocations  */
ErrorCode allocateNextNode(Node *current_node, bool first_iteration)
{
	if (first_iteration)
	{
		(*current_node) = (Node *)malloc(sizeof(Node));
	}
	else
	{

		(*current_node)->next = (Node *)malloc(sizeof(Node));
		(*current_node) = (*current_node)->next;
	}

	if (!((*current_node)))
	{

		return MEMORY_ERROR;
	}
	(*current_node)->next=NULL;
	return SUCCESS;
}
/*  Function checks given arguement for mergeSortedlist functions, and calculates length on the way.
 Error Codes:  At least one of the lists are empty - NULL_ARGUEMENT
			   At least one of the lists are unsorted - UNSORTED_LIST
			   At least one of the lists are empty - EMPTY_LIST
 Returns    :  ErrorCode indicating valid/invalid arguements  */
ErrorCode checkInputArguements(Node list1, Node list2, int *length1, int *length2)
{
	if (!list1 || !list2)
	{
		return NULL_ARGUMENT;
	}
	if (!isListSorted(list1) || !isListSorted(list2))
	{
		return UNSORTED_LIST;
	}
	*length1 = getListLength(list1);
	*length2 = getListLength(list2);
	if (*length1 == 0 || *length2 == 0)
	{
		return EMPTY_LIST;
	}
	return SUCCESS;
}
int main()
{
	Node list1 = NULL;
	list1 = (Node *)malloc(sizeof(Node));
	list1->x = 1;
	list1->next = (Node *)malloc(sizeof(Node));
	list1->next->x = 4;
	list1->next->next = NULL;

	Node list2 = NULL;
	list2 = (Node *)malloc(sizeof(Node));
	list2->x = 3;
	list2->next = (Node *)malloc(sizeof(Node));
	list2->next->x = 6;
	list2->next->next = NULL;
	Node merged = NULL;
	mergeSortedLists(list1, list2, &merged);
	return 0;
}