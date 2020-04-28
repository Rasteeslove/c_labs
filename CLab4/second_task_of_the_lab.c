#include "clab4.h"

int is_digit(char symbol)
{
    if (symbol >= '0' && symbol <= '9')
        return 1;

    return 0;
}

void out_m_num(struct m_number * number)
{
    number = find_tail(number);
    while (number != NULL)
    {
        printf("%d", number->digit);
        number = number->pre;
    }  
}

void second_task_of_the_lab(char * file_name)
{
    FILE * text = fopen(file_name, "r");

    if (text == NULL)
    {
        printf("\nError opening text file in second task of the lab. Probably bc there's no file with such name.\n");
        exit(EXIT_FAILURE);
    }

    /* reading file adding up positive numbers and counting them */
    int s;
    int sign = 0;   /* 0 for +, 1 for - */
    struct m_number * cur_num = NULL, * sum = add_digit_to_number(NULL, 0), * counter = add_digit_to_number(NULL, 0);
    while ((s = fgetc(text)) != EOF)
    {
        if (is_digit(s))
        {
            cur_num = add_digit_to_number(cur_num, s - '0');
        } 
        else
        {
            /* if we just finished reading number in file */
            if (cur_num != NULL)
            {
                #pragma region deleting number if it is negative and resuming reading

                if (sign == 1)
                {
                    if (delete_number(cur_num) == 0)
                    {
                        printf("\nSomething went wrong in the 1st number deleting process\n");
                        exit(EXIT_FAILURE);
                    }  
                    cur_num = NULL;
                    sign = 0;

                    continue;
                }

                #pragma endregion

                #pragma region reversing read number and simplifying it
                
                struct m_number * tmp_cur = reversed_number(cur_num);
                if (delete_number(cur_num) == 0)
                {
                    printf("\nSomething went wrong in the 2nd number deleting process\n");
                    exit(EXIT_FAILURE);    
                }
                cur_num = simplify(tmp_cur);

                #pragma endregion

                #pragma region adding it to the sum
    
                struct m_number * tmp_sum = sum_for_two_m_numbers(sum, cur_num);
                if (delete_number(sum) == 0 || delete_number(cur_num) == 0)
                {
                    printf("\nSomething went wrong in the 3rd number deleting process\n");
                    exit(EXIT_FAILURE);
                }
                cur_num = NULL;
                sum = tmp_sum;

                #pragma endregion
                
                #pragma region doing ++ for the counter of positive numbers
                
                counter = do_plus_one(counter);

                #pragma endregion
            }
            
            if (s == '-')
                sign = 1;
            else
                sign = 0;
            
        }
    }

    /* if file ends with a positive number */
    if (cur_num != NULL)
    {
        if (sign == 0)
        {
            #pragma region reversing read number and simplifying it
                
            struct m_number * tmp_cur = reversed_number(cur_num);
            if (delete_number(cur_num) == 0)
            {
                printf("\nSomething went wrong in the 2nd number deleting process\n");
                exit(EXIT_FAILURE);    
            }
            cur_num = simplify(tmp_cur);

            #pragma endregion

            #pragma region adding it to the sum
    
            struct m_number * tmp_sum = sum_for_two_m_numbers(sum, cur_num);
            if (delete_number(sum) == 0 || delete_number(cur_num) == 0)
            {
                printf("\nSomething went wrong in the 3rd number deleting process\n");
                exit(EXIT_FAILURE);
            }
            cur_num = NULL;
            sum = tmp_sum;

            #pragma endregion
                
            #pragma region doing ++ for the counter of positive numbers
                
            counter = do_plus_one(counter);

            #pragma endregion
        }
        else
            delete_number(cur_num);
    }
    
    printf("\n\nThe sum of positive numbers in file is:\n");
    out_m_num(sum);    

    printf("\n\nThe number of positive numbers in file is:\n");
    out_m_num(counter); 

    printf("\n\nSo the average positive number is:\n");

    struct m_number ** division = shitty_division(sum, counter);

    out_m_num(division[0]); 
    if (find_tail(division[1])->digit != 0)
    {
        printf(" + ");
        out_m_num(division[1]);
        printf(" / ");
        out_m_num(counter);
    }

    fclose(text);
}