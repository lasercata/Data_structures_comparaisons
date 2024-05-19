//------Includes
#include <stdlib.h> // malloc, free, NULL, ...
#include <stdio.h> // fprintf, ...
#include <stdbool.h> // bool, true, false

#include "../include/bst.h"
#include "../include/complexite.h"
#include "../include/common.h"


//------Signatures
bst_tree bst_create_node(t_film* v);
void _print_tree_infix(bst_tree t);


//------Implementations
bst_tree create_empty_bst_tree() {
    /*Creates an empty bst_tree.*/

    operation_elementaire();

    return NULL;
}

void free_bst_tree(bst_tree* t_ptr) {
    /*
    Recursively frees the bst_tree *t_ptr.
    This is a friterie.

    - bst_tree* t_ptr : a pointer to the bst_tree to free.
    */

    operation_elementaire();

    if (*t_ptr == NULL)
        return;

    free_bst_tree(&((*t_ptr)->left));
    free_bst_tree(&((*t_ptr)->right));

    free(*t_ptr);
    *t_ptr = NULL;
}

bst_tree bst_create_node(t_film* v) {
    /*
    Allocates and returns a new node (actually a struct node*) containing the element v.

    - int v : the element 
    */

    operation_elementaire();

    // bst_tree ret = (bst_tree) malloc(sizeof(struct node));
    bst_tree ret = (bst_tree) allouer(sizeof(struct node));
    ret->v = v;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

void add_to_bst_tree(bst_tree* t_ptr, t_film* v) {
    /*Adds v to *t_ptr.

    - bst_tree* t_ptr : a pointer to the bst_tree to which add the element ;
    - int v       : the element to add to the bst_tree.
    */

    operation_elementaire();

    if (*t_ptr == NULL) // base case
        *t_ptr = bst_create_node(v);

    else {
        if (le(v, (*t_ptr)->v))
            add_to_bst_tree(&((*t_ptr)->left), v);

        else
            add_to_bst_tree(&((*t_ptr)->right), v);
    }
}

void print_bst_tree_infix(bst_tree t) {
    /*Print the bst_tree t using _print_tree_infix.*/

    operation_elementaire();

    if (t == NULL)
        printf("Empty bst_tree.\n");

    else {
        printf("Root: %s ; bst_tree : ", t->v->titre);
        _print_tree_infix(t);
        printf("\b\b  \b\b\n");
    }
}

void _print_tree_infix(bst_tree t) {
    /*
    Traverses the bst_tree t and prints its content (infix traverse)

    - bst_tree t : the bst_tree to print
    */

    operation_elementaire();

    if (t != NULL) {
        _print_tree_infix(t->left);
        printf("%s, ", t->v->titre);
        _print_tree_infix(t->right);
    }
}

bool in_bst_tree(bst_tree t, t_film* v) {
    /*
    Checks if v is in t.

    - bst_tree t : the bst_tree ;
    - int v  : the value to search for.
    */

    operation_elementaire();

    if (t == NULL)
        return false;

    if (equals(t->v, v))
        return true;

    else if (le(v, t->v))
        return in_bst_tree(t->left, v);

    return in_bst_tree(t->right, v);
}

void bst_right_rotation(bst_tree* t_ptr) {
    /*
    Applies a right rotation to the bst_tree *t_ptr.

    - bst_tree* t_ptr : a pointer to the bst_tree.
    */

    operation_elementaire();

    if (*t_ptr == NULL) {
        fprintf(stderr, "error: bst_right_rotation: empty bst_tree\n");
        return;
    }
    if ((*t_ptr)->left == NULL) {
        fprintf(stderr, "error: bst_right_rotation: empty left sub-bst_tree\n");
        return;
    }

    bst_tree tmp = *t_ptr;
    *t_ptr = tmp->left;

    tmp->left = (*t_ptr)->right;
    (*t_ptr)->right = tmp;
}

void bst_left_rotation(bst_tree* t_ptr) {
    /*
    Applies a right rotation to the bst_tree *t_ptr.

    - bst_tree* t_ptr : a pointer to the bst_tree.
    */

    operation_elementaire();

    if (*t_ptr == NULL) {
        fprintf(stderr, "error: bst_left_rotation: empty bst_tree\n");
        return;
    }
    if ((*t_ptr)->right == NULL) {
        fprintf(stderr, "error: bst_left_rotation: empty left sub-bst_tree\n");
        return;
    }

    bst_tree tmp = *t_ptr;
    *t_ptr = tmp->right;

    tmp->right = (*t_ptr)->left;
    (*t_ptr)->left = tmp;
}

void bst_add_in_root(bst_tree* t_ptr, t_film* v) {
    /*
    Adds v at the root of *t_ptr, keeping an ABR.

    - bst_tree* t_ptr : a pointer to the bst_tree into add v ;
    - int v       : the value to add.
    */

    operation_elementaire();

    if (*t_ptr == NULL)
        *t_ptr = bst_create_node(v);

    else {
        if (le(v, (*t_ptr)->v)) {
            bst_add_in_root(&((*t_ptr)->left), v);
            bst_right_rotation(t_ptr);
        }
        else {
            bst_add_in_root(&((*t_ptr)->right), v);
            bst_left_rotation(t_ptr);
        }
    }
}

bool is_bst(bst_tree t) {
    /*Recursively checks if t is well a binary search tree.*/

    if (t == NULL)
        return true;

    if (t->left != NULL && le(t->v, t->left->v))
        return false;

    if (t->right != NULL && le(t->right->v, t->v))
        return false;

    return is_bst(t->left) && is_bst(t->right);
}

int get_bst_height(bst_tree t) {
    /*
    Calculate the tree height.

    - bst_tree t : the binary search tree.
    */

    if (t == NULL)
        return -1;

    //TODO: maybe there will be a stack overflow ...
    return 1 + max(get_bst_height(t->left), get_bst_height(t->right));
}
