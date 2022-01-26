#include "sort.h"

int sort_insertion(data_t** data, int size)
{
    int i = 0;
    if (NULL == data || size <= 0) {
        return -1;
    }

    for (i = 1; i < size; i++) {
        int j = i;
        for (j = i; j > 0; j--) {
            if (data[j]->value < data[j - 1]->value) {
                data_t* t = data[j];
                data[j] = data[j - 1];
                data[j - 1] = t;
            }
        }
    }

    return 0;
}