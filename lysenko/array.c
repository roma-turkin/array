#include "array.h"
#include <stdlib.h>
#include <stdio.h>

struct elem{
    DATA value;
    INDEX key;
    struct elem *left_child, *right_child, *parent;
};

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

DATA get(ARRAY arr, INDEX x)
{
    struct elem * root = (struct elem *) arr;
    if ((root == NULL) || (x == (root -> key))) 
        return (root -> value);
    if (x < root-> key)
        return get(root -> left_child, x);
    else
        return get(root -> right_child, x);
}

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
    while (y != NULL && x== y -> left_child)
    {
        x = y;
        y = y -> parent;
    }
    return y;
}


int insert(ARRAY arr, INDEX key_t, DATA value_t)
{
    struct elem * root = (struct elem *) arr;
    if (key_t > root -> key)
    {
        if (root -> right_child != NULL)
            insert(root -> right_child, key_t, value_t);
        else
        {
            struct elem *new = malloc(sizeof(struct elem));
            new -> parent = root;
            root -> right_child = new;
            new -> value = value_t;
            new -> key = key_t;
            new -> left_child = NULL;
            new -> right_child = NULL;
        }
    }
    if (key_t < root -> key)
    {
        if ((root -> left_child) != NULL)
            insert(root -> left_child, key_t, value_t);
        else
        {
            struct elem *new = malloc(sizeof(struct elem));
            new -> parent = root;
            root -> left_child = new;
            new -> value = value_t;
            new -> key = key_t;
            new -> right_child = NULL;
            new -> left_child = NULL;
        }
    }
    if (key_t == root -> key && value_t != NULL)
    {
        root -> value = value_t;
    }
    if (key_t == root -> key && value_t == NULL) //deleting element
    {
        struct elem * x = malloc(sizeof(struct elem));
        struct elem * y = malloc(sizeof(struct elem));
        if (root -> right_child != NULL && root -> left_child != NULL)
        {
            y = next(root);
            x = NULL;
            if (y == y->parent->left_child)
                y->parent->left_child = NULL;
            else
                y->parent->right_child = NULL;
            root -> key = y -> key;
            root -> value = y -> value;
            free(root);
        }
        else if (root -> left_child != NULL || root -> right_child != NULL)
        {
            y = root;
            if (y -> left_child != NULL)
                x = y -> left_child;
            else
                x = y -> right_child;
        }
        else
        {
            y = root;
            x = NULL;
        }
        if (x != NULL)
            x -> parent = y -> parent;
        if (y -> parent == NULL)
            arr = (void *) x;
        else
        {
            if (y == y->parent->left_child)
                y->parent->left_child = x;
            else
                y->parent->right_child = x;
        }
        free(root);
    }
    return 0;
}

int destroy_array(ARRAY arr)
{
    struct elem * root = (struct elem *) arr;
    if (root == NULL) return;
    destroy_array(root->left_child);
    free(root);
    destroy_array(root->right_child);
    return 0;
}

