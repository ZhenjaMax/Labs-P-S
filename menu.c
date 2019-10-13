#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

int array_create(int *array){
    char symbol;
    for(int i=0; i<20; i++){
        scanf("%i%c", &array[i], &symbol);
        if(symbol == '\n'){
            i++;
            return i;
        }
    }
}

int main(){
    int function;
    scanf("%i", &function);
    int array[20];
    int number=array_create(array);
    switch (function){
        case 0:
            printf("%i\n", index_first_negative_function(array, &number));
            break;
        case 1:
            printf("%i\n", index_last_negative_function(array, &number));
            break;
        case 2:
            printf("%i\n", multi_between_negative_function(array, &number));
            break;
        case 3:
            printf("%i\n", multi_before_and_after_negative_function(array, &number));
            break;
        default:
            printf("Данные некорректны\n");
    }
}