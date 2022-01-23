#ifndef ___SORTINGS__DATA_H___
#define ___SORTINGS__DATA_H___

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#define DATALIST_DEFAULT_SIZE   1000

typedef struct data_s data_t;
struct data_s
{
    int value;
};

data_t* data_create(int value);

void data_free(data_t* node);

data_t* data_parse(const char* s);

data_t** data_list_random(int size, int range);

void data_list_free(data_t** list, int size);

data_t** data_list_read(FILE* fd, int* size);

#ifdef __cplusplus
}
#endif

#endif