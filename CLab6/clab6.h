#include <stdio.h>
#include <stdlib.h>

typedef struct b_node
{
    struct b_node * left, * right;
    char * str;
} b_node;

typedef struct stack
{
    int size, capacity;
    char ** strs;
} stack;

b_node * new_node(char * str);
b_node * move_to(b_node * root, int coordinate);
void delete_tree(b_node * root);

stack * new_stack();
void push(stack * this, char * new_str);
char * pop(stack * this);
void delete_stack(stack * this);

void task();

char * get_string(FILE * file_or_con, size_t def_size);