#include <stdio.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream){

    if(in_stream == NULL){
        reutrn NULL;
    }

    RLEList list = RLEListCreate();

    if(list == NULL){
        return NULL;
    }

    char current_char;

    current_char = fgetc(in_stream);

    while (current_char != EOF) {
        RLEListResult result = RLEListAppend(list, current_char);
        if (result != RLE_LIST_SUCCESS) {
            RLEListDestroy(list);
            return NULL;
        }
        current_char = fgetc(in_stream);
    }

    return list;
}


// Function to write ASCII art from RLE list to a file stream
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream) {
    // Check if a NULL pointer was sent as one of the parameters
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList current = list;
    while (current != NULL){
        int len = current->len;
        char letter = current->letter;
        for(int i = 0; i<len; i++){
            fputs(letter, out_stream);        
        }
    }   
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream){
// Check if a NULL pointer was sent as one of the parameters
    if (list == NULL || out_stream == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    // Export the RLE list to a string
    RLEListResult result;
    char* output = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }


    char currentChar = output[0];
    int index = 0;

    while(currentChar != '\0'){
        puts(currentChar, out_stream);
        index++;
        currentChar = output[index];
    }
    free(output);
    return RLE_LIST_SUCCESS;
}


