#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int qsortcmp(const void *ptr1, const void *ptr2){
    return strcmp(*(char**)ptr1, *(char**)ptr2);
}

int bsearchcmp(const void* ptr1, const void* ptr2){
    return strcmp((char*)ptr1, *(char**)ptr2);
}

int main(){
    char text[1001], str[31];
    char delim[] = " .";
    fgets(text, 1000, stdin);
    fgets(str, 30, stdin);
    
    char **word = (char**)malloc(sizeof(char*));
    char* p = strtok(text, delim);
    int counter;

    for(counter=0; p; counter++){
        word[counter]=p;
        p = strtok(NULL, delim);
        word = realloc(word, (counter+2)*sizeof(char*));
    }
    counter--;
    
    qsort(word, counter, sizeof(char*), qsortcmp);
    if(bsearch(str, word, counter, sizeof(char*), bsearchcmp)==NULL)
        printf("doesn't exist");
    else printf("exists");
    
    return 0;
}