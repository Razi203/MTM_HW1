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
    list -> next = node;
    return RLE_LIST_SUCCESS;
}


RLEListResult RLEListRemove(RLEList list, int index){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    
    // returning out of bounds if list is empty or incorrect index
    if (index < 0 || list -> count == 0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    if (index == 0){
        if (list -> count > 1){
            list -> count--;
            return RLE_LIST_SUCCESS;
        }
        if (list -> next == NULL){
            list -> count = 0;
            return RLE_LIST_SUCCESS;
        }
        RLEList to_be_removed = list -> next;
        list -> val = to_be_removed -> val;
        list -> next = to_be_removed -> next;
        free(to_be_removed);
        return RLE_LIST_SUCCESS;
    }

    // moving to the node before the one to be removed
    while (index > 1){
        if (list -> next == NULL){ 
            return RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        list = list -> next;
    }
    if (list -> next == NULL){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    RLEList to_be_removed = list -> next;
    list -> next = to_be_removed -> next;
    free(to_be_removed);
    return RLE_LIST_SUCCESS;
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
