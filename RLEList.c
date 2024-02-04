#include "RLEList.h"

typedef struct RLEList_t {
    char val;
    int count;
    struct RLEList_t *next;
}*RLEList;

//implement the functions here

RLEList RLEListCreate(){
    RLEList new_list = malloc(sizeof(*new_list));
    if (!new_list){
        return NULL;
    }
    new_list -> next = NULL;
    new_list -> count = 0;
    
}


void RLEListDestroy(RLEList list){
    while(list){
    RLEList toDestroy=list;
    list=list->next;
    free(toDestroy);
}
}



RLEListResult RLEListAppend(RLEList list, char value){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list -> next != NULL){
        list = list -> next;
    }
    if (list -> val == value){
        list -> count++;
        return RLE_LIST_SUCCESS;
    }
    RLEList node = RLEListCreate();
    if (node == NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    node -> count = 1;
    node -> val = value;
    node -> next = list -> next;
    list -> next = node;
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list){
    if(list == NULL){
        return -1;
    }
    int size = 0;
    while(list){
        size += list->count;
        list = list->next;
    }
    return size;
}


RLEListResult RLEListRemove(RLEList list, int index){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0 || index >= RLEListSize(list)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList prev = list;
    while (index > list->count){
        index -= list->count;
        prev = list;
        list = list -> next;
    }

    if (list -> count > 1){
        list -> count--;
        return RLE_LIST_SUCCESS;
    }

    if (prev == list){
        if (list -> next == NULL){
            list -> count = 0;
            return RLE_LIST_SUCCESS;
        }
        RLEList to_be_removed = list -> next;
        list -> val = to_be_removed -> val;
        list -> next = to_be_removed -> next;
        list -> count = to_be_removed -> count;
        free(to_be_removed);
        return RLE_LIST_SUCCESS;
    }
    prev -> next = list -> next;
    free(list);
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if (list == NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(index < 0 || index >= RLEListSize(list)){
        *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    int currentIndex=0;
    while(list && (currentIndex<index)){
        currentIndex += list->count;
        list = list->next;
    }
    char returnedChar=list->val;
    *result=RLE_LIST_SUCCESS;
    return returnedChar;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    while (list != NULL){
        list -> val = map_function(list -> val);
        list = list -> next;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    if(list==NULL){
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int RLEListLen=0;
    RLEList head=list;
    while(head){
        RLEListLen++;
        head=head->next;
    }
    char *returnedStr = malloc(3*RLEListLen);
    if(returnedStr==NULL){
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
     for(int i = 0; i < RLEListLen; i++){
        returnedStr[i*3] = list->val;
        returnedStr[i*3 +1] = list->count;
        returnedStr[i*3 +2] = '\n';
        list=list->next;
     }
    returnedStr[3*RLEListLen]='\0';
    *result=RLE_LIST_SUCCESS;
    return returnedStr;
}
