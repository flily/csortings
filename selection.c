#include "sort.h"

int sort_selection(data_t** data, int size)
{
    int i = 0;
    if (NULL == data || size <= 0) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        int min = i;
        int j = i + 1;
        data_t* t = NULL;
        for (j = i + 1; j < size; j++) {
            if (data[j]->value < data[min]->value) {
                min = j;
            }
        } 
        
        t = data[i];
        data[i] = data[min];
        data[min] = t;
    }

    return 0;
}