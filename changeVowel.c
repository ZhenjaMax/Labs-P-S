#include <stdio.h>
#include <stdlib.h>

int isVowel(char ch){
	char vowels[7] = "aeiouy"};
	if (strstr(ch, vowels)==NULL)
	    return 0;
	return 1;
}

void changeVowel(char **text, int* sentence_count){
	for int i=0; i<sentence_count; i++)
		for(int j=0; j<strlen(text[i]); i++)
			if(isVowel(text[i][j])
				text[i][j]++;
	return;
}
