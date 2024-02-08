#include "RLEList.h"
#include <stdlib.h>

struct RLEList_t {
    char letter;
    int len;
    struct RLEList_t* next;
};

//implement the functions here

// create empty RLEList
RLEList RLEListCreate(){
    RLEList newList = malloc(sizeof(*newList));
    // make sure memory allocation worked
    if(newList == NULL){
        return NULL;
    }
    // set defult values
    newList->letter = '\0';
    newList->len = 0;
    newList->next = NULL;
    return newList;
}




// free the memory of all the list
void RLEListDestroy(RLEList list){
    if(list == NULL){
        return;
    }

    // free each node
    while(list) {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}


// add letter to end of the string
RLEListResult RLEListAppend(RLEList list, char value){
    // if a NULL was sent as one of the parameters
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(value == '\0'){
        return RLE_LIST_SUCCESS;
    }


    if(RLEListSize(list) == 0){
        list->letter = value;
        list->len = 1;
        list->next = RLEListCreate();
        return RLE_LIST_SUCCESS;
    }


    RLEList current = list;
    RLEList nextNode = list->next;

    while(nextNode->next != NULL){
        current = nextNode;
        nextNode = nextNode->next;
    }

    if(current->letter == value){
        current->len += 1;
    } 
    else{
        RLEList newNode = RLEListCreate();
        newNode->letter = value;
        newNode->len = 1;
        current->next = newNode;
        newNode->next = nextNode;
    }
    return RLE_LIST_SUCCESS;
}

int numberOfDigits(int num){
    int count = 0;
    while(num != 0){
        count++;
        num /= 10;
    }
    return count;
}

int RLEListStringLen(RLEList list){
    if(list == NULL){
        return 0;
    }
    int stringLen = 0;
    RLEList current = list;
    while(current != NULL){
        int charLen = numberOfDigits(current->len);
        stringLen += charLen + 2;
        current = current->next;
    }
    return stringLen;
}

int RLEListSize(RLEList list){
    if(list == NULL){
        return -1;
    }
    int size = 0;
    RLEList head = list;
    while(head != NULL){
        size+= head->len;
        head = head->next;
    }
    return size;
}

char* intToString(int number, int numberOfDigits){
    char* result = malloc(numberOfDigits*sizeof(*result) + 1);

    if(result == NULL){
        return NULL;
    }
    
    for(int i = numberOfDigits -1; i>=0; i--){
        int digit = number%10;
        result[i] = digit + '0';
        number = number/10;
    }
    result[numberOfDigits] = '\0';
    return result;
}


/*RLEListResult isListValid(RLEList list){
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current = list;

    while(current != NULL){
        if(current->len < 1){
            return RLE_LIST_ERROR;
        }
        current = current->next;
    }
    return RLE_LIST_SUCCESS;
}
*/

// unit the nodes that with same letter
void removeDuplicatesNodes(RLEList list){
    if(list == NULL){
        return;
    }

    RLEList current = list;

    while(current->next != NULL){
        RLEList nextNode = current->next;
        if(current->letter == nextNode->letter){
            current->len += nextNode->len;
            current->next = nextNode->next;
            nextNode->next = NULL;
            RLEListDestroy(nextNode);
        } 
        else{
            current = nextNode;
        }
        
    }
}


RLEListResult RLEListRemove(RLEList list, int index){
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(index > RLEListSize(list) - 1 || index < 0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    if(index == RLEListSize(list)){
        return RLE_LIST_SUCCESS;
    }

    /*if(list->len == 1 && index == 0){

    }*/

    RLEList prev = NULL;
    RLEList current = list;
    int perfixLen = 0;  

    while(perfixLen <= index){
        perfixLen += current->len;
        if(perfixLen > index){
            if(current->len == 1){
                if(prev == NULL){
                    RLEList toDelete = list->next;

                    list->len = list->next->len;
                    list->letter = list->next->letter;
                    list->next = list->next->next;

                    free(toDelete);      
                } else{
                prev->next = current->next;
                free(current);
                }             
            }
            else{
                current->len -= 1;
            }
            removeDuplicatesNodes(list);
            return RLE_LIST_SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    
    return RLE_LIST_ERROR;;
}





char RLEListGet(RLEList list, int index, RLEListResult *result){

    if(list == NULL){
        if(result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }    
        return 0;
    }

    if(index > RLEListSize(list) - 1  || index < 0){
        if(result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }        
        return 0;
    }

    RLEList current = list;
    int perfixLen = 0;  
    char returnedChar = '\0';
    while(current != NULL){
        perfixLen += current->len;
        if(perfixLen >= index){
            *result = RLE_LIST_SUCCESS;
            returnedChar = current->letter;
            return returnedChar;
        }
        current = current->next;
    }

    *result = RLE_LIST_ERROR;
    return 0;
        
    
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){ 
    if(list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList current = list;

    while(current != NULL){
        current->letter = map_function(current->letter);
        current = current->next;
    }

    removeDuplicatesNodes(list);

    return RLE_LIST_SUCCESS;
}




char* RLEListExportToString(RLEList list, RLEListResult *result){
    if(list == NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    RLEList current = list;
    int len = RLEListStringLen(current);
    char* output = malloc(len + 1);

    if(output == NULL){
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }

    int count = 0;
    while(current != NULL){
        int letterNum = current->len;
        int numLen = numberOfDigits(letterNum);
        char* numString = intToString(letterNum, numLen);
        output[count] = current->letter;
        count++;
        for(int i = 0; i<numLen; i++){
            output[count] = numString[i];
            count++;
        }
 
        free(numString);
        output[count] = '\n';
        count++;
        current = current->next;
    }
    *result = RLE_LIST_SUCCESS;
    return output;
}

int main(){
    RLEList list = RLEListCreate();
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'w');
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'w');
    RLEListRemove(list, 0);
    RLEListResult result;
    char* test = RLEListExportToString(list, &result);
    printf("%s", test);
    printf("\n!!!!!!!!!\n");
    char a;
    a = RLEListGet(list, 0, &result);
    //b = RLEListGet(list, 1, &result);
    printf("%c", a);
    //printf("%c", b);
    return 0;
}













