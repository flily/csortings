#include "sort.h"

#include <stdlib.h>

static
int data_compare(const void* a, const void* b)
{
    data_t* data_a = *(data_t**)a;
    data_t* data_b = *(data_t**)b;

    if (data_a->value < data_b->value) {
        return -1;

    } else if (data_a->value > data_b->value) {
        return 1;

    } else {
        return 0;
    }
}

int sort_qsort(data_t** data, int size)
{
    if (NULL == data || size <= 0) {
        return -1;
    }

    qsort(data, size, sizeof(data_t*), data_compare);
    return 0;
}

static
int quick_partition(data_t** data, int lo, int hi)
{
    int i = lo + 1, j = hi;
    data_t* v = data[lo];

    while (1) {
        for (; i < hi && data[i]->value <= v->value; i++);
        for (; j > lo && data[j]->value >= v->value; j--);
        if (i >= j) {
            break;
        }

        data_list_swap(data, i, j);
    }

    data_list_swap(data, lo, j);
    return j;
}

static
int quick_sort(data_t** data, int lo, int hi)
{
    int j = 0;

    if (lo >= hi) {
        return 0;
    }

    j = quick_partition(data, lo, hi);
    quick_sort(data, lo, j - 1);
    quick_sort(data, j + 1, hi);

    return 0;
}

int sort_quick(data_t** data, int size)
{
    if (NULL == data || size <= 0) {
        return -1;
    }

    quick_sort(data, 0, size - 1);
    return 0;
}
