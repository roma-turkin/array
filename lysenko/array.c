#include "../array.h"
#include <stdlib.h>
#include <stdio.h>

//single node
struct elem{
    DATA value;
    INDEX key;
    struct elem *left_child, *right_child, *parent;
};

//creating the array - the first node of the tree(root)
ARRAY create_array(){
    struct elem *root;
    root = malloc(sizeof(struct elem));
    if (root == NULL) return NULL;
    root -> value = 0;
    root -> key = 0; 
    root -> left_child = NULL;
    root -> right_child = NULL;
    root -> parent = NULL;
    return root;
}

//recursive search for the element
DATA get(ARRAY arr, INDEX x)
{
    struct elem * root = (struct elem *) arr;
    if (root == NULL)
        return NULL;
    if (x == (root -> key)) 
        return (root -> value);
    if (x < root-> key)
        return get(root -> left_child, x);
    else
        return get(root -> right_child, x);
}

//two service functions
struct elem * minimum(struct elem * x)
{
    if (x -> left_child == NULL)
        return x;
    return minimum(x -> left_child);
}

struct elem * next(struct elem * x)
{
    if (x -> right_child != NULL)
        return minimum(x -> right_child);
    struct elem * y = x -> parent;
    while (y != NULL && x== y -> right_child)
    {
        x = y;
        y = y -> parent;
    }
    return y;
}

//insert with smart deleting
int insert(ARRAY arr, INDEX key_t, DATA value_t)
{
    struct elem * root = (struct elem *) arr;
    if (key_t < 0) return -1;
    if (key_t > root -> key)
    {
        if (root -> right_child != NULL)
            insert(root -> right_child, key_t, value_t);
        else
        {
            struct elem *new = malloc(sizeof(struct elem));
            if (!new) return -1;
            new -> parent = root;
            root -> right_child = new;
            new -> value = value_t;
            new -> key = key_t;
            new -> left_child = NULL;
            new -> right_child = NULL;
            return 0;
        }
    }
    if (key_t < root -> key)
    {
        if ((root -> left_child) != NULL)
            insert(root -> left_child, key_t, value_t);
        else
        {
            struct elem *new = malloc(sizeof(struct elem));
            if (!new) return -1;
            new -> parent = root;
            root -> left_child = new;
            new -> value = value_t;
            new -> key = key_t;
            new -> right_child = NULL;
            new -> left_child = NULL;
            return 0;
        }
    }
    if (key_t == root -> key && value_t != NULL)
    {
        root -> value = value_t;
    }
    if (key_t == root -> key && value_t == NULL) //deleting element
    {
        struct elem *y;
        struct elem *x;
        if (root->left_child == NULL || root->right_child == NULL) 
            y = root;
        else y = next(root);
        if (y->left_child != NULL) 
            x = y -> left_child;
        else x = y -> right_child;
        if (x != NULL) 
            x -> parent = y -> parent;
        if (y -> parent == NULL && x == NULL) 
        {
            y -> value = NULL;
            return 0;
        }
        if (y -> parent == NULL)
        {
            //printf("ROOT");
            y -> left_child = x -> left_child;
            y -> right_child = x -> right_child;
            y -> key = x -> key;
            y -> value = x -> value;
            if (x -> right_child != NULL) 
                x -> right_child -> parent = y;
            if (x -> left_child != NULL) 
                x -> left_child -> parent = y;
            free(x);
            return 0;
        }
        else if (y == y -> parent-> left_child) 
            y -> parent -> left_child = x;
        else y -> parent -> right_child = x;
        if (y != root) 
        {
            root -> key = y -> key;
            root -> value = y -> value;
        }
        free(y);
    }
    return 0;
}

//recursive destroy
int destroy_array(ARRAY arr)
{
    struct elem * root = (struct elem *) arr;
    if (root == NULL) return -1;
    destroy_array(root->left_child);
    destroy_array(root->right_child);
    free(root);
    return 0;
}

