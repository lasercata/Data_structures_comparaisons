#ifndef __AVL_H
#define __AVL_H

#include <stdbool.h>
#include "../include/film.h"

#define MAX 20

// node struct
struct s_node {
    // int val;
    t_film* val;
    int eq; // in -1 0 1
    struct s_node* left;
    struct s_node* right;
};

// tree type
typedef struct s_node* avl_tree;

// Functions
avl_tree init_avl_tree();
bool in_avl_tree(avl_tree t, t_film* i);

void print_avl_tree(avl_tree t);

void avl_left_rotation(avl_tree* t_ptr);
void avl_right_rotation(avl_tree* t_ptr);
void avl_left_right_rotation(avl_tree* t_ptr);
void avl_right_left_rotation(avl_tree* t_ptr);

void avl_leaf_insertion(avl_tree* t_ptr, t_film* i);

bool is_avl_a_bst(avl_tree t);
bool is_avl(avl_tree t);
int get_avl_height(avl_tree t);

void free_avl_tree(avl_tree* t_ptr);

#endif
