#include "data.h"

#include <string.h>



data_t* data_create(int value)
{
    data_t* data = malloc(sizeof(data_t));
    if (NULL == data) {
        return NULL;
    }

    data->value = value;
    return data;
}

void data_free(data_t* data)
{
    if (NULL == data) {
        return;
    }

    free(data);
}

data_t* data_parse(const char* str)
{
    if (NULL == str) {
        return NULL;
    }

    int value = atoi(str);
    return data_create(value);
}

data_t** data_list_random(int size, int range)
{
    int i = 0;
    data_t** list = NULL;
    size_t list_size = sizeof(data_t*) * size;

    if (size <= 0) {
        return NULL;
    }

    list = malloc(list_size);
    if (NULL == list) {
        return NULL;
    }

    memset(list, 0, list_size);

    do {
        int success = 0;
        for (i = 0; i < size; ++i) {
            data_t* data = data_create(rand() % range);
            if (NULL == data) {
                success = 1;
                break;
            }
            list[i] = data;
        }

        if (success > 0) {
            break;
        }

        return list;

    } while (0);

    for (i = 0; i < size; ++i) {
        data_free(list[i]);
        list[i] = NULL;
    }

    return NULL;
}

data_t** data_list_duplicate(data_t** list, int size)
{
    int i = 0;
    data_t** new_list = NULL;
    size_t new_list_size = sizeof(data_t*) * size;

    if (NULL == list || size <= 0) {
        return NULL;
    }

    new_list = malloc(new_list_size);
    if (NULL == new_list) {
        return NULL;
    }

    memset(new_list, 0, new_list_size);
    for (i = 0; i < size; ++i) {
        new_list[i] = data_create(list[i]->value);
        if (NULL == new_list[i]) {
            break;
        }
    }

    if (i < size) {
        data_list_free(new_list, size);
        new_list = NULL;
    }

    return new_list;
}

void data_list_free(data_t** list, int size)
{
    int i = 0;
    if (NULL == list) {
        return;
    }

    for (i = 0; i < size; ++i) {
        if (NULL != list[i]) {
            data_free(list[i]);
        }
    }

    free(list);
}

data_t** data_list_read(FILE* fd, int* size)
{
    data_t** list = NULL;
    int length = 0;

    if (NULL == fd || NULL == size || size < 0) {
        return NULL;
    }

    list = malloc(sizeof(data_t*) * (*size));
    if (NULL == list) {
        return NULL;
    }
    memset(list, 0, sizeof(data_t*) * (*size));

    do {
        int n = 0;
        int failure = 0;

        while (0 < fscanf(fd, "%d", &n)) {
            data_t* data = data_create(n);
            if (NULL == data) {
                break;
            }

            if (length >= *size) {
                int j = 0;
                *size *= 2;
                list = realloc(list, sizeof(data_t*) * (*size));
                for (j = length; j < *size; ++j) {
                    list[j] = NULL;
                }
            }

            list[length] = data;
            length += 1;
        }

        if (failure) {
            break;
        }

        *size = length;
        return list;
    } while (0);

    data_list_free(list, length);
    return NULL;
}
