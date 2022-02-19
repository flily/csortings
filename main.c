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

struct benchmark_info_s {
    char* name;
    sort_func sort;
};

static
struct benchmark_info_s sort_algos[] = {
    { "selection", sort_selection },
    { "insertion", sort_insertion },
    { "bubble", sort_bubble },
    { "qsort", sort_qsort },
    { "quick", sort_quick },
    { NULL, NULL },
};

sort_func find_algo(const char* name)
{
    int i = 0;
    for (i = 0; sort_algos[i].name != NULL; i++) {
        if (strcmp(sort_algos[i].name, name) == 0) {
            return sort_algos[i].sort;
        }
    }

    return NULL;
}


void do_random(int size, int range)
{
    data_t** list = NULL;
    int sorted = 0;
    
    srand(time(NULL));
    list = data_list_random(size, range);
    if (NULL == list) {
        fprintf(stderr, "generate random list failed\n");
        return;
    }

    print_data_list(list, size);
    sorted = data_list_sorted(list, size);
    printf("sorted: %d\n", sorted);
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

void do_sort(const char* algo)
{
    data_t** list = NULL;
    int size = 1;
    int sorted = 0;

    sort_func sort = find_algo(algo);
    if (NULL == sort) {
        fprintf(stderr, "unknown sort algorithm: %s\n", algo);
        return;
    }

    list = data_list_read(stdin, &size);
    if (NULL == list) {
        fprintf(stderr, "read data list failed\n");
        return;
    }

    sort(list, size);
    print_data_list(list, size);
    sorted = data_list_sorted(list, size);
    printf("sorted: %d\n", sorted);
    data_list_free(list, size);
}

int do_test(const char* algo, int size, int range, int output)
{
    data_t** list = NULL;
    int sorted = 0;

    list = data_list_random(size, range);
    if (NULL == list) {
        fprintf(stderr, "generate random list failed\n");
        return 0;
    }

    sort_func sort = find_algo(algo);
    if (NULL == sort) {
        fprintf(stderr, "unknown sort algorithm: %s\n", algo);
        return 0;
    }

    if (output > 0) {
        print_data_list(list, size);
        printf("---------------- sorting by %s ----------------\n", algo);
    }

    sort(list, size);

    if (output > 0) {
        print_data_list(list, size);
    }

    sorted = data_list_sorted(list, size);
    data_list_free(list, size);
    return sorted;
}

void do_benchmark(int size, int range)
{
    int i = 0;
    data_t** list = NULL;
    
    list = data_list_random(size, range);
    if (NULL == list) {
        fprintf(stderr, "generate random list failed\n");
        return;
    }

    printf("size: %d, range: %d\n", size, range);
    printf("---------------- benchmark ----------------\n");
    for (i = 0; sort_algos[i].name != NULL; i++) {
        struct benchmark_info_s* info = &sort_algos[i];
        data_t** data = NULL;
        clock_t clock_start, clock_end;

        data = data_list_duplicate(list, size);
        if (NULL == data) {
            fprintf(stderr, "duplicate data list failed\n");
            return;
        }

        clock_start = clock();
        info->sort(data, size);
        clock_end = clock();

        data_list_free(data, size);
        printf("%-20s  \t\t    %ld\n",
            info->name,
            clock_end - clock_start);
    }
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
        int batch = 1;

        if (argc <= 2) {
            printf("missing algorithm name\n");
            usage(argv[0]);
            return 0;
        }

        algo = argv[2];
        if (argc > 3) {
            size = atoi(argv[3]);
            if (argc > 4) {
                range = atoi(argv[4]);
                if (argc > 5) {
                    batch = atoi(argv[5]);
                }
            }
        }
        printf("algo: %s, size: %d, range: %d\n", algo, size, range);
        if (batch == 1) {
            int sorted = do_test(algo, size, range, 1);
            printf("sorted: %d\n", sorted);

        } else {
            int i = 0;
            for (i = 0; i < batch; i++) {
                int sorted = do_test(algo, size, range, 0);
                printf("test list %d sorted: %d\n", i, sorted);
                if (sorted == 0) {
                    printf("test failed\n");
                    return 0;
                }
            }
        }

    } else if (!strcmp(cmd, "sort")){
        char* algo = NULL;
        if (argc <= 2) {
            printf("missing algorithm name\n");
            usage(argv[0]);
            return 0;
        }

        algo = argv[2];
        do_sort(algo);

    } else if (!strcmp(cmd, "benchmark")) {
        int size = 10000;
        int range = 100000;

        if (argc > 2) {
            size = atoi(argv[2]);
            if (argc > 3) {
                range = atoi(argv[3]);
            }
        }
        do_benchmark(size, range);

    } else {
        usage(argv[0]);
    }

    return 0;
}