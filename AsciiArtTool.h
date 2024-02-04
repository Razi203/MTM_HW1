#ifndef ASCII_TOOLS_H
#define ASCII_TOOLS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream){
    RLEList list=RLEListCreate();
    if(NULL==list){
      return list;
    }
        char current[1];
        while (fgets(current, 1, in_stream) != NULL) {
            RLEListResult result=RLEListAppend(list, current[1]);
            if(result!=RLE_LIST_SUCCESS){
                RLEListDestroy(list);
                return NULL;
            }
        }
    return  list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    if (list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list != NULL){
        int size = list -> count;
        char *string = (char*)malloc(size + 1);
        if (string == NULL){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        for (int i = 0; i < size; i++){
            *(string + i) = list -> val;
        }
        *(string + size) = '\0';
        fputs(string, out_stream);
        free(string); 
    }
    return RLE_LIST_SUCCESS;
}


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





#endif // ASCII_TOOLS_H