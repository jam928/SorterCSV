#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void loadlist(linkedList* llist, char* columns) {
    char* str = strdup(columns);
    char* currentElement = (char*) strtok(str, ",");
    
    int numberOfColumns = 0;
    while(currentElement != 0) {
        numberOfColumns++;
        currentElement = (char*) strtok(NULL, ",");
    }
    llist->numberOfColumns = numberOfColumns;
    llist->types = (int*) malloc(sizeof(int)*llist->numberOfColumns);
    llist->columns = (char**) malloc(sizeof(char*)*llist->numberOfColumns);
    free(str);
    str = strdup(columns);
    currentElement = (char*) strtok(str, ",");
    int i;
    for(i = 0; i < llist->numberOfColumns; i++) {
        if(i == llist->numberOfColumns - 1) {
            // remove the \r and \n
            int removeChar = strcspn(currentElement, "\r\n");
            if(removeChar != 0) {
                currentElement[removeChar] = '\0'; // remove the special characters
            }
        }
        llist->columns[i] = strdup(currentElement);
        currentElement = (char*) strtok(NULL, ",");
    }
    free(str);
    free(currentElement);
}
void addLast(linkedList* llist, data dataNode) {
    Node* node = (Node*) malloc(sizeof(Node)); // dynamically allocate memory for the node
    node->next = NULL;
    node->nodeData = dataNode;
    
    // add the node to the tail
    // check if the front is empty or tail
    if((llist->front == NULL) && (llist->tail == NULL)) {
        llist->front = node;
        llist->tail = node;
        llist->length++;
    }
    // if theres one node in the list
    else if((llist->front == llist->tail)) {
        llist->tail = node;
        llist->front->next = llist->tail;
        llist->length++;
    }
    // if theres more than two nodes
    else {
        llist->tail->next = node;
        llist->tail = node;
        llist->length++;
    }
}

void freeLinkedList(linkedList* llist) {
    Node* node = llist->front;
    int i;
    
    // traverse thru the list and free the linked list!
    while(node != NULL) {
        char** str = node->nodeData.columndata;
        for(i = 0; i < llist->numberOfColumns; i++) {
            free(str[i]);
        }
        free(str);
    Node* oldNode = node;
    node = node->next;
    free(oldNode);
    }

    for(i = 0; i < llist->numberOfColumns; i++) {
        free(llist->columns[i]);
    }

    free(llist->columns);
    free(llist->types);
    free(llist);
}

void definelisttypes(linkedList* llist) {
    // if the linkedlist is null
    if(llist->front == NULL) {
        return;
    }

    Node* curr = llist->front;
    int i;
    for(i = 0; i < llist->numberOfColumns; i++) {
        char* str = curr->nodeData.columndata[i];
        char* str2;
        long longNum = 0;
        float floatNum = 0.0;
        if(i == llist->numberOfColumns-1) {
            // remove the \r and \n
            int removeChar = strcspn(str, "\r\n");
            if(removeChar != 0) {
                str[removeChar] = '\0'; // remove the special characters
            }
        }
        // check if the string has a dot in which case might be a decimal number or a string with a . or period
        if(strchr(str, '.')) {
            floatNum = strtof(str, &str2);
            if((str == str2) || (str2 != (str + strlen(str)))) {
                llist->types[i] = 0; // its a string element
            }
            else {
                llist->types[i] = 2; // its a double
            }
        }
        // else its eiter a string or an int
        else {
            longNum = strtol(str, &str2, 10);
            if((str == str2) || (str2 != (str + strlen(str)))) {
                llist->types[i] = 0;
            }
            else {
                llist->types[i] = 1;
            }
        }
    }
}
