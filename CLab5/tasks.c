#include "clab5.h"

int equals_one(struct m_number * number)
{
    if (number == NULL)
        return 0;
    if (number->digit == 1 && number->pre == NULL && number->next == NULL)
        return 1;
    return 0;
}

void task_one()
{
    /* the task is to determine if two numbers are coprime */

    printf("Enter your two numbers (the first, the ENTER, then the second):\n");

    struct m_number * first, * second, * gcd;

    first = set_number_via_console();

    second = set_number_via_console();

    gcd = euklids_gcd_of_two(first, second);

    if (equals_one(gcd))
        printf("They're coprime.");
    else   
        printf("They're not coprime.");

    delete_number(first);
    delete_number(second);
}