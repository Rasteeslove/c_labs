#include "clab6.h"

#define MAX_NUM_LEN 9
#define DEF_STR_LEN 16

int yes_function(char * anything);
int task_filter(char * str);
void move_strs(b_node * root, stack * str_stack, int (*filter)(char*));

int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;

    return 0;
}

int length_of(char * str)
{
    if (str == NULL)
    {
        return 0;
    }

    int i = 0;
    for (; str[i]; i++) {}

    return i + 1;
}

char * copy_str(char * original)
{
    if (original == NULL)
    {
        return NULL;
    }

    int size = length_of(original) + 1;

    char * copied = (char*)malloc(size * sizeof(char));

    if (copied == NULL)
    {
        printf("\nMemory error\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    for (; i < size - 1; i++)
        copied[i] = original[i];

    copied[size - 1] = '\0';

    return copied;
}

void task()
{
    #pragma region input



    printf("1: Input of the tree:\n\n");
    
    char * num_buff;
    int coordinate;
    b_node * root = new_node(NULL);
    printf("Enter the coordinate of the node: ");          /* + 1 bc \0 */
    while (length_of(num_buff = get_string(stdin, MAX_NUM_LEN + 1)) > 1)   /* if there's more than '\0' in entered 'coordinate' */
    {

        #pragma region checking length

        if (length_of(num_buff) > MAX_NUM_LEN + 1)      /* +1 bc \n */
        {
            printf("The input line is too long\n");
            printf("Enter the coordinate of the node: ");
            continue;
        }

        #pragma endregion

        #pragma region converting string to int

        coordinate = 0;
        int i = 0;
        for (; num_buff[i]; i++)
        {
            if (!is_digit(num_buff[i]))
                break;

            coordinate = coordinate * 10 + (num_buff[i] - '0');
        }

        #pragma endregion

        #pragma region checking if int is zero

        if (coordinate == 0)
        {
            printf("Can't enter zero. No such coordinate\n");
            printf("Enter the coordinate of the node: ");
            continue;
        }

        #pragma endregion

        #pragma region moving to the node of the entered coordinate

        b_node * cur_node = move_to(root, coordinate);

        #pragma endregion

        #pragma region getting string for the node or replacing the existing one

        if (cur_node->str != NULL) 
            free(cur_node->str);
        
        printf("Enter the string for the coordinate #%d: ", coordinate);

        cur_node->str = get_string(stdin, DEF_STR_LEN);

        #pragma endregion

        printf("Enter the coordinate of the node: ");
        free(num_buff);
    }

    free(num_buff);



    #pragma endregion

    #pragma region processing and output



    #pragma region checking if the tree is empty

    if (root->left == NULL && root->right == NULL && root->str == NULL)
    {
        printf("\nThe tree is empty.");
        return;
    }

    #pragma endregion

    #pragma region moving all strings to stack

    stack * str_stack = new_stack();

    move_strs(root, str_stack, yes_function);

    #pragma endregion

    #pragma region stack output and clearing 

    printf("\n2: Output of all strings:\n\n");
    
    while (str_stack->size > 0)
    {
        char * tmp = pop(str_stack);
        if (length_of(tmp) == 0)
            printf("(empty string)");
        printf("%s\n", tmp);
        free(tmp);
    }

    #pragma endregion

    #pragma region moving all sum-of-char-codes-is-even strings to stack

    move_strs(root, str_stack, task_filter);

    #pragma endregion

    #pragma region stack output

    printf("\n3: Output of all sum-of-char-codes-is-even strings:\n\n");

    int i = 0;
    for (; i < str_stack->size; i++)
    {
        if (length_of(str_stack->strs[i]) == 0)
            printf("(empty string)");
        printf("%s\n", str_stack->strs[i]);
    }
    #pragma endregion

    #pragma region deleting the stack and the tree

    delete_stack(str_stack);
    delete_tree(root);

    #pragma endregion 



    #pragma endregion
}

void move_strs(b_node * root, stack * str_stack, int (*filter)(char*))
{
    if (root == NULL || str_stack == NULL || filter == NULL)
    {
        return;
    }

    if (root->str != NULL && filter(root->str))
        push(str_stack, copy_str(root->str));
    
    if (root->left != NULL)
        move_strs(root->left, str_stack, filter);

    if (root->right != NULL)
        move_strs(root->right, str_stack, filter);    
}

int task_filter(char * str)
{
    if (str == NULL)
        return 0;

    int counter = 0;

    int i = 0;
    for (; str[i]; i++)
        counter += str[i];

    if (counter % 2 == 0)
        return 1;

    return 0;
}

int yes_function(char * anything)
{
    if (anything == NULL)
        return 0;

    return 1;
}