#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "data.h"
#include "sort.h"

int usage(const char* program)
{
    printf("Usage: %s CMD  [args ...]\n", program);
    return 1;
}

void do_random(int size, int range)
{
    int i = 0;
    data_t** list = NULL;
    
    srand(time(NULL));
    list = data_list_random(size, range);
    if (NULL == list) {
        fprintf(stderr, "generate random list failed\n");
        return;
    }

    for (i = 0; i < size; i++) {
        data_t* data = list[i];
        if (NULL == data) {
            fprintf(stderr, "unexpected null data node.\n");
            return;
        }

        printf("%5d %d\n", i, data->value);
    }

    data_list_free(list, size);
}

void do_import()
{
    data_t** list = NULL;
    int size = 100;
    int i = 0;

    list = data_list_read(stdin, &size);
    if (NULL == list) {
        fprintf(stderr, "read data list failed\n");
        return;
    }

    for (i = 0; i < size; i++) {
        data_t* data = list[i];
        if (NULL == data) {
            fprintf(stderr, "unexpected null data node.\n");
            return;
        }

        printf("%5d %d\n", i, data->value);
    }

    data_list_free(list, size);
}

int main(int argc, char* argv[])
{
    char* cmd = NULL;
    if (argc <= 1) {
        usage(argv[0]);
        return 0;
    }

    cmd = argv[1];
    if (!strcmp(cmd, "random")) {
        int size = 20;
        int range = 1000;

        if (argc > 2) {
            size = atoi(argv[2]);
            if (argc > 3) {
                range = atoi(argv[3]);
            }
        }

        do_random(size, range);

    } else if (!strcmp(cmd, "import")) {
        do_import();

    } else {
        usage(argv[0]);
    }

    return 0;
}