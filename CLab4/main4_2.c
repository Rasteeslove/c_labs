#include "clab4.h"

int main()
{
    /* нужно, чтобы в папке лабы лежал текст */

    printf("Create text file with text in the lab\'s folder then enter its name: ");

    char text_name[DEF_LINE_LEN];
    fgets(text_name, DEF_LINE_LEN, stdin);

    int i = 0;
    for (; i < DEF_LINE_LEN && text_name[i]; i++)
        if (text_name[i] == '\n')
            text_name[i] = '\0';

    second_task_of_the_lab(text_name);

    return 0;
}