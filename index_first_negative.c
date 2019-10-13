#include <stdio.h>
#include "index_first_negative.h"

int index_first_negative_function(int *array, int *number){
    for (int i=0; i<*number; i++){
        if (array[i]<0){
            return i;
        }
    }
}