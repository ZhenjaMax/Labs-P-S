#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char** readText(int *sentence_count){
	char **text = (char**)calloc(1, sizeof(char*));
    if (text == NULL)
        return NULL;
    int i=0;
    char **buffer_text;
	char *buffer_sentence;
	int sentence_max=0;
    char c = getchar();
	
    do{
        i=0;
        if((buffer_text=(char**)realloc(text, (*sentence_count+1)*sizeof(char**)))==NULL)
            return NULL;
        text=buffer_text;
        do{
			if((buffer_sentence=(char*)realloc(text[*sentence_count], sizeof(char*)*(i+3)))==NULL)
    			return NULL;
    		text[*sentence_count]=buffer_sentence;
            text[*sentence_count][i]=c;
            i++;
        }while((c=getchar())!='.');
        text[*sentence_count][i]='.';
        text[*sentence_count][i+1]='\0';
        (*sentence_count)++;
		if(i+2>sentence_max)
			sentence_max=i+2;
    }while((c = getchar())!=EOF);
    
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
				free(text[j]); 								/////////////////
				(*sentence_count)--;
				for(int k=j; k<*sentence_count; k++){
					text[k]=text[k+1];
					strcpy(checker[k], checker[k+1]);
				}
				j--;
			}
	text = (char**)realloc(text, *sentence_count);
	return text;
}

void printText(char **text, int sentence_count){
    for(int i=0; i<sentence_count; i++)
        printf("%s", text[i]);
    return;
}

int isVowel(char ch){
    char vowels[7] = "aeiouy";
    if (strstr(ch, vowels)==NULL)
        return 0;
    return 1;
}

void changeVowel(char **text, int sentence_count){
    for(int i=0; i<sentence_count; i++)
        for(int j=0; j<strlen(text[i]); i++)
            if(isVowel(text[i][j]))
                text[i][j]++;
    return;
}

int isToBe(char* sentence){
	mask[18]="To * or not to *.";
	int length[2] = {0};
	int wordCount=0;
	int j=0;
	for(int i=0; i<17; i++){
		if(mask[j]='*'){
			while(sentence[i]!=' '){
				i++;
				length[wordCount]++;
			}
			j++;
			wordCount++;
			
		}
		if(sentence[i]!=mask[j])
			return 0;
		j++;
	}
	if(length[0]>length[1])
		return -length[0];
	else return length[1];
}

void findToBe(char **text, *sentence_count){
	int length;
	char *wordFirst = (char*)calloc(1, sizeof(char));
	char *wordSecond = (char*)calloc(1, sizeof(char));
	int j = 0
	for(int i=0; i<*sentence_count; i++){
		length = isToBe(text[i]);
		if(length!=0){
			if(length<0){
				length = -length;
				wordFirst = (char*)realloc(wordFirst, length+1);
				for(j=0; j<length; j++)
					wordFirst[j]=text[i][3+j];
				wordFirst[length]='\0';
			}else{
				
			}
		}else text[i] = NULL;	
	}
}

int isFourWord(char *sentence){
	for(int i=0; i<4; i++)
		if(!alnum(sentence[i]))
			return 0;
	if(!alnum(sentence[i]))
		return 1;
	return 0;
}

void deleteFour(char **text, int *sentence_count){
	for(int i=0; i<*sentence_count; i++)
		if(strlen(text[i])>6)
			if(isFourWord(text[i])){
				free(text[i]);								////////////////
				(*sentence_count)--;
				for(int j=i; j<*sentence_count; j++)
					text[j]=text[j+1];
				i--;
			}
	return;
}

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
}

int mystrcmp(char* first, char* second){
	int i1=0;
	int i2=0;
	while(1){
		if((first[i1]=='.')&&(first[i2]=='.'))
			return 0;
		if(first[i1]=='.')
			return second[i2];
		if(first[i2]=='.')
			return first[i1];
		while((first[i1]==' ')||(first[i1]==','))
			i1++;
		while((second[i2]==' ')||(second[i2]==','))
			i2++;
		if(first[i1]==second[i2]){
			i1++;
			i2++;
		} else return first[i1]-second[i2];
	}
}

void sortLast(char **text; int sentence_count){
	backwardText(text, sentence_count);
	qsort(text, sentence_count, sizeof(char*), mystrcmp);
	backwardText(text, sentence_count);
	return;
}

int main(){
	int command;
	int sentence_count = 0;
	char **text = readText(&sentence_count);
	if(text==NULL){
		printf("Ошибка выделения памяти.");
		return 1;
	}
	printf("Введите одно из чисел ниже, чтобы выбрать действие:\n\n1) Заменить в тексте все гласные буквы на следующую букву в алфавите.\n2) Найти все предложения вида “To <подстрока1> or not to <подстрока2>” и для каждого такого предложения вывести подстроку у которой длина больше.\n3) Удалить все предложения у которых длина первого слова равняется 4.\n4) Отсортировать предложения по увеличению кода последнего символа не являющегося разделителем предложений или слов.\n0) Выйти из программы.\n");
	scanf("%d", &command);
	switch(command){
		case 1:
			changeVowel(text, sentence_count);
			printText(text, sentence_count);
			break;
		case 2:
			findToBe(text, *sentence_count);
			printText(text, sentence_count);
			break;
		case 3:
			deleteFour(text, &sentence_count);
			printText(text, sentence_count);
			break;
		case 4:
			sortLast(text, sentence_count);
			printText(text, sentence_count);
			break;
		case 0:
			break;
		default:
			printf("Неправильный ввод!");
			break;
	}
	return 0;
}
