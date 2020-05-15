#include "clab4.h"

char is_letter(char symbol);
void add_letter(char new_letter, int * letters);
char is_letter_checked(char new_letter, int letters);

/* first task : */
void leave_first_letters(char * name)
{
    FILE * text = fopen(name, "r+");

    if (text == NULL)
    {
        printf("\nError opening file in the first task\n");
        exit(EXIT_FAILURE);
    }

    int letters_checked = 0;
    char cur_letter;                                            /* насколько это нормально / юзлесс? */
    while ((cur_letter = fgetc(text)) != EOF && letters_checked != 0b00000011111111111111111111111111)
    {
        if (cur_letter == '\n')
            continue;

        if ((is_letter(cur_letter) && !is_letter_checked(cur_letter % 'a' % 'A', letters_checked)))
        {
            add_letter(cur_letter % 'a' % 'A', &letters_checked);
            continue;    
        }
            fseek(text, -1, SEEK_CUR);
            fputc(' ', text);
            fseek(text, 0, SEEK_CUR);
    }

    while ((cur_letter = fgetc(text)) != EOF)
    {
        if (cur_letter == '\n')
            continue;

        fseek(text, -1, SEEK_CUR);
        fputc(' ', text);
        fseek(text, 0, SEEK_CUR);
    }

    fclose(text);
}

void check_if_same_lets(char * word, int len)
{   
    if (word[0] % 'a' % 'A' == word[len - 2] % 'a' % 'A')
        printf("%s\n", word);   
}

/* second task : */
void out_same_lets(char * name)
{
    FILE * text = fopen(name, "r");

    if (text == NULL)
    {
        printf("\nError opening file in the second task\n");
        exit(EXIT_FAILURE);
    }

    int cur_letter, cur_len = 0, cur_capacity = DEF_LINE_LEN;
    char * cur_word = NULL;
    while ((cur_letter = fgetc(text)) != EOF)
    {
        
        if (is_letter(cur_letter))
        {
            if (cur_len == 0)
                cur_word = (char*)calloc(cur_capacity, sizeof(char));    
            else if (cur_len == cur_capacity)
                cur_word = (char*)realloc(cur_word, sizeof(char) * (cur_capacity *= 2));

            cur_word[cur_len] = (char)cur_letter;
            cur_len++;
        } 
        else
        {
            if (cur_word == NULL)
                continue;
            cur_word = (char*)realloc(cur_word, sizeof(char) * (cur_len + 1));
            cur_word[cur_len] = '\0';

            check_if_same_lets(cur_word, cur_len + 1);

            cur_len = 0;
            cur_capacity = DEF_LINE_LEN;
            free(cur_word);
            cur_word = NULL;    
        }

    }

    fclose(text);
}

int modify_bit(int number, char position, int new_bit) 
{ 
    int mask = 1 << position; 
    return (number & ~mask) | ((new_bit << position) & mask); 
} 

void add_letter(char new_letter, int * letters)
{
    *letters = modify_bit(*letters, new_letter, 1);
}

char is_letter_checked(char new_letter, int letters)
{
    return (letters >> new_letter) % 2;
}

char is_letter(char symbol)
{
    if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
        return 1;
    return 0;
}

