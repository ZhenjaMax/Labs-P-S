#include "changevowel.h"

int isVowel(char ch){
	const char vowels[] = "aeiouyAEIOUY";
	if (strchr(vowels, ch)==NULL)
		return 0;
	return 1;
}

void changeVowel(char **text, int sentence_count){
	for(int i=0; i<sentence_count; i++)
		for(int j=0; j<strlen(text[i]); j++)
			if(isVowel(text[i][j]))
				text[i][j]++;
	return;
}