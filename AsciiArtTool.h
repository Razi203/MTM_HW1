#ifndef ASCII_TOOLS_H
#define ASCII_TOOLS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RLEList.h"

/**
*
* Handles Files and RLE List together.
*
* The following functions are available:
*   asciiArtRead                - Creates a new RLE list from a given file.
*   asciiArtPrint               - Writes a given RLE list to a given file.
*   asciiArtPrintEncoded        - Write an encoded RLE list to a given file.
*/




/**
*   asciiArtRead: Creates a new RLE list from a given file.
*
* @param in_stream - The file which to make the list from.
* @return
* 	NULL if an allocation failed.
* 	A new RLE list with the files date in case of success.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
*   asciiArtPrint: Writes a given RLE list to a given file.
*
* @param list - The list which from to take the data to be printed from.
* @param out_stream - The file to print the list to.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_SUCCESS the character found at index has been retrieved successfully.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
*   asciiArtPrintEncoded: Write an encoded RLE list to a given file.
*
* @param list - The list which from to take the date to be printed.
* @param out_stream - The file to print the encoded list to.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_SUCCESS the character found at index has been retrieved successfully.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // ASCII_TOOLS_H