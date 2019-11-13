#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int is_sign(char ch){
    if((ch != ',')&&(ispunct(ch))){
        if(ch == '!')
            return 2;
        return 1;
    }
    return 0;
}

int sentence_print(int* before, int* after){
    int len = 1;
    char* sentence = (char*)malloc(sizeof(char));
    int num_prestart, num_postend;
    (*before)++;
    
    do {*sentence = getchar();
    } while(isblank(*sentence));
    while(is_sign(*(sentence+(len-1)))==0){
        sentence = (char *)realloc(sentence, len+2);
        *(sentence+len)=getchar();
        len++;
    }
    *(sentence+len)='\0';
    for(int j=1; j<len; j++){
        if(isdigit(*(sentence+j))){
            num_prestart=j;
            num_postend=j;
            while(isdigit(*(sentence+num_prestart))&&(num_prestart>0))
                num_prestart--;
            while(isdigit(*(sentence+num_postend)))
                num_postend++;
            if((isdigit(*(sentence+j))) && (isalpha(*(sentence+num_prestart))) && (isalpha(*(sentence+num_postend)))){
                free(sentence);
                return 1;
            }
        }
    }
    printf("%s\n", sentence);
    (*after)++;
    if(is_sign(*(sentence+len-1))==2){
        free(sentence);
        return 0;
    }
    return 1;
}

int main(){
    int before = 0;
    int after = 0;
    while(sentence_print(&before, &after));
    printf("Количество предложений до %d и количество предложений после %d", before-1, after-1);
    return 0;
}