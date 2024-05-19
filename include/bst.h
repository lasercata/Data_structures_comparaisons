#ifndef __BST_H
#define __BST_H

#include <stdbool.h>
#include "../include/film.h"

//------Type
struct node {
    // int v;
    t_film* v;
    struct node* left;
    struct node* right;
};

typedef struct node* bst_tree;


//------Signatures
bst_tree create_empty_bst_tree();
void free_bst_tree(bst_tree* t_ptr);
void add_to_bst_tree(bst_tree* t_ptr, t_film* v);

void print_bst_tree_infix(bst_tree t);

bool in_bst_tree(bst_tree t, t_film* v);

void bst_right_rotation(bst_tree* t_ptr);
void bst_left_rotation(bst_tree* t_ptr);

void bst_add_in_root(bst_tree* t_ptr, t_film* v);

bool is_bst(bst_tree t);
int get_bst_height(bst_tree t);

#endif
