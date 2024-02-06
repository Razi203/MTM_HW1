#include "RLEList.h"
#include <stdlib.h>


/**
*   The RLE list struct implementaion:
*   @param val - The letter the node represents.
*   @param count - The amount of consecutive letters
*   @param next - A pointer to the next node in the list.
*/
struct RLEList_t {
    char val;
    int count;
    struct RLEList_t *next;
};


/**
*   RLEListCreate: Allocates memory for a new empty node (count = 0).
*/
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


/**
*   RLEListDestroy - deallocates all the nodes in the list one by one.
*/
void RLEListDestroy(RLEList list){
    while(list){
        RLEList toDestroy = list;
        list = list -> next;
        free(toDestroy);
    }
}

/**
*   Case 1: the list is empty - count = 0 - the function changed the first node (uninizilized)/
*   Case 2: the given letter is the same as the last node, the function adds to the node count/
*   Case 3: the letter is not the last one, it makes a new node with the given letter and links it to the end.
*/
RLEListResult RLEListAppend(RLEList list, char value){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    // case 1:
    if (list -> count == 0){
        list -> val = value;
        list -> count++;
        return RLE_LIST_SUCCESS;
    }

    while (list -> next != NULL){
        list = list -> next;
    }
    // case 2:
    if (list -> val == value){
        list -> count++;
        return RLE_LIST_SUCCESS;
    }
    // case 3:
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

/**
 * The function goes through each node till the last one (next node is NULL) while adding the count of the node.
*/
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

/**
 * The function removes the letter in the given index if possible - not out of bounds.
 * If the letter is the first node and there are no repetitions, then the next node is duplicated into the first
 * one while removing it, unless there is no other node then empty the list.
 * If the node is emptied out and the next node is has the sane letter as the one before, merge both nodes into one.
*/
RLEListResult RLEListRemove(RLEList list, int index){
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0 || index >= RLEListSize(list)){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList prev = list;
    while (index >= list->count){   // find the wanted node.
        index -= list->count;
        prev = list;
        list = list -> next;
    }

    if (list -> count > 1){     // the node is not emptied out.
        list -> count--;
        return RLE_LIST_SUCCESS;
    }
    if (list -> next == NULL){  // the node is the last one.
        if (prev == list){      // node is the first and only node.
            list -> count = 0;
            return RLE_LIST_SUCCESS;
        }
        free(list);
        prev -> next = NULL;
        return RLE_LIST_SUCCESS;
    }
    if (prev == list){      // node is the first one, duplicate the next one into it.
        RLEList to_be_removed = list -> next;
        list -> val = to_be_removed -> val;
        list -> next = to_be_removed -> next;
        list -> count = to_be_removed -> count;
        free(to_be_removed);
        return RLE_LIST_SUCCESS;
    }
    prev -> next = list -> next;
    free(list);
    if (prev -> val == prev -> next -> val){    // if next node has the same letter then merge them.
        RLEList to_be_removed = prev -> next;
        prev -> count += to_be_removed -> count;
        prev -> next = to_be_removed -> next;
        free(to_be_removed);
    }
    return RLE_LIST_SUCCESS;
}

/**
 * The function loops untill the index is the current node (the next jump will exceed it).
*/
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

/**
 * Changes every letter in the list according to a given function.
 * If two letters become the same then merge them.
*/
RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList prev = list;
    while (list != NULL){
        list -> val = map_function(list -> val);
        if (prev != list && prev -> val == list -> val){ // merging similar nodes.
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

/**
 * A helping function to count how many digits in total the list nodes' counts have.
*/
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

/**
 * A helping function to reverse a given string.
*/
void reverseString(char *str, int size){
    while (size > 1){
        char temp = *str;
        *str = str[size-1];
        *(str++ + size-1) = temp;
        size -= 2;
    }
}

/**
 * The function allocates memory to fit all the node's letters and '\n' and the count,
 * The count is calculed using countDigits. 
 * The function goes through each node in order, appends the letter and writes the digits backwards (easier
 * to calculate) then reverses the number using reverseString. After it appends the new line '\n'.
*/
char* RLEListExportToString(RLEList list, RLEListResult* result){
    if(list == NULL){
        if (result != NULL){
        *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int RLEListLen = 0;
    RLEList head = list;
    while(head && head -> count != 0){ //count number of nodes.
        RLEListLen++;
        head = head -> next;
    }
    int size = 2*RLEListLen + countDigits(list);    // The overall size of the string.
    char *returnedStr = malloc(size + 1);
    if(returnedStr == NULL){
        if (result != NULL){
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    int i = 0;
    while(i < size){
        returnedStr[i++] = list->val;           // adding the letter.
        int start = i, num = list -> count;
        while(num > 0){                         // adding the digits in reverse order.
            returnedStr[i++] = num % 10 + '0';
            num /= 10;
        }
        reverseString(returnedStr + start, i - start);  // correct the order.
        returnedStr[i++] = '\n';
        list=list->next;
    }
    returnedStr[size]='\0';     // ending the string.
    
    if (result != NULL){
        *result=RLE_LIST_SUCCESS;   
    }
    return returnedStr;
}

