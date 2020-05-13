#include "clab2.h"

const int month_codes[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
const int twenty_first_century_code = 6;

int is_a_leap_year(int year);
int day_of_the_week(date one);
unsigned int duration_in_work_days_of(project one);

int is_a_leap_year(int year)
{
    if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))
        return 0;

    return 1;
}

unsigned int duration_in_work_days_of(project one) 
{
    unsigned int days = 0;

    #pragma region counting days w/o leap ones

    unsigned int i;
    for (i = one.start_date.year; i < one.finish_date.year; i++)
        days += 365;
    
    for (i = 1; i < one.finish_date.month; i++)
        days += months[i - 1];

    for (i = 1; i <= one.finish_date.day; i++)
        days++;

    for (i = 1; i < one.start_date.month; i++)
        days -= months[i - 1];
    
    for (i = 1; i < one.start_date.day; i++)
        days--;

    #pragma endregion

    #pragma region adding leap days

    for (i = one.start_date.year; i < one.finish_date.year; i++)
        if (is_a_leap_year(i))
            days++;

    if (is_a_leap_year(one.finish_date.year) && one.finish_date.month > 2)
        days++;

    if (is_a_leap_year(one.start_date.year) && one.start_date.month > 2)
        days--;

    #pragma endregion

    #pragma region counting work days

    int start_week_day = day_of_the_week(one.start_date);
    int finish_week_day = day_of_the_week(one.finish_date);

    /* work days of all weeks */
    unsigned int work_days = (days + start_week_day + 6 - finish_week_day) / 7 * 5;

    /* extracting excluded days of the first week */
    work_days -= (start_week_day < 5 ? start_week_day : 5);

    /* extracting excluded days of the last week */
    work_days -= (finish_week_day < 5 ? 4 - finish_week_day : 0);

    #pragma endregion

    return work_days;
}

int day_of_the_week(date one)
{
    /* https://artofmemory.com/blog/how-to-calculate-the-day-of-the-week-4203.html */
    int week_day_code = ((one.year % 100 + (one.year % 100 / 4)) % 7 + 
        month_codes[one.month - 1] + twenty_first_century_code + one.day -
            ((one.month == 1 || one.month == 2) && is_a_leap_year(one.year) ? 1 : 0)) % 7;

    return (6 + week_day_code) % 7;
}