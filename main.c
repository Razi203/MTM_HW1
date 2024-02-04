#include <stdio.h>
#include <stdlib.h>
#include "AsciiArtTool.h"

#define INVERTED "-i"
#define ENCODED "-e"

char invertChar(char c);


int main(int argc, char **argv){
    if (argc != 3){
        error("Usage: AsciiArtTool <flags> <source> <target>", NULL);
    }
    char *flags = argv[0];
    if (flags != INVERTED && flags != ENCODED){
        error("Usage: AsciiArtTool <flags> <source> <target>", NULL); // Check Later
    }
    FILE* source = fopen(argv[1], "r");
    if (!source){
        error("Error: can not open", argv[1]);
    }
    FILE* target = fopen(argv[2], "w");
    if (!target){
        fclose(source);
        error("Error: can not open", argv[2]);
    }
    
    RLEList list = asciiArtRead(source);
    if(list == NULL){
        fclose(source);
        fclose(target);
        return RLE_LIST_OUT_OF_MEMORY;
    }

    if (flags == ENCODED){
        RLEListResult result = asciiArtPrintEncoded(list, target);
        fclose(source);
        fclose(target);
        return result;
    }
    if (flags == INVERTED){
        RLEListMap(list, invertChar);
        RLEListResult result = asciiArtPrint(list, target);
        fclose(source);
        fclose(target);
        return result;
    }
}


char invertChar(char c){
    if (c == ' '){
        return '@';
    }
    if (c == '@'){
        return ' ';
    }
    return c;
}