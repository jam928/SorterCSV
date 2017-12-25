#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.c"
#include "linked_list.c"


void writeNewCsvfile(linkedList* llist) {
    /*char const *newFileName = "sortedmovies.csv";
    //FILE *fp = fopen(newFileName, "w");
    if(fp == NULL) {
        printf("Invalid file name\n");
    }
    */
    int i;
    // write the header row
    for(i = 0; i < llist->numberOfColumns; i++) {
        if(i != llist->numberOfColumns-1) {
            fprintf(stdout, "%s,", llist->columns[i]);
        }
        else {
            fprintf(stdout, "%s\n", llist->columns[i]);
        }
    }

    Node* cur = llist->front;
    while(cur != NULL) {
        if(cur->nodeData.comma == NULL) {
            
            for(i = 0; i < llist->numberOfColumns; i++) {
                if(i != llist->numberOfColumns-1) {
                    fprintf(stdout, "%s,", cur->nodeData.columndata[i]);
                }

                else {
                    fprintf(stdout, "%s\n", cur->nodeData.columndata[i]);
                }
            }
        }
        else {
            for(i = 0; i < llist->numberOfColumns; i++) {
                if((cur->nodeData.comma[i]) == 0) {
                    if(i != llist->numberOfColumns-1) {
                        fprintf(stdout,"%s,", cur->nodeData.columndata[i]);
                    }
                    else {
                        fprintf(stdout, "%s\n", cur->nodeData.columndata[i]);
                    }
                }
                else {
                    if(i != llist->numberOfColumns - 1){
                        fprintf(stdout,"\"%s\",", cur->nodeData.columndata[i]);
                    }
                    else {
                        fprintf(stdout,"\"%s\"\n",cur->nodeData.columndata[i]);
                    }
                }
            }
        }
        cur = cur->next;
    }
    //fclose(fp); to use fp replace fp with stdout
}
int main(int argc, char *argv[]) {
    // read the file into a file pointer
    FILE *file;
    file = stdin;
    
    // dymincally allocate memory for the linked list
    linkedList* llist = (linkedList*) malloc(sizeof(linkedList));

    char* buffer = (char*) malloc(sizeof(char)*1000);
    memset(buffer,0,sizeof(char)*1000);

    // skip the header line(1st row)
    fgets(buffer,1000,file);

    // load list
    loadlist(llist,buffer);

    char character;
    int current = 0;
    int counter = 0;
    int index = 0;
    int quote = 0;
    data datanode = {};
    //int numberOfColumns = llist->numberOfColumns;
// printf("number of columns: %d",llist->numberOfColumns);
    datanode.columndata = (char**) malloc(sizeof(char*)*llist->numberOfColumns);
    datanode.comma = NULL;
    memset(buffer,0,sizeof(char)*1000);

    while((character = fgetc(file)) != EOF) {

        // check to see if youre at the end of the record index 
        // ex if its color it will store in the datanode 
        if((character == ',' || character == '\n') && (quote == 0)) {
            datanode.columndata[current] = strdup(buffer);

            if(character == '\n') {
                addLast(llist, datanode);
                counter++;
		current = 0;
                index = 0;
                memset(buffer,0, sizeof(char)*1000);
                datanode.columndata = (char**) malloc(sizeof(char*)*llist->numberOfColumns);
                datanode.comma = NULL;
            }

            else {
                current++;
                index = 0;
                memset(buffer,0,sizeof(char)*1000);
            }
        }
        else if(character == '"') {
            if(quote == 0) {
                datanode.comma = (int*) malloc(sizeof(int)*llist->numberOfColumns);
                memset(datanode.comma, 0, sizeof(sizeof(int)*llist->numberOfColumns));
                datanode.comma[current] = 1;
                quote = 1;
            }
            else {
                quote = 0;
            }
        }
        else {
            buffer[index] = character;
            index++;
        }
    }

    free(datanode.columndata);
    free(buffer);

    definelisttypes(llist);

    // read the column to sort 
    if(argc >= 3) {
        if(strcmp("-c", argv[1]) == 0) {
            startMergeSort(llist, argv[2]);
        }
    }

    writeNewCsvfile(llist);
    freeLinkedList(llist);
}