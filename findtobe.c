#include "findtobe.h"

int isToBe(char* sentence){
	char mask[]="To * or not to *.";
	int length[2] = {0};
	int word=0;
	int j=0;
	for(int i=0; i<strlen(mask); i++){
		if(mask[i]=='*'){
			while(isalnum(sentence[j])){
				j++;
				length[word]++;
			}
			i++;
			word++;
		}
		if(sentence[j]!=mask[i])
			return 0;
		j++;
	}
	if(length[0]>length[1])
		return -length[0];
	else return length[1];
}

void findToBe(char **text, int *sentence_count){
	int length=0;
	char *ptr1 = (char*)calloc(1, sizeof(char));
	char *ptr2 = (char*)calloc(1, sizeof(char));
	for(int i=0; i<*sentence_count; i++){
		length = isToBe(text[i]);
		if(length<0){
			length = -length;
			ptr1 = (char*)realloc(ptr1, length+1);
			for(int j=0; j<length; j++)
				ptr1[j]=text[i][3+j];
			ptr1[length]='\0';
			text[i]=realloc(text[i], length+1);
			strcpy(text[i], ptr1);
			continue;
		}
		if(length>0){
			ptr2=(char*)realloc(ptr2, length+1);
			for(int j=0; j<length; j++)
				ptr2[length-1-j]=text[i][strlen(text[i])-2-j];
			ptr2[length]='\0';
			text[i]=realloc(text[i], length+1);
			strcpy(text[i], ptr2);
			continue;
			}
		if(length==0){
			free(text[i]);
			(*sentence_count)--;
			for(int j=i; j<*sentence_count; j++)
				text[j]=text[j+1];
			i--;
			continue;
		}
	}
	free(ptr1);
	free(ptr2);
	return;
}