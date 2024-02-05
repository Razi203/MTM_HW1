#ifndef ASCII_TOOLS_H
#define ASCII_TOOLS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "RLEList.h"

RLEList asciiArtRead(FILE* in_stream);

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // ASCII_TOOLS_H