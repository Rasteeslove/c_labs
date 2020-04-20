#include <stdio.h>
#include <stdlib.h>

struct m_number
{
    struct m_number * pre;
    char digit;
    struct m_number * next;
};

struct m_number * set_number_via_console();
void output_number_via_console(struct m_number * number);

struct m_number * find_tail(struct m_number * number);
struct m_number * find_head(struct m_number * number);

struct m_number * add_digit_to_number(struct m_number * list_node, char new_digit);
struct m_number * delete_digit_from_number(struct m_number * odd_node);
int delete_number(struct m_number * number);

struct m_number * copy_m_number(struct m_number * number);
struct m_number * reversed_number(struct m_number * number);

struct m_number * simplify(struct m_number * number);
struct m_number * euklids_gcd_of_two(struct m_number * first, struct m_number * second);

void task_one();
