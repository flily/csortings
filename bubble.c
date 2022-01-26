#include "sort.h"

int sort_bubble(data_t** data, int size)
{
    int swap = 1;
    if (NULL == data || size <= 0) {
        return -1;
    }

    while (swap > 0) {
        int i = 0;
        swap = 0;
        for (i = 0; i < size - 1; i++) {
            if (data[i]->value > data[i + 1]->value) {
                data_t* t = data[i];
                data[i] = data[i + 1];
                data[i + 1] = t;
                swap += 1;
            }
        }
    }

    return 0;
}