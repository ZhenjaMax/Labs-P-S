#include <stdio.h>
#include "index_last_negative.h"

int index_last_negative_function(int *array, int *number){
    int index_last_negative=-1;
    for (int i=0; i<*number; i++){
        if (array[i]<0){
            index_last_negative=i;
        }
    }
    return index_last_negative;
}