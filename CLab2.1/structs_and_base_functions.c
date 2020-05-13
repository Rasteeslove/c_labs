#include "clab2.h"

void report_error(char * message);
date new_date();
project new_project(char * name, date start, date finish, int num_of_devs);

void report_error(char * message)
{
    printf("\n%s\n", message);
    exit(EXIT_FAILURE);
}

date new_date()
{
    date new_one;

    new_one.month = new_one.day = new_one.year = 0;

    return new_one;
}

project new_project(char * name, date start, date finish, int num_of_devs)
{
    project new_one;

    new_one.name = name;
    new_one.start_date = start;
    new_one.finish_date = finish;
    new_one.number_of_developers = num_of_devs;

    return new_one;
}
