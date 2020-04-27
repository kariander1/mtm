#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
//question1
typedef struct node_t {
	int x;
	struct node_t *next;
} *Node;

typedef enum {
	SUCCESS = 0,
	MEMORY_ERROR,
	EMPTY_LIST,
	UNSORTED_LIST,
	NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out);
void distroyMergedNexts(Node merged_head);
ErrorCode copyElementxToMerged(Node* merged, Node* current_list, Node* other_list, bool last_check, Node all_merged_for_distroy);

bool isListSorted(Node list) {
	return true;
}

ErrorCode copyElementxToMerged(Node* merged, Node* current_list, Node* other_list, bool last_check, Node all_merged_for_distroy) {
	(*merged)->x = (*current_list)->x;
	(*merged)->next = malloc(sizeof(*(*merged)));
	if ((*merged)->next == NULL) {
		distroyMergedNexts(all_merged_for_distroy);
		return MEMORY_ERROR;
	}
	(*current_list) = (*current_list)->next;
	if ( (!last_check)  || ((last_check) && ((*current_list) != NULL))){ // only if it is the last check and the next address is NULL the merged will not be promoted.
		(*merged) = (*merged)->next;
	}
	return SUCCESS;
}
void distroyMergedNexts(Node connected_list) {
	while (connected_list) {
		Node todelete = connected_list;
		connected_list = connected_list->next;
		free(todelete);
	}
}
ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out) {
	if ((!list1) && (!list2)) {
		return NULL_ARGUMENT;
	}
	//int list1_len = 2;
	//int list2_len = 1;
	int list1_len = getListLength(list1);
	int list2_len = getListLength(list2);
	if ((!list1_len) || (!list2_len)) {
		return EMPTY_LIST;
	}
	if ((!isListSorted(list1)) || (!isListSorted(list2))) {
		return UNSORTED_LIST;
	}
	Node merged_head = malloc(sizeof(*merged_head));
	if (merged_head == NULL) {
		return MEMORY_ERROR;
	}
	*merged_out = merged_head;

	Node ptr_list1 = list1; 
	Node ptr_list2 = list2;
	while ((ptr_list1 != NULL) && (ptr_list2 != NULL)) {
		if ((ptr_list1->x) <= (ptr_list2->x)) {
			ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list1, &ptr_list2, false,*merged_out );
			if (check_success == MEMORY_ERROR) {
				return MEMORY_ERROR;
			}
		}
		else {
			ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list2, &ptr_list1, false, *merged_out);
			if (check_success == MEMORY_ERROR) {
				return MEMORY_ERROR;
			}
		}
	}
	while (ptr_list2 != NULL) {
		ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list2, &ptr_list1, true, *merged_out);
		if (check_success == MEMORY_ERROR) {
			return MEMORY_ERROR;
		}
	}
	while (ptr_list1 != NULL) {
		ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list1, &ptr_list2, true, *merged_out);
		if (check_success == MEMORY_ERROR) {
			return MEMORY_ERROR;
		}			
	}
	free(merged_head->next);
	merged_head->next= NULL;
	return SUCCESS;
}

int main() {
	Node merged = NULL;
	Node left = NULL, right = NULL;
	left = malloc(sizeof(*left));
	left->x = 5;
	left->next = malloc(sizeof(*left));
	left->next->x = 10;
	left->next->next = NULL;

	right = malloc(sizeof(*right));
	right->x = 8;
	right->next = NULL;

	ErrorCode result = mergeSortedLists(left, right, &merged);
	distroyMergedNexts(left);
	distroyMergedNexts(right);
	if (result !=MEMORY_ERROR ){
		Node new_merged = merged;
		while (new_merged != NULL) {
			printf("%d ", new_merged->x);
			new_merged = new_merged->next;
	}
		distroyMergedNexts(merged);
	}
}


/*
//question2
char *duplicete_string(char *str_in, int times) {
	assert(str_in);
	assert(times > 0);
	int len = strlen(str_in);
	char *str_out = malloc((len*times) +1);
	if (str_out == NULL) :
		return NULL;
	//char* start_str_out = str_out;
	for (int i = 0; i < times; i++) {
		strcpy(str_out +i*len, str_in);
		//str_out = str_out + LEN
	}
	return str_out;
}

*/
