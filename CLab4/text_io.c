#include "clab4.h"

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

    str[len++] = '\n';

    if (len == def_size)
    {
        str = (char*)realloc(str, sizeof(char) * (def_size *= 2));
        if (str == NULL)
            return str;
    }

    str[len++] = '\0';

    return (char*)realloc(str, sizeof(char) * len);
}

char * read_text(char * name, int (*condition_for_reading)()) 
{        
    FILE * text = fopen(name, "a");

    if (text == NULL)
    {
        printf("\nError creating or opening text file\n");
        exit(EXIT_FAILURE);
    }

    char * line;
    while (condition_for_reading())
    {
        line = get_string(stdin, DEF_LINE_LEN);
        
        int num;
        if ((num = fputs(line, text)) == EOF) 
        {
            printf("\nError writing to file\n");
            exit(EXIT_FAILURE);    
        }
        free(line);
    }
    
    fclose(text);

    return name;
}

void write_text(char * name)
{
    FILE * text = fopen(name, "r");
    
    if (text == NULL)
    {
        printf("\nError opening text file for reading\n");
        exit(EXIT_FAILURE);
    }

    int s;

    while ((s = fgetc(text)) != EOF)
        printf("%c", s);
    

    fclose(text);
}