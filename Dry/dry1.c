#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
 
char* stringDuplicator(char* str, int times){ 
    assert(str); 
    assert(times > 0); 
    int len = strlen(str); 
    char* out = malloc(len*times+1); 
    if (!out){
        free(out);
        return NULL;
    } 
    for (int i=0; i< times; i++){ 
        strcpy(out,str); 
        out = out + len; 
    } 
    *out = '\0';
    out -= times*len;
    return out; 
} 

int main(){
    char string[5] = "hello";
    char *n;
    char* new = stringDuplicator(n, 5);
    printf("%s", new);
}
