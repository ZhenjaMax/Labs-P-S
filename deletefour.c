#include "deletefour.h"

int isFourWord(char *sentence){
	for(int i=0; i<4; i++)
		if(!isalnum(sentence[i]))
			return 0;
	if(!isalnum(sentence[4]))
		return 1;
	return 0;
}

void deleteFour(char **text, int *sentence_count){
	for(int i=0; i<*sentence_count; i++)
		if(isFourWord(text[i])){
			free(text[i]);
			(*sentence_count)--;
			for(int j=i; j<*sentence_count; j++)
				text[j]=text[j+1];
			i--;
		}
	return;
}