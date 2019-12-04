#include "readprinttext.h"

char** readText(int *sentence_count){
	char **text = (char**)calloc(1, sizeof(char*));
    if (text == NULL)
        return NULL;
    int i=0;
	int sentence_max=0;
    char c = getchar();
    do{
        i=0;
        if((text=(char**)realloc(text, ((*sentence_count)+1)*sizeof(char**)))==NULL)
            return NULL;
        do{
			if ((text[*sentence_count]=(char*)realloc(text[*sentence_count], sizeof(char*)*(i+3)))==NULL)
    			return NULL;
            text[*sentence_count][i]=c;
            i++;
        }while((c=getchar())!='.');
        text[*sentence_count][i]='.';
        text[*sentence_count][i+1]='\0';
        (*sentence_count)++;
		if (i+2>sentence_max)
			sentence_max=i+2;
    }while((c = getchar())!='\n');
	
    //	Deleting same sentences	\\
	
    char checker[*sentence_count][sentence_max];
    int j;
	for(i=0; i<*sentence_count; i++){
		strcpy(checker[i], text[i]);
		for(j=0; checker[i][j]; j++)
		    checker[i][j]=tolower(checker[i][j]);
	}
    for(i=0;i<*sentence_count;i++)
		for(j=i+1; j<*sentence_count; j++)
			if(!strcmp(checker[i], checker[j])){
				(*sentence_count)--;
				for(int k=j; k<*sentence_count; k++){
					text[k]=text[k+1];
					strcpy(checker[k], checker[k+1]);
				}
				j--;
			}
    return text;
}

void printText(char **text, int sentence_count){
	for(int i=0; i<sentence_count; i++){
		printf("%s\n", text[i]);
		free(text[i]);
	}
	free(text);
	return;
}