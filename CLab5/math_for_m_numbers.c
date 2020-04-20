#include "clab5.h"

// subtraction and 
// gcd

int length_of(struct m_number * number)
{
    if (number == NULL)
    {
        return 0;
    }

    number = find_head(number);
    int i = 0;
    for (; number != NULL; i++)
        number = number->next;

    return i;
}

struct m_number ** get_the_biggest_number(struct m_number ** first, struct m_number ** second);

struct m_number * difference_for_two_m_numbers(struct m_number * first_root, struct m_number * second_root)
{
    struct m_number * difference, 
                    ** big_ptr = get_the_biggest_number(&first_root, &second_root); 

    // return zero if equals
    if (big_ptr == NULL)
    {
        difference = add_digit_to_number(NULL, 0);
        return difference;
    }

    struct m_number * small = ((* big_ptr) == first_root ? second_root : first_root);
        
    // copying big into difference
    difference = copy_m_number((* big_ptr));

    #pragma region subtraction

    char tmp_subtrahend = 0;    // extra subtrahend moving the order up

    while (small != NULL)
    {
        char tmp = (small->digit + tmp_subtrahend > difference->digit ? 1 : 0);
        difference->digit = (10 + difference->digit - small->digit - tmp_subtrahend) % 10;

        tmp_subtrahend = tmp;
        if (difference->next != NULL)
            difference = difference->next;
        small = small->next;
    }

    while (tmp_subtrahend)
    {
        char tmp = (difference->digit == 0 ? 1 : 0);
        difference->digit = (10 + difference->digit - 1) % 10;
        tmp_subtrahend = tmp;
        if (difference->next != NULL)
            difference = difference->next;
    }

    #pragma endregion

    // standardizing
    difference = simplify(difference);

    return difference;
}

struct m_number ** get_the_biggest_number(struct m_number ** first, struct m_number ** second)
{   
    struct m_number * first_num = find_head((* first)), * second_num = find_head((* second));
    
    int i = length_of(first_num), j = length_of(second_num);

    if (i > j)
        return first;
    else if (j > i)
        return second;
    
    while (first_num != NULL && second_num != NULL)
        if (first_num->digit > second_num->digit)
            return first;
        else if (second_num->digit > first_num->digit)
            return second;
        else
        {
            first_num = first_num->pre;
            second_num = second_num->pre;
        }

    return NULL;
}

struct m_number * euklids_gcd_of_two(struct m_number * first, struct m_number * second)
{
    if (first == NULL || second == NULL)
    {
        return NULL;
    }

    struct m_number ** tmp,
                    * first_tmp = copy_m_number(first),
                    * second_tmp = copy_m_number(second);

    while ((tmp = get_the_biggest_number(&first_tmp, &second_tmp)) != NULL)
    {
        struct m_number * tmp_ref;

        if ((* tmp) == first_tmp)
        {
            tmp_ref = first_tmp;
            first_tmp = difference_for_two_m_numbers(first_tmp, second_tmp);
        }
        else 
        {
            tmp_ref = second_tmp;
            second_tmp = difference_for_two_m_numbers(first_tmp, second_tmp);
        }

        delete_number(tmp_ref);
    }
    
    delete_number(second_tmp);

    return first_tmp; 
}