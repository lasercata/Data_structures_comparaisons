#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/avl.h"
#include "../include/complexite.h"
#include "../include/common.h"


//------Init
avl_tree init_avl_tree() {
    operation_elementaire();

    return (avl_tree) NULL;
}

avl_tree avl_create_node(t_film* i) {
    operation_elementaire();

    // avl_tree t = (avl_tree) malloc(sizeof(struct s_node));
    avl_tree t = (avl_tree) allouer(sizeof(struct s_node));

    if (t != NULL) {
        t->val = i;
        t->left = NULL;
        t->right = NULL;
    }
    else
        fprintf(stderr, "Error with memory allocation\n");

    return t;
}

//------Print
void print_tree_(avl_tree t) {
    operation_elementaire();

    if (t != NULL) {
        printf("<");
        print_tree_(t->left);
        printf(" , %s, ", t->val->titre);
        print_tree_(t->right);
        printf(">");
    }
    else {
        printf("<>");
    }
}

void print_avl_tree(avl_tree t) {
    print_tree_(t);
    printf("\n");
}

//------In_tree
bool in_avl_tree(avl_tree t, t_film* i) {
    /* Checks if i is in the tree t. */

    operation_elementaire();

    if (t == NULL)
        return false;

    if (equals(t->val, i))
        return true;

    else if (le(i, t->val))
        return in_avl_tree(t->left, i);

    return in_avl_tree(t->right, i);
}

//------Rotations
void left_rotation_(avl_tree* t_ptr) {
    // precondition : arbre de hauteur 1 avec son sous-arbre droit non vide

    operation_elementaire();

    // if ((*t_ptr)->right == NULL) {
    //     fprintf(stderr, "left_rotation_: error: right sub tree should not be empty\n");
    //     exit(EXIT_FAILURE);
    // }

    avl_tree tmp = *t_ptr;
    *t_ptr = (*t_ptr)->right;
    tmp->right = (*t_ptr)->left;
    (*t_ptr)->left = tmp;
}

void avl_left_rotation(avl_tree* t_ptr) {
    // Same as above, but changes 'eq'

    operation_elementaire();

    left_rotation_(t_ptr);

    (*t_ptr)->eq++;
    (*t_ptr)->left->eq++;
    // (*t_ptr)->eq = 0;
    // (*t_ptr)->left->eq = 0;
}

void right_rotation_(avl_tree* t_ptr) {
    // precondition : arbre de hauteur 1 avec son sous-arbre gauche non vide

    operation_elementaire();

    if ((*t_ptr)->left == NULL) {
        fprintf(stderr, "right_rotation_: error: left sub tree should not be empty\n");
        exit(EXIT_FAILURE);
    }

    avl_tree tmp = *t_ptr;
    *t_ptr = (*t_ptr)->left;
    tmp->left = (*t_ptr)->right;
    (*t_ptr)->right = tmp;
}

void avl_right_rotation(avl_tree* t_ptr) {
    // precondition : arbre de hauteur 1 avec son sous-arbre gauche non vide

    operation_elementaire();

    right_rotation_(t_ptr);

    // Update eq
    (*t_ptr)->eq--;
    (*t_ptr)->right->eq--;
    // (*t_ptr)->eq = 0;
    // (*t_ptr)->right->eq = 0;
}

void avl_left_right_rotation(avl_tree* t_ptr) {
    // precondition : arbre de hauteur 2 avec son sous-arbre droit puis gauche non vide

    operation_elementaire();

    //init
    avl_tree old_root = *t_ptr;
    avl_tree old_left = (*t_ptr)->left;
    avl_tree old_left_right = old_left->right;

    // Rotations
    left_rotation_(&((*t_ptr)->left));
    right_rotation_(t_ptr);

    // Eq updates
    switch(old_left_right->eq) {
        case 1:
            old_root->eq = -1;
            old_left->eq = 0;
            break;
        case -1:
            old_root->eq = 0;
            old_left->eq = 1;
            break;
        case 0:
            old_root->eq = 0;
            old_left->eq = 0;
            break;
    }

    // mise a jour du degre de la future racine
    old_left_right->eq = 0;
}

void avl_right_left_rotation(avl_tree* t_ptr) {
    // precondition : arbre de hauteur 2 avec son sous-arbre gauche puis sous sous-droit non vide

    operation_elementaire();

    //init
    avl_tree old_root = *t_ptr;
    avl_tree old_right = (*t_ptr)->right;
    avl_tree old_right_left = old_right->left;

    // Rotations
    right_rotation_(&((*t_ptr)->right));
    left_rotation_(t_ptr);

    // Eq updates
    switch(old_right_left->eq) {
        case 1:
            old_root->eq = 0;
            old_right->eq = -1;
            break;
        case -1:
            old_root->eq = 1;
            old_right->eq = 0;
            break;
        case 0:
            old_root->eq = 0;
            old_right->eq = 0;
            break;
    }

    old_right_left->eq = 0;
}

