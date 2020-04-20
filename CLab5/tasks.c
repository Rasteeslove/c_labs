#include "clab5.h"

char equals_one(struct m_number * number)
{
    if (number == NULL)
        return 0;
    if (number->digit == 1 && number->pre == NULL && number->next == NULL)
        return 1;
    return 0;
}

void task_one()
{
    // the task is to determine if two numbers are coprime

    struct m_number * first, * second, * gcd;

    first = set_number_via_console();

    second = set_number_via_console();

    gcd = euklids_gcd_of_two(first, second);

    if (equals_one(gcd))
        printf("They're coprime.");
    else   
        printf("They're not coprime.");
}