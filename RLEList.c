#include "RLEList.h"

struct RLEList_t {
    char val;
    int count;
    struct RLEList_t *next;
};

//implement the functions here

RLEList RLEListCreate(){
    RLEList new_list = malloc(sizeof(*new_list));
    if (!new_list){
        return NULL;
    }
    new_list -> next = NULL;
    new_list -> count = 0;
    new_list -> val = 0;
    return new_list;
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
    if (list -> count == 0){
        list -> val = value;
        list -> count++;
        return RLE_LIST_SUCCESS;
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
    while(list != NULL){
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
    while (index >= list->count){
        index -= list->count;
        prev = list;
        list = list -> next;
    }

    if (list -> count > 1){
        list -> count--;
        return RLE_LIST_SUCCESS;
    }
    if (list -> next == NULL){
            list -> count = 0;
            return RLE_LIST_SUCCESS;
    }
    if (prev == list){
        RLEList to_be_removed = list -> next;
        list -> val = to_be_removed -> val;
        list -> next = to_be_removed -> next;
        list -> count = to_be_removed -> count;
        free(to_be_removed);
        return RLE_LIST_SUCCESS;
    }
    prev -> next = list -> next;
    free(list);
    if (prev -> val == prev -> next -> val){
        RLEList to_be_removed = prev -> next;
        prev -> count += to_be_removed -> count;
        prev -> next = to_be_removed -> next;
        free(to_be_removed);
    }
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if (list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;    
        }
        return 0;
    }
    if(index < 0 || index >= RLEListSize(list)){
        if (result != NULL){
            *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;            
        }
        return 0;
    }

    int currentIndex=0;
    while(list != NULL && (currentIndex + list->count <= index)){
        currentIndex += list->count;
        list = list->next;
    }
    
    char returnedChar = list->val;
    
    if (result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return returnedChar;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList prev = list;
    while (list != NULL){
        list -> val = map_function(list -> val);
        if (prev != list && prev -> val == list -> val){
            prev -> count += list -> count;
            prev -> next = list -> next;
            free(list);
            list = prev;
        }
        prev = list;
        list = list -> next;
    }
    return RLE_LIST_SUCCESS;
}

int countDigits(RLEList list){
    int digits = 0;
    while (list != NULL){
        int num = list -> count;
        while (num > 0){
            digits++;
            num /= 10;
        }
        list = list -> next;
    }
    return digits;
}

void reverseString(char *str, int size){
    while (size > 1){
        char temp = *str;
        *str = str[size-1];
        *(str++ + size-1) = temp;
        size -= 2;
    }
}


char* RLEListExportToString(RLEList list, RLEListResult* result){
    if(list==NULL){
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int RLEListLen=0;
    RLEList head=list;
    while(head && head -> count != 0){
        RLEListLen++;
        head=head->next;
    }
    int size = 2*RLEListLen + countDigits(list);
    char *returnedStr = malloc(size + 1);
    if(returnedStr==NULL){
        if (result != NULL){
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    int i = 0;
    while(i < size){
        returnedStr[i++] = list->val;
        int start = i, num = list -> count;
        while(num > 0){
            returnedStr[i++] = num % 10 + '0';
            num /= 10;
        }
        reverseString(returnedStr + start, i - start);
        returnedStr[i++] = '\n';
        list=list->next;
    }
    returnedStr[size]='\0';
    
    if (result != NULL){
        *result=RLE_LIST_SUCCESS;   
    }
    return returnedStr;
}

