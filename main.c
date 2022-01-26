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

void print_data_list(data_t** data, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        data_t* item = data[i];
        if (NULL == item) {
            fprintf(stderr, "unexpected null data node at %d.\n", i);
            return;
        }

        printf("%5d %d\n", i, item->value);
    }
}

void do_random(int size, int range)
{
    data_t** list = NULL;
    
    srand(time(NULL));
    list = data_list_random(size, range);
    if (NULL == list) {
        fprintf(stderr, "generate random list failed\n");
        return;
    }

    print_data_list(list, size);
    data_list_free(list, size);
}

void do_import()
{
    data_t** list = NULL;
    int size = 100;

    list = data_list_read(stdin, &size);
    if (NULL == list) {
        fprintf(stderr, "read data list failed\n");
        return;
    }

    print_data_list(list, size);
    data_list_free(list, size);
}

void do_test(const char* algo, int size, int range)
{
    data_t** list = NULL;

    list = data_list_random(size, range);
    if (NULL == list) {
        fprintf(stderr, "generate random list failed\n");
        return;
    }

    sort_func sort = NULL;
    if (!strcmp("selection", algo)) {
        sort = sort_selection;
    
    } else if (!strcmp("insertion", algo)) {
        sort = sort_insertion;

    } else {
        fprintf(stderr, "unknown sort algorithm: %s\n", algo);
        return;
    }

    print_data_list(list, size);
    printf("---------------- sorting by %s ----------------\n", algo);
    sort(list, size);

    print_data_list(list, size);
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

    } else if (!strcmp(cmd, "test")) {
        char* algo = NULL;
        int size = 100;
        int range = 1000;

        if (argc <= 2) {
            printf("missing algorithm name\n");
            usage(argv[0]);
            return 0;
        }

        algo = argv[2];
        if (argc > 3) {
            size = atoi(argv[3]);
            if (argc > 3) {
                range = atoi(argv[4]);
            }
        }
        printf("algo: %s, size: %d, range: %d\n", algo, size, range);
        do_test(algo, size, range);

    } else {
        usage(argv[0]);
    }

    return 0;
}