#include "clab6.h"

b_node * new_node(char * str)
{
    b_node * new_node = (b_node*)malloc(sizeof(b_node));

    new_node->left = new_node->right = NULL;
    new_node->str = str;

    return new_node;
}

b_node * move_to(b_node * root, int coordinate)
{
    if (root == NULL || coordinate <= 0)
        return NULL;

    while (coordinate > 1)
    {
        if (coordinate % 2)
        {
            if (root->right == NULL)
                root->right = new_node(NULL);
            
            root = root->right;
        }
        else
        {
            if (root->left == NULL)
                root->left = new_node(NULL);
            
            root = root->left;
        }

        coordinate /= 2;
    }

    return root;
}

void delete_tree(b_node * root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->str != NULL)
    {
        free(root->str);
        root->str = NULL;
    }

    if (root->left != NULL)
        delete_tree(root->left);

    if (root->right != NULL)
        delete_tree(root->right); 

    root->left = root->right = NULL;
    free(root);
}