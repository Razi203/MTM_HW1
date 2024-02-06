#include <stdio.h>
#include "RLEList.h"

int main(){
    RLEList list = RLEListCreate();
    RLEListAppend(list, 'a');
    RLEListRemove(list, 0);
    printf("##%s##", RLEListExportToString(list, NULL));
    RLEListAppend(list, 'a');
    printf("##%s##", RLEListExportToString(list, NULL));
    RLEListRemove(list, 0);
    RLEListAppend(list, 'b');
    printf("##%s##", RLEListExportToString(list, NULL));
}