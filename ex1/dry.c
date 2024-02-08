#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

char* stringDuplicator(char* s, int times){
assert(s != NULL);
assert(times > 0);

int len = strlen(s);
char* out = malloc(len*times*sizeof(*out) + 1);

if(out == NULL){
    return NULL;
}
out[len*times] = '\0';
char* ptr = out;

for (int i=0; i<times; i++){
    strcpy(ptr,s);
    ptr = ptr + len;
}
return out;
}


typedef struct node_t {
int val;
struct node_t *next;
} *Node;

bool isListSorted(Node list){
    return true;
}

Node mergeSortedLists(Node list1, Node list2){

    if(list1 == NULL || list2 == NULL){
        return NULL;
    }

    if(!isListSorted(list1) || !isListSorted(list2)){
        return NULL;
    }

    Node listPtr1 = list1;
    Node listPtr2 = list2;
    Node mergedList = malloc(sizeof(*mergedList));
    Node nodePtr = mergedList;

    while(listPtr1 != NULL && listPtr2!= NULL)
    {
        if(listPtr1->val < listPtr2->val){
            nodePtr->val = listPtr1->val;     
            listPtr1 = listPtr1->next;     
        } 
        else {
            nodePtr->val = listPtr2->val;
            listPtr2 = listPtr2->next;
        }     
        nodePtr->next = malloc(sizeof(*nodePtr));;
        nodePtr = nodePtr->next;
    }


    while(listPtr1 != NULL){
        nodePtr->val = listPtr1->val;     
        listPtr1 = listPtr1->next;
        nodePtr->next = malloc(sizeof(*nodePtr));;
        nodePtr = nodePtr->next;
    }
    while(listPtr2 != NULL){
        nodePtr->val = listPtr2->val;     
        listPtr2 = listPtr2->next;
        nodePtr->next = malloc(sizeof(*nodePtr));;
        nodePtr = nodePtr->next;
    }
    
    free(nodePtr);

    return mergedList;
}


