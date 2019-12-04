#include "sortlast.h"

void backwardText(char **text, int sentence_count){
	int j, k;
	char temp;
	for(int i=0; i<sentence_count; i++){
		j=0;
		k=strlen(text[i])-2;
		while(j<k){
			temp=text[i][j];
			text[i][j]=text[i][k];
			text[i][k]=temp;
			j++;
			k--;
		}
	}
	return;
}

int mystrcmp(const void* first, const void* second){
	int i1=0;
	int i2=0;
	char** temp1=(char**)first;
	char** temp2=(char**)second;
	char *ptr1 = *temp1;
	char *ptr2 = *temp2;
	while(1){
		if((ptr1[i1]=='.')&&(ptr2[i2]=='.'))
			return 0;
		if(ptr1[i1]=='.')
			return ptr2[i2];
		if((ptr2)[i2]=='.')
			return ptr1[i1];
		if(!isalnum(ptr1[i1]))
			i1++;
		if(!isalnum(ptr2[i2]))
			i2++;
		if(ptr1[i1]==ptr2[i2]){
			i1++;
			i2++;
		} else return ptr1[i1]-ptr2[i2];
	}
}

void sortLast(char **text, int sentence_count){
	backwardText(text, sentence_count);
	qsort(text, sentence_count, sizeof(char*), mystrcmp);
	backwardText(text, sentence_count);
	return;
}