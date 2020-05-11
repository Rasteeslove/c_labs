#include "clab7.h"

int length_of(char * str);

void report_merror();
void report_uerror();
void report_werror();

int substr(char * sub, char * str);
int are_strs_same(char * first, char * second);
int is_among(int * items, int num_of_items, int item);
void out_str_wo_nl(char * str);

void report_merror()
{
    printf("\nMemory error\n");
    exit(EXIT_FAILURE);
}

void report_uerror()
{
    printf("\nSomething went wrong during the reading of file\n");
    exit(EXIT_FAILURE);
}

void report_werror()
{
    printf("\nSomething went wrong during the writing to file\n");
    exit(EXIT_FAILURE);
}

int length_of(char * str)
{
    if (str == NULL)
    {
        return 0;
    }

    int i = 0;
    for (; str[i]; i++) {}

    return i + 1;
}

int substr(char * sub, char * str)
{
    if (str == NULL)
        return -1;

    if (sub == NULL || length_of(sub) == 1)
        return 0;

    int i = 0;
    for (; str[i]; i++)
    {
        int j = 0;
        for (; sub[j] && str[i + j] && sub[j] == str[i + j]; j++) {}
        if (sub[j] == '\0')
            return i + j;
    }
    return -1;
}

int are_strs_same(char * first, char * second)
{
    int i = 0;
    for (; first[i] && second[i]; i++)
        if (first[i] != second[i])
            return 0;

    if (first[i] || second[i])
        return 0;

    return 1;
}

int is_among(int * items, int num_of_items, int item)
{
    int i = 0;
    for (; i < num_of_items; i++)
        if (item == items[i])
            return 1;

    return 0;
}

void out_str_wo_nl(char * str)
{
    if (str == NULL)
        return;

    int i = 0;
    for (; str[i] && str[i] != '\n'; i++)
        printf("%c", str[i]);
}
