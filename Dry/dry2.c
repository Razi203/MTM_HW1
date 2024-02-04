#include <stdio.h>
#include <stdbool.h>

typedef struct node_t {
    int val;
    struct node_t *next;
} *Node;

bool isListSorted(Node list);

Node mergeSortedLists(Node list1, Node list2);

Node mergeSortedLists(Node list1, Node list2){
    if(list1 == NULL || list2 == NULL){
        return NULL;
    }
    if(!isListSorted(list1) || !isListSorted(list2)){
        return NULL;
    }
    Node merged_list;
    if (list1 -> val < list2 -> val){
        merged_list = list1;
        list1 = list1 -> next;
    }else{
        merged_list = list2;
        list2 = list2 -> next;
    }
    Node head = merged_list;

    while (list1 != NULL && list2 != NULL){
        if (list1 -> val < list2 -> val){
            head -> next = list1;
            list1 = list1 -> next;
        } else {
            head -> next = list2;
            list2 = list2 -> next;
        }
        head = head -> next;
    }

    if (list1 != NULL){
        head -> next = list1;
    }

    if (list2 != NULL){
        head -> next = list2;
    }
    
    return merged_list;
}






Node createNode(int d) {
    Node ptr = malloc(sizeof(*ptr));
    if(!ptr) {
        return NULL;
    }
    ptr->val = d;
    ptr->next = NULL;
    return ptr;
}

Node insert(Node head, int d) {
    Node newHead = createNode(d);
    if(!newHead) {
    return NULL;
    }
    newHead->next = head;
    return newHead;
}

void destroyList(Node head) {
    while(head) {
        Node toDelete = head;
        head = head->next;
        free(toDelete);
    }
}


bool isListSorted(Node list){
    return true;
}

int main(){
    Node head1 = NULL;
    Node head2 = NULL;
    int input;
    int counter = 0;
    while (counter++ < 4 && scanf(" %d",&input)) {
        head1 = insert(head1,input);
        //printf("now: %d    ", input);   
    }
    
    //printf("\n");
    
    counter = 0;
    while (counter++ < 4 && scanf(" %d",&input)) {
        //printf("now: %d    ", input);
       head2 = insert(head2,input);
    }
    Node head = mergeSortedLists(head1, head2);
    //Node head = head2;
    for(Node ptr = head ; ptr != NULL ; ptr=ptr->next) {
        printf("-- %d --",ptr->val);
    }
    destroyList(head);
    return 0;

}
