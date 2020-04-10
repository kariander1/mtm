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
ErrorCode copyElementxToMerged(Node* merged, Node* current_list, Node* other_list, bool last_check);

bool isListSorted(Node list) {
	return true;
}

ErrorCode copyElementxToMerged(Node* merged, Node* current_list, Node* other_list, bool last_check) {
	(*merged)->x = (*current_list)->x;
	(*merged)->next = malloc(sizeof(Node));
	if ((*merged)->next == NULL) {
		free((*current_list));
		free((*other_list));
		distroyMergedNexts((*merged));
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
	int list1_len = 2;
	int list2_len = 1;
	//int list1_len = getListLength(list1);
	//int list2_len = getListLength(list2);
	if ((!list1_len) || (!list2_len)) {
		return EMPTY_LIST;
	}
	if ((!isListSorted(list1)) || (!isListSorted(list2))) {
		return UNSORTED_LIST;
	}
	Node merged_head = malloc(sizeof(Node));
	if (merged_head == NULL) {
		return MEMORY_ERROR;
	}
	*merged_out = merged_head;
	Node ptr_list1 = malloc(sizeof(*ptr_list1));
	if (ptr_list1 == NULL) {
		free(merged_head);
		return MEMORY_ERROR;
	}
	Node ptr_list2 = malloc(sizeof(*ptr_list1));
	if (ptr_list2 == NULL) {
		free(ptr_list1);
		free(merged_head);
		return MEMORY_ERROR;
	}
	ptr_list1 = list1;
	ptr_list2 = list2;
	while ((ptr_list1 != NULL) && (ptr_list2 != NULL)) {
		if ((ptr_list1->x) <= (ptr_list2->x)) {
			ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list1, &ptr_list2, false);
			if (check_success == MEMORY_ERROR) {
				return MEMORY_ERROR;
			}
		}
		else {
			ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list2, &ptr_list1, false);
			if (check_success == MEMORY_ERROR) {
				return MEMORY_ERROR;
			}
		}
	}
	while (ptr_list2 != NULL) {
		ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list2, &ptr_list1, true);
		if (check_success == MEMORY_ERROR) {
			return MEMORY_ERROR;
		}
	}
	while (ptr_list1 != NULL) {
		ErrorCode check_success = copyElementxToMerged(&merged_head, &ptr_list1, &ptr_list2, true);
		if (check_success == MEMORY_ERROR) {
			return MEMORY_ERROR;
		}			
	}
	merged_head->next= NULL;
	//*merged_out = merged_head;
	free(ptr_list1);
	free(ptr_list2);
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
distroyMergedNexts(left);
	right = malloc(sizeof(Node));
	right->x = 8;
	right->next = NULL;

	ErrorCode result = mergeSortedLists(left, right, &merged);
	printf("%d\n", result);
	while (merged != NULL) {
		printf("%d ", merged->x);
		merged = merged->next;
	}
	distroyMergedNexts(left);
	distroyMergedNexts(right);
	distroyMergedNexts(merged);

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
