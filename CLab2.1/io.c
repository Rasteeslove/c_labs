#include "clab2.h"

#define DEF_LINE_LEN 16

char * get_string(FILE * file_or_con);
void write_string_to_file(char * str, FILE * file);
date get_date_from_file(FILE * file);
void write_date_to_file(date one, FILE * file);
project get_project_from_file(FILE * file);
void write_project_to_file(project one, FILE * file);
void write_data_to_file();
void get_data_from_file();

char * get_string(FILE * file_or_con)
{
    char * str;
    int chinput;
    size_t len = 0;
    size_t capacity = DEF_LINE_LEN;

    str = (char*)malloc(sizeof(char) * capacity);
    
    if (str == NULL)
        report_error("memory error");

    while ((chinput = fgetc(file_or_con)) != EOF && chinput != '\n')
    {
        str[len++] = chinput;
        if (len == capacity)
        {
            str = (char*)realloc(str, sizeof(char) * (capacity *= 2));
            if (str == NULL)
                report_error("memory error");
        }
    }

    str[len++] = '\n';

    if (len == capacity)
    {
        str = (char*)realloc(str, sizeof(char) * (capacity += 1));
        if (str == NULL)
            report_error("memory error");

        str[len++] = '\0';
        return str;
    }

    str[len++] = '\0';

    return (char*)realloc(str, sizeof(char) * len);
}

void write_string_to_file(char * str, FILE * file)
{
    if (fputs(str, file) == EOF)
        report_error("error writing string to file");
}

date get_date_from_file(FILE * file)
{
    date new_one;

    if (fscanf(file, "%d %d %d ", &new_one.month, &new_one.day, &new_one.year) == EOF)
        report_error("error getting date from file");

    return new_one;
}

void write_date_to_file(date one, FILE * file)
{
    if (fprintf(file, "%d %d %d ", one.month, one.day, one.year) == EOF)
        report_error("error writing date to file");
}

project get_project_from_file(FILE * file)
{
    project new_one;

    new_one.name = get_string(file);

    new_one.start_date = get_date_from_file(file);
    new_one.finish_date = get_date_from_file(file);

    if (fscanf(file, "%d ", &new_one.number_of_developers) == EOF)
        report_error("error getting project from file");

    return new_one;
}

void write_project_to_file(project one, FILE * file)
{
    write_string_to_file(one.name, file);
    
    write_date_to_file(one.start_date, file);
    write_date_to_file(one.finish_date, file);

    if (fprintf(file, "%d ", one.number_of_developers) == EOF)
        report_error("error writing project to file");
}

void write_data_to_file()
{
    FILE * db = fopen(file_name, "w");

    if (fprintf(db, "%d ", number_of_projects) == EOF)
        report_error("error writing to file");

    int i = 0;
    for (; i < number_of_projects; i++)
        write_project_to_file(projects[i], db);

    fclose(db);
}

void get_data_from_file()
{
    FILE * db = fopen(file_name, "r");

    if (db == NULL)
    {
        printf("The projects file of the set name doesn\'t exist. "
               "Press c to create one or e to exit the app.");

        int choice;
        do
        {
            choice = getch();
        } while (choice != 'c' && choice != 'e');

        if (choice == 'e')
        {
            exit(0);
        }
        else
        {
            FILE * new_file = fopen(file_name, "w");
            fclose(new_file);            
        }
    }

    if (fscanf(db, "%d ", &number_of_projects) == EOF)
    {
        number_of_projects = 0;
        return;
    }

    projects = (project*)malloc(sizeof(project) * number_of_projects);
    if (projects == NULL)
        report_error("memory error");

    int i = 0;
    for (; i < number_of_projects; i++)
        projects[i] = get_project_from_file(db);

    fclose(db);
}
