#ifndef _SORTER_H_
#define _SORTER_H_
/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set

// data inside the node
typedef struct nodedata {
    char** columndata; // array of strings 
    int* comma;
}data;

// the node itself
typedef struct node {
    data nodeData; // node data
    struct node* next; // next node in the linked list
}Node;

// linked list struct that contains the nodes(movies)
typedef struct LinkedList {
    Node* front; // got to have a front
    Node* tail; // got to have a tail
    int length; // the number of nodes in the list
    int numberOfColumns; // the numbers of columns in the csv file
    int columnToSort; // the column to sort ig.) color is 0 column
    int sortingType; // which type of variable to sort
    int* types; // 0 = string, 1 = int
    char** columns; // keep track of the columns
}linkedList;

//Suggestion: prototype a mergesort function
void startMergeSort(linkedList* llist, char* column);
Node* mergeSort(linkedList* llist, Node* front);
Node* split(Node* front);
Node* merge(linkedList* llist, Node* leftNode, Node* rightNode);
#endif
