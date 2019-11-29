#include <stdio.h>
#include <stdlib.h>

void printText(char **text, int* sentence_count){
	for(int i=0; i<sentence_count; i++)
	    printf("%s", text[i]);
	return;
}
