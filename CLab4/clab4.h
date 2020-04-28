#include <stdio.h>
#include <windows.h>
#include <locale.h> 
#include <stdlib.h>

#define MAX_LINE_LEN 64
#define DEF_LINE_LEN 16

struct m_number
{
    struct m_number * pre;
    char digit;
    struct m_number * next;
};

char * read_text(char * name, int (*condition_for_reading)());
void write_text(char * text);
void leave_first_letters(char * name);
void out_same_lets(char * name);

void second_task_of_the_lab(char * file_name);

struct m_number * find_head(struct m_number * number);
struct m_number * find_tail(struct m_number * number);
struct m_number * add_digit_to_number(struct m_number * list_node, char new_digit);
struct m_number * copy_m_number(struct m_number * number);
struct m_number * simplify(struct m_number * number);
int delete_number(struct m_number * number);
struct m_number * sum_for_two_m_numbers(struct m_number * first_number, struct m_number * second_number);
struct m_number * reversed_number(struct m_number * number);
struct m_number ** shitty_division(struct m_number * dividend, struct m_number * divisor);
struct m_number * do_plus_one(struct m_number * number);