//------Insertion
void insertion(avl_tree* t_ptr, t_film* i, bool* height_changed_ptr) {
    /*
    Inserts i into *t_ptr.

    - avl_tree* t_ptr          : a pointer to the tree into which insert the element ;
    - int i                    : the element to insert ;
    - bool* height_changed_ptr : (out) a boolean indicating if the height has been changed.
    */

    operation_elementaire();

    if (*t_ptr == NULL) { // Base case
        *t_ptr = avl_create_node(i);

        if (*t_ptr == NULL) {
            fprintf(stderr, "Error with memory allocation\n");
            *height_changed_ptr = false;
            exit(EXIT_FAILURE);
        }
        else
            *height_changed_ptr = true;
    }
    else { // HR : on sait insérer un element dans un arbre de hauteur plus petite
        if (le(i, ((*t_ptr)->val))) { // Insertion in the left sub-tree
            insertion(&((*t_ptr)->left), i, height_changed_ptr);

            if (*height_changed_ptr) {
                switch(((*t_ptr)->eq)) {
                    case -1:
                        ((*t_ptr)->eq) = 0;
                        *height_changed_ptr = false;
                        break;

                    case 0:
                        ((*t_ptr)->eq) = 1;
                        *height_changed_ptr = true;
                        break;

                    case 1:
                        if ((((*t_ptr)->left)->eq) == 1) {
                            // simple right rotation
                            avl_right_rotation(t_ptr);
                        }
                        else {
                            // double rotation
                            avl_left_right_rotation(t_ptr);
                        }

                        *height_changed_ptr = false;
                        break;
                }
            }
        }
        else { // Insertion in the right sub-tree
            insertion(&((*t_ptr)->right), i, height_changed_ptr);

            //TODO: check that it is correct (I changed 1 to -1, r to l, ...)
            if (*height_changed_ptr) {
                switch(((*t_ptr)->eq)) {
                    case 1:
                        ((*t_ptr)->eq) = 0;
                        *height_changed_ptr = false;
                        break;

                    case 0:
                        ((*t_ptr)->eq) = -1;
                        *height_changed_ptr = true;
                        break;

                    case -1:
                        if ((((*t_ptr)->right)->eq) == -1) {
                            // simple left rotation
                            avl_left_rotation(t_ptr);
                        }
                        else {
                            // double rotation
                            avl_right_left_rotation(t_ptr);
                        }

                        *height_changed_ptr = false;
                        break;
                }
            }
        }
    }
}

void avl_leaf_insertion(avl_tree* t_ptr, t_film* i) {
    // Inserts i in the tree *t_ptr.

    bool height_changed_ptr = false;
    insertion(t_ptr, i, &height_changed_ptr);
}

//------Is_avl
bool is_avl_a_bst(avl_tree t) {
    /*Recursively checks if t is well a binary search tree.*/

    if (t == NULL)
        return true;

    if (t->left != NULL && le(t->val, t->left->val))
        return false;

    if (t->right != NULL && le(t->right->val, t->val))
        return false;

    return is_avl_a_bst(t->left) && is_avl_a_bst(t->right);
}

bool is_avl_(avl_tree t, int* height_ptr) {
    /*
    Checks if the tree t is an AVL.

    - avl_tree t        : the tree to check ;
    - int* height_ptr : (out) the height of the tree t. Used and calculated in the procedure.
    */

    //---Base case
    if (t == NULL) {
        *height_ptr = -1;
        return true;
    }

    //---Check that it is a bst
    if (t->left != NULL && le(t->val, t->left->val))
        return false;

    if (t->right != NULL && le(t->right->val, t->val))
        return false;

    //---Check the heights
    int left_h = 0;
    int right_h = 0;

    if (!is_avl_(t->left, &left_h) || !is_avl_(t->right, &right_h))
        return false;


    if (abs(left_h - right_h) > 1)
        return false;

    //---Return
    *height_ptr = 1 + max(left_h, right_h);
    return true;
}

bool is_avl(avl_tree t) {
    /* Checks if the tree t is an AVL. */

    int a;
    return is_avl_(t, &a);
}

int get_avl_height(avl_tree t) {
    /*
    Calculate the tree height.

    - avl_tree t : the AVL tree.
    */

    if (t == NULL)
        return -1;

    //TODO: maybe there will be a stack overflow ...
    return 1 + max(get_avl_height(t->left), get_avl_height(t->right));
}

//------Free
void free_avl_tree_(avl_tree t) {
    /* Frees the tree t, recursively. */

    operation_elementaire();

    if (t != NULL) {
        free_avl_tree_(t->left);
        free_avl_tree_(t->right);

        free(t);
    }
}

void free_avl_tree(avl_tree* t_ptr) {
    /*
    Frees the tree *t_ptr (recursively)

    - avl_tree* t_ptr : a pointer to the tree to free.
    */

    operation_elementaire();

    free_avl_tree_(*t_ptr);
    *t_ptr = NULL;
}
