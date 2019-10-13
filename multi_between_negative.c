#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative_function.h"

int multi_between_negative_function(int *array, int *number){
    int multi_between_negative=1;
    for(int i=index_first_negative_function(array, number); i<index_last_negative_function(array, number); i++){
        multi_between_negative=multi_between_negative*array[i];
    }
    return multi_between_negative;
}