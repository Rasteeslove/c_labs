#include <stdio.h>
#include <conio.h>
#include <windows.h>

typedef struct date
{
    int year, month, day;
} date;

typedef struct project
{
    char * name;

    struct date start_date;
    struct date finish_date;

    int number_of_developers;
} project;

extern const int months[];

char * file_name;
int number_of_projects;
project * projects;

int day_of_the_week(date one);
int is_a_leap_year(int year);
unsigned int duration_in_work_days_of(project one);

date new_date();
project new_project(char * name, date start, date finish, int num_of_devs);

char * get_string(FILE * file_or_con);
void get_data_from_file();
void write_data_to_file();

void report_error(char * message);
void main_menu();
