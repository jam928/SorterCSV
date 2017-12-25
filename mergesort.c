#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startMergeSort(linkedList* llist, char* column) {
    // check if the list has no front or tail
    if((llist->front == NULL) || (llist->tail == llist->front)) {
        printf("Unable to sort, no record in the csv");
	return;
    }

    int type = 0;
    int columnFound = 0;

    // traverse thru the first row and check if that column name is in the csv
    for(type = 0; type < llist->numberOfColumns; type++) {
        // compare and see if the column entered matches one of the columns from the csv
        if(strcmp(column,llist->columns[type]) == 0) {
		printf("%d\n", type);
            llist->columnToSort = type;
            columnFound = 1;
        }
    }

    if(columnFound == 0) {
        printf("Column not found.\n");
    }

    // find out the column type eg. color is string(0) or duration(1)
    llist->sortingType = llist->types[llist->columnToSort];
    llist->front = mergeSort(llist, llist->front);
}

Node* mergeSort(linkedList* llist, Node* front) {
    // check if the linked list is empty
    if((front == NULL) || (front->next == NULL)) {
        return front;
    }

    Node* middle = split(front);
    front = mergeSort(llist, front);
    middle = mergeSort(llist, middle);

    front = merge(llist,front,middle);

    return front;
}

//return a pointer to a middle node
Node* split(Node* front) {
     // check if the linked list is empty
     if((front == NULL) || (front->next == NULL)) {
        return NULL;
    }
    
    Node* q = front->next;
    Node* p = front;
    

    while(q != NULL) {
        q = q->next;
        if(q != NULL) {
            p = p->next;
            q = q->next;
        }
    }

    Node* middle = p->next;
    p->next = NULL;
    return middle;
}

Node* merge(linkedList* llist, Node* leftNode, Node* rightNode) {
    if(leftNode == NULL) {
        return rightNode;
    }
    else if(rightNode == NULL) {
        return leftNode;
    }
    if(llist->sortingType == 0) {
        char* leftString = leftNode->nodeData.columndata[llist->columnToSort];
        char* rightString = rightNode->nodeData.columndata[llist->columnToSort];

        Node* result = NULL;
	int cmp = strcmp(leftString,rightString);
        if(cmp <= 0) {
            result = leftNode;
            result->next = merge(llist, leftNode->next, rightNode);
        }
        else {
            result = rightNode;
            result->next = merge(llist, leftNode, rightNode->next);
        }
        return result;
    }
    else if(llist->sortingType == 1) {

        Node* result = NULL;
        int leftNumber = atoi(leftNode->nodeData.columndata[llist->columnToSort]);
        int rightNumber = atoi(rightNode->nodeData.columndata[llist->columnToSort]);

        if(leftNumber <= rightNumber) {
            result = leftNode;
            result->next = merge(llist, leftNode->next, rightNode);
        }
        else {
            result = rightNode;
            result->next = merge(llist, leftNode, rightNode->next);
        }
        return result;
    }
}
