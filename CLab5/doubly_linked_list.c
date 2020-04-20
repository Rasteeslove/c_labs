#include "clab5.h"

struct m_number * find_head(struct m_number * number);
struct m_number * find_tail(struct m_number * number);

char is_single_digit(struct m_number * number)
{
    if (number == NULL)
    {
        return 0;
    }
       
    if (number->next == NULL && number->pre == NULL)
        return 1;
    return 0;
}

struct m_number * new_m_number(char first_digit)  
{
    struct m_number * root;
    root = (struct m_number *)malloc(sizeof(struct m_number));
    
    root->digit = first_digit;
    root->next = NULL; 
    root->pre = NULL; 

    return root;
}

struct m_number * add_digit_to_number(struct m_number * list_node, char new_digit)
{
    if (list_node == NULL)
        return new_m_number(new_digit);
    
    struct m_number * new_node, * tmp;
    
    new_node = (struct m_number *)malloc(sizeof(struct m_number));

    tmp = list_node->next; 
    list_node->next = new_node; 
    new_node->digit = new_digit; 
    new_node->next = tmp; 
    new_node->pre = list_node;

    if (tmp != NULL)
        tmp->pre = new_node;
 
    return new_node;
}

struct m_number * delete_digit_from_number(struct m_number * odd_node)
{
    if (odd_node == NULL)
    {
        return NULL;
    }

    struct m_number * previous_node, * next_node;
    previous_node = odd_node->pre; 
    next_node = odd_node->next;

    if (previous_node != NULL)
        previous_node->next = odd_node->next;

    if (next_node != NULL)
        next_node->pre = odd_node->pre; 

    free(odd_node);

    return(previous_node);
}

struct m_number * simplify(struct m_number * number)
{
    if (number == NULL)
    {
        return NULL;
    }

    number = find_tail(number);

    while (number->digit == 0 && !is_single_digit(number))                     
        number = delete_digit_from_number(number);
     
    number = find_head(number);

    return number;
}

struct m_number * copy_m_number(struct m_number * number)
{
    if (number == NULL)
    {
        return NULL;
    }

    struct m_number * new_number = NULL;
    
    number = find_head(number);

    while (number != NULL)
    {
        new_number = add_digit_to_number(new_number, number->digit);
        number = number->next;
    }

    new_number = find_head(new_number);

    return new_number;
}

struct m_number * reversed_number(struct m_number * number)
{
    if (number == NULL)
    {
        return NULL;
    }

    struct m_number * reversed = NULL;

    number = find_tail(number);

    while (number != NULL)
    {
        reversed = add_digit_to_number(reversed, number->digit);
        number = number->pre;
    }

    reversed = find_head(reversed);

    return reversed;
}

struct m_number * find_tail(struct m_number * number)
{
    if (number == NULL)
    {
        return NULL;
    }

    while (number->next != NULL)
        number = number->next;

    return number;
}

struct m_number * find_head(struct m_number * number)
{
    if (number == NULL)
    {
        return NULL;
    }

    while (number->pre != NULL)
        number = number->pre;

    return number;
}

int delete_number(struct m_number * number) // returns 1 if success, 0 otherwise
{
    if (number == NULL)
    {
        return 0;
    }

    number = find_tail(number);

    while (number != NULL)
        number = delete_digit_from_number(number);
    
    return 1;
}