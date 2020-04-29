#include "clab6.h"

/* input of any allocatable line */
char * get_string(FILE * file_or_con, size_t def_size)
{
    char * str;
    int chinput;
    size_t len = 0;
    str = (char*)realloc(NULL, sizeof(char) * def_size);
    
    if (str == NULL)
        return str;

    while ((chinput = fgetc(file_or_con)) != EOF && chinput != '\n')
    {
        str[len++] = chinput;
        if (len == def_size)
        {
            str = (char*)realloc(str, sizeof(char) * (def_size *= 2));
            if (str == NULL)
                return str;
        }
    }

    str[len++] = '\0';

    return (char*)realloc(str, sizeof(char) * len);
}

