#include "clab6.h"

#define DEF_STACK_CAP 4

stack * new_stack()
{
    stack * new_stack = (stack*)malloc(sizeof(stack));

    new_stack->capacity = DEF_STACK_CAP;
    new_stack->size = 0;
    new_stack->strs = (char**)malloc(DEF_STACK_CAP * sizeof(char*));

    if (new_stack->strs == NULL)
    {
        printf("\nMemory error\n");
        exit(EXIT_FAILURE);
    }

    return new_stack;
}

void push(stack * this, char * new_str)
{
    if (this->size == this->capacity)
    {
        char ** tmp = (char**)realloc(this->strs, sizeof(char*) * (this->capacity *= 2));
        if (tmp == NULL)
        {
            printf("\nMemory error\n");
            free(this->strs);
            exit(EXIT_FAILURE);
        }
        this->strs = tmp;
    }

    this->strs[this->size] = new_str;
    this->size++;
} 

char * pop(stack * this)
{
    this->size--;
    
    if (this->size == this->capacity / 2 && this->capacity > DEF_STACK_CAP)
    {
        char ** tmp = (char**)realloc(this->strs, sizeof(char*) * (this->capacity /= 2));
        if (tmp == NULL)    /* dunno if this could happen */
        {
            printf("\nMemory error\n");
            free(this->strs);
            exit(EXIT_FAILURE);
        }
        this->strs = tmp;
    }

    char * tmp = this->strs[this->size];
    this->strs[this->size] = NULL;
    return tmp;
}

void delete_stack(stack * this)
{
    while (this->size > 0)
    {
        char * tmp = pop(this);
        free(tmp);
    }

    free(this->strs);
    free(this);
}