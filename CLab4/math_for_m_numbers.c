#include "clab4.h"

/* subtraction and 
   gcd */

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

struct m_number * sum_for_two_m_numbers(struct m_number * first_number, struct m_number * second_number)
{
    if (first_number == NULL)
    {
        return copy_m_number(second_number);
    } 
    else if (second_number == NULL)
    {
        return copy_m_number(first_number);
    }

    first_number = find_head(first_number);
    second_number = find_head(second_number);

    struct m_number * result = NULL;
    int tmp_addendum = 0;
    while (first_number != NULL || second_number != NULL)
    {
        result = add_digit_to_number(result, ((first_number != NULL ? first_number->digit : 0) + (second_number != NULL ? second_number->digit : 0) + tmp_addendum) % 10);
        tmp_addendum = ((first_number != NULL ? first_number->digit : 0) + (second_number != NULL ? second_number->digit : 0) + tmp_addendum) / 10;

        if (first_number != NULL)
            first_number = first_number->next;

        if (second_number != NULL)
            second_number = second_number->next;
    }

    if (tmp_addendum)
        result = add_digit_to_number(result, 1);

    return find_head(result);
}

struct m_number * difference_for_two_m_numbers(struct m_number * first_root, struct m_number * second_root)
{
    struct m_number * difference, 
                    ** big_ptr = get_the_biggest_number(&first_root, &second_root); 

    /* return zero if equals */
    if (big_ptr == NULL)
    {
        difference = add_digit_to_number(NULL, 0);
        return difference;
    }

    struct m_number * small_m_num = ((* big_ptr) == first_root ? second_root : first_root);
        
    /* copying big into difference */
    difference = copy_m_number((* big_ptr));

    #pragma region subtraction

    char tmp_subtrahend = 0;    /* extra subtrahend moving the order up */

    while (small_m_num != NULL)
    {
        char tmp = (small_m_num->digit + tmp_subtrahend > difference->digit ? 1 : 0);
        difference->digit = (10 + difference->digit - small_m_num->digit - tmp_subtrahend) % 10;

        tmp_subtrahend = tmp;
        if (difference->next != NULL)
            difference = difference->next;
        small_m_num = small_m_num->next;
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

    /* standardizing */
    difference = simplify(difference);

    return difference;
}

struct m_number ** get_the_biggest_number(struct m_number ** first, struct m_number ** second)
{   
    struct m_number * first_num = find_tail((* first)), * second_num = find_tail((* second));
    
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

struct m_number * do_plus_one(struct m_number * number)
{
    struct m_number * one = add_digit_to_number(NULL, 1);

    if (number == NULL)
        return one;

    struct m_number * tmp = sum_for_two_m_numbers(number, one);

    if (delete_number(one) == 0 || delete_number(number) == 0)
    {
        printf("\nSomething went wrong in the \"do plus one\" number deleting process\n");
        exit(EXIT_FAILURE);
    }

    return tmp;
}

struct m_number ** shitty_division(struct m_number * dividend, struct m_number * divisor)
{
    /* делать полноценное деление длинной арифметики только ради среднего арифметического - довольно неблагодарное занятие, так что вот вычитание со счетчиком */
    struct m_number * result = add_digit_to_number(NULL, 0);

    struct m_number * difference = copy_m_number(dividend);
    while (get_the_biggest_number(&difference, &divisor) == &difference || get_the_biggest_number(&difference, &divisor) == NULL)
    {
        struct m_number * tmp_difference = difference_for_two_m_numbers(difference, divisor);
        if (delete_number(difference) == 0)
        {
            printf("\nSomething went wrong in the number deleting cycle of shitty division\n");
            exit(EXIT_FAILURE);
        }
        difference = tmp_difference;

        result = do_plus_one(result);
    }

    struct m_number ** output = (struct m_number **)calloc(2, sizeof(struct m_number *));
    output[0] = result;
    output[1] = difference;

    return output;
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