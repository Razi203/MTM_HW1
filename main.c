#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AsciiArtTool.h"

#define INVERTED "-i"
#define ENCODED "-e"

/**
 * A helping function to invert a char as desired, switching ' ' and '@'.
*/
char invertChar(char c){
    if (c == ' '){
        return '@';
    }
    if (c == '@'){
        return ' ';
    }
    return c;
}

/**
 * The main function - prints an encoded or inverted version of a file to another file.
 * Usage: ./executable <flags> <source> <target>
 * @param flags - There are two flags to use one of them:
 * '-e' - prints the encoded source file into the target file.
 * '-i' - prints the inverted source file into the target file.
 * @param source - The source file to take the data from.
 * @param target - The target file to print the desired output to.
*/
int main(int argc, char **argv){
    if (argc != 4){
        return 0;
    }
    char *flags = argv[1];
    if (strcmp(flags,INVERTED) != 0 && strcmp(flags,ENCODED)){
        return 0;
    }
    FILE* source = fopen(argv[2], "r");
    if (!source){
        return 0;
    }
    FILE* target = fopen(argv[3], "w");
    if (!target){
        fclose(source);
        return 0;
    }
    
    RLEList list = asciiArtRead(source);
    if(list == NULL){
        fclose(source);
        fclose(target);
        return 0;
    }
    if (strcmp(flags, ENCODED) == 0){
        RLEListResult result = asciiArtPrintEncoded(list, target);
        fclose(source);
        fclose(target);
        RLEListDestroy(list);
        return 0;
    }
    if (strcmp(flags, INVERTED) == 0){
        RLEListMap(list, invertChar);
        RLEListResult result = asciiArtPrint(list, target);
        fclose(source);
        fclose(target);
        RLEListDestroy(list);
        return 0;
    }
}
