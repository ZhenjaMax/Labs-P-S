#include<stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_before_and_after_negative.h"

int multi_before_and_after_negative_function(int *array, int *number){
    int multi_before_and_after_negative=1;
    for(int i=0; i<index_first_negative_function(array, number); i++){
        multi_before_and_after_negative=multi_before_and_after_negative*array[i];
    }
    for(int i=index_last_negative_function(array, number); i<*number; i++){
        multi_before_and_after_negative=multi_before_and_after_negative*array[i];
    }
    return multi_before_and_after_negative;
}