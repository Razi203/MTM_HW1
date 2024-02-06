#include "AsciiArtTool.h"

/**
 * The function scans a single letter every time and appends it to a new list. 
*/
RLEList asciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    if(list == NULL){
        return list;
    }
    char current;
    while (fscanf(in_stream, "%c", &current) == 1) {
        RLEListResult result = RLEListAppend(list, current);
        if(result != RLE_LIST_SUCCESS){
            RLEListDestroy(list);
            return NULL;
        }
    }
    return list;
}

/**
 * using fputs the function adds every letter while going through all possible indices.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    if (list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char string[2] = " ";
    for(int i = 0; i < RLEListSize(list); i++){
        char letter = RLEListGet(list, i, &result);
        if (result != RLE_LIST_SUCCESS){
            return result;
        }
        string[0] = letter;
        fputs(string, out_stream);
    }
    return RLE_LIST_SUCCESS;
}

/**
 * Using the RLEListExportToString, the function encodes the list then prints it to the file using fupts.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    if (list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char *string = RLEListExportToString(list, &result);
    if(result != RLE_LIST_SUCCESS){
        return result;
    }
    fputs(string,out_stream);
    free(string);
    return RLE_LIST_SUCCESS;
}



