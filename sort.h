#ifndef ___SORTINGS__SORT_H___
#define ___SORTINGS__SORT_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "data.h"

typedef int (*sort_func)(data_t** data, int size);

int sort_selection(data_t** data, int size);

int sort_insertion(data_t** data, int size);

int sort_bubble(data_t** data, int size);

int sort_qsort(data_t** data, int size);

int sort_quick(data_t** data, int size);

int sort_merge(data_t** data, int size);

int sort_heap(data_t** data, int size);

int sort_shell(data_t** data, int size);

#ifdef __cplusplus
}
#endif

#endif