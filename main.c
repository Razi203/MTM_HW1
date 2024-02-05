#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AsciiArtTool.h"

#define INVERTED "-i"
#define ENCODED "-e"

char invertChar(char c);

void error(char* message, char* filename);

int main(int argc, char **argv){
    if (argc != 4){
        //printf("%d\n", argc);
        //error("Usage: AsciiArtTool <flags> <source> <target>", NULL);
        return 0;
    }
    char *flags = argv[1];
    if (strcmp(flags,INVERTED) != 0 && strcmp(flags,ENCODED)){
        //error("Usage: AsciiArtTool <flags> <source> <target>", NULL); // Check Later
        return 0;
    }
    FILE* source = fopen(argv[2], "r");
    if (!source){
        //error("Error: can not open", argv[1]);
        return 0;
    }
    FILE* target = fopen(argv[3], "w");
    if (!target){
        fclose(source);
        //error("Error: can not open", argv[2]);
        return 0;
    }
    
    RLEList list = asciiArtRead(source);
    if(list == NULL){
        fclose(source);
        fclose(target);
        return RLE_LIST_OUT_OF_MEMORY;
    }
    if (strcmp(flags, ENCODED) == 0){
        RLEListResult result = asciiArtPrintEncoded(list, target);
        fclose(source);
        fclose(target);
        RLEListDestroy(list);
        return result;
    }
    if (strcmp(flags, INVERTED) == 0){
        RLEListMap(list, invertChar);
        RLEListResult result = asciiArtPrint(list, target);
        fclose(source);
        fclose(target);
        RLEListDestroy(list);
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


void error(char* message, char* filename){
    printf("%s %s\n", message, filename ? filename : "");
}