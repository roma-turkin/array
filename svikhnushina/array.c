#include <stdio.h>
#include <stdlib.h>
#include "array.h"

typedef struct node node_t;
struct node {
    INDEX index;
    DATA data;
    struct node * right;
    struct node * left;
};

node_t *node_alloc(INDEX ind, DATA dat)
{
    node_t *node;
    if ( !(node = malloc(sizeof(node_t))) ) return NULL;
    node->index = ind;
    node->data = dat;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ARRAY create_array()
{
    node_t **arr;
    arr = malloc(sizeof(node_t*));
    if (arr) *arr = NULL;

    return arr;
}

void destroy_node(node_t *node)
{
    if (node->left) destroy_node(node->left);
    if (node->right) destroy_node(node->right);
    free(node);
}

int destroy_array(ARRAY arr)
//-1 if there is no such array
{
    node_t *root;
    if ( !arr ) return -1;
    root = *((node_t **)arr);
    if ( root ) destroy_node(root);
    free(arr);
    return 0;
}

int insert(ARRAY arr, INDEX ind, DATA dat)
//if DATA = NULL it equals to deleting element, 0 in case of success
{
    node_t **current;  /* address of variable that points to the current node */
    node_t *node;

    if ( !arr ) return -1;
    if (ind < 0) return -1;
    current = arr;
    // if root node doesn't exist yet, create it
    if ( !*current ) {
        if ( !dat ) return -1;
        if ( !(*current = node_alloc(ind, dat)) ) return -1;
        return 0;
    }

    // seek for node
    while ( (*current)->index != ind ) {
        if ( (*current)->index > ind ) {
            if ( (*current)->left ) {
                current = &(*current)->left;
                continue;
            }
//            if ( !dat ) return -1;
            if ( !dat ) return 0;
            if ( !((*current)->left = node_alloc(ind, dat)) ) return -1;
        } else {
            if ( (*current)->right ) {
                current = &(*current)->right;
                continue;
            }
//            if ( !dat ) return -1;
            if ( !dat ) return 0;
            if ( !((*current)->right = node_alloc(ind, dat)) ) return -1;
        }
        return 0;
    }

    /* node with searched index was found */
    if ( dat ) {            // insert
        (*current)->data = dat;
    } else {                // delete
        if ( (*current)->left ) {
            node = (*current)->left;
            while ( node->right ) node = node->right;
            node->right = (*current)->right;
            node = *current;
            *current = (*current)->left;
            free(node);
        } else {
            node = *current;
            *current = (*current)->right;
            free(node);
        }
    }

    return 0;
}

DATA get(ARRAY arr, INDEX ind)
//returns NULL in case of failure
{
    node_t *node;
    if ( !arr ) return NULL;
    node = *((node_t **)arr);
    // seek for node
    while ( node && node->index != ind ) {
        if ( node->index > ind ) node = node->left;
        else node = node->right;
    }
    if ( !node ) return NULL;
    return node->data;
}
