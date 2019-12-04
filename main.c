#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "readprinttext.h"
#include "changevowel.h"
#include "findtobe.h"
#include "deletefour.h"
#include "sortlast.h"

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