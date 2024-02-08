#include <stdio.h>
#include "AsciiArtTool.h"

char mapInverr(char c){
    if(c == '@'){
        return ' ';
    } 
    else if(c == ' '){
        return '@';
    } 
    else{
        return c;
    }
}


// Function to handle command-line arguments and invoke the appropriate operation
int AsciiArtTool(int argc, char* argv[]) {
    if (argc != 4) {
        return 0;
    }

    const char* flag = argv[1];
    const char* source = argv[2];
    const char* target = argv[3];

    // Check if the flag is valid
    if (strcmp(flag, "-e") != 0 && strcmp(flag, "-i") != 0) {
        return 0;
    }

    FILE* sourceFile = fopen(source, "r");
    if(sourceFile == NULL){
        return 0;
    }
    FILE* targetFile = fopen(target, "w");
    if(targetFile == NULL){
        fclose(sourceFile);
        return 0;
    }

    RLEList list = asciiArtRead(sourceFile);

    if(strcmp(flag, "-e") == 0){   
        RLEListResult resultFlagE = asciiArtPrintEncoded(list, targetFile);
        if(resultFlagE != RLE_LIST_SUCCESS){
            fclose(sourceFile);
            fclose(targetFile);
            return 0;
        }
    } else{
        RLEListResult resultMap = RLEListMap(list, mapInverr);
        if(resultFlagI != RLE_LIST_SUCCESS){
            fclose(sourceFile);
            fclose(targetFile);
            return 0;
        }

        RLEListResult resultFlagI = asciiArtPrint(list, targetFile);  
        if(resultFlagI != RLE_LIST_SUCCESS){
            fclose(sourceFile);
            fclose(targetFile);
            return 0;
        }
    }
    fclose(sourceFile);
    fclose(targetFile);
    return 1;
}

int main(int argc, char* argv[]) {
    return AsciiArtTool(argc, argv);
}