#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define SENT_UNIT 64

char* readText(){
    
    char textFrag[SENT_UNIT];
    char* tempp;
    char* rawText = (char*)malloc(sizeof(char)*SENT_UNIT);
    
    while (1){
        tempp = fgets(textFrag, SENT_UNIT, stdin);
        if (tempp == NULL)
            return rawText;;
        rawText = (char*)realloc(rawText, sizeof(char)*SENT_UNIT+strlen(rawText));
        strcpy(rawText+strlen(rawText)*sizeof(char), tempp);
    }
}

int main(){
	
    const char* regexString = "(\\w+:\\/\\/)?(www\\.)?((\\w+\\.)+\\w+)\\/(\\w+\\/)*(.+\\.\\w+)";
	const int siteName = 3;
	const int fileName = 6;
	const int maxGroups = 7;
    int sentcount = 0;
    char** text = (char**)malloc(sizeof(char*));
	
    regex_t regexStringCompiled;
    regmatch_t groupArray[maxGroups];

	char* rawText = readText();
    char* tempp = strtok (rawText, "\n");
	
    while (tempp != NULL){
        text[sentcount] = tempp;
        sentcount++;
        text = (char**)realloc(text, (sentcount+1)*sizeof(char*));
        tempp = strtok(NULL, "\n");
    }
	
    regcomp(&regexStringCompiled, regexString, REG_EXTENDED);
    for(int i=0; i<sentcount; i++){
        if (regexec(&regexStringCompiled, text[i], maxGroups, groupArray, 0) == 0){
            for(int j=groupArray[siteName].rm_so; j<groupArray[siteName].rm_eo; j++)
                printf("%c", text[i][j]);
            printf(" - ");
            for(int j=groupArray[fileName].rm_so; j<groupArray[fileName].rm_eo; j++)
                printf("%c", text[i][j]);
        }
	    printf("\n");
    }
    
    regfree(&regexStringCompiled);
    free(rawText);
    free(text);
    
    return 0;
}