#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int isToBe(char* sentence){
	char* ptr1 = strstr(sentence, "To ");
	char* ptr2 = strstr(sentence, " or not to ");
	int len1, len2;
	if(ptr1==sentence && ptr2!=NULL){
		len1 = ptr2-ptr1-3;
		len2 = sentence+strlen(sentence)-(ptr2+12);
		if(len1>len2)
			return -len1;
		else return len2;
	}
	else return 0;
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

int main(){
    int sentence_count=0;
    int command;
    char** text = readText(&sentence_count);
    if(text==NULL){
		printf("Ошибка выделения памяти.\n");
		return 1;
	}
	printf("Введите одно из чисел ниже, чтобы выбрать действие:\n\n1) Заменить в тексте все гласные буквы на следующую букву в алфавите.\n2) Найти все предложения вида “To <подстрока1> or not to <подстрока2>” и для каждого такого предложения вывести подстроку у которой длина больше.\n3) Удалить все предложения у которых длина первого слова равняется 4.\n4) Отсортировать предложения по увеличению кода последнего символа не являющегося разделителем предложений или слов.\n0) Выйти из программы.\n");
	scanf("%d", &command);
	printf("\n");
	switch(command){
	    case 1:
			changeVowel(text, sentence_count);
			printText(text, sentence_count);
			break;
		case 2:
		    findToBe(text, &sentence_count);
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
			printf("Неправильный ввод!\n");
			break;
	}
	return 0;
}
