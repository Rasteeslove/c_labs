#include <conio.h>

#define ENTER 13
#define BACKSPACE 8

#include "clab5.h"
  
int is_number(char symbol)
{
    if (symbol >= '0' && symbol <= '9')
        return 1;
    return 0;
}

struct m_number * set_number_via_console()
{
    char chinput;
    struct m_number * new_number = NULL;

    while ((chinput = getch()) != ENTER)
    {
        if (is_number(chinput))
        {
            new_number = add_digit_to_number(new_number, chinput - '0');
            printf("%c", chinput);
        }
        else if (chinput == BACKSPACE)
        {
            new_number = delete_digit_from_number(new_number);
            printf("\b \b");
        }
    }
    printf("\n");

    struct m_number * tmp = new_number;
    new_number = reversed_number(new_number);

    if (delete_number(tmp) == 0)
    {
        return NULL;
    }

    new_number = simplify(new_number);
    return new_number;
}

void output_number_via_console(struct m_number * number)
{
    number = find_tail(number);

    while (number != NULL)
    {
        printf("%c", '0' + number->digit);
        number = number->pre;
    }
}