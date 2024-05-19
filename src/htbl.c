#include <stdlib.h> // malloc, free
#include <stdio.h> // printf

#include "../include/htbl.h"
#include "../include/complexite.h"


int hash(t_film* f, int n) {
    /*
    Return the hash of the element k for the hash table.

    - t_film* f : the element to hash ;
    - int n     : the size of the hash table.
    */

    int k = f->num;

    return k % n;
}

htbl* init_htbl(int n) {
    /*
    Create and initiate (with NULL) a new hash table of size n.

    - int n : the size of the hash table.
    */

    operation_elementaire();

    // htbl* ret = malloc(sizeof(htbl));
    htbl* ret = allouer(sizeof(htbl));

    ret->n = n;
    // ret->tbl = malloc(((long unsigned int) n) * sizeof(list));
    ret->tbl = allouer(((long unsigned int) n) * sizeof(list));

    for (int k = 0 ; k < n ; k++)
        ret->tbl[k] = creer_liste(); // = NULL

    return ret;
}

bool is_in_htbl(htbl t, t_film* e) {
    /*
    Check if the element e is in the table t.

    - htbl t : the hash table ;
    - int e : the element to research for.
    */

    operation_elementaire();

    return is_in_list(t.tbl[hash(e, t.n)], e);
}

void add_elem_htbl(htbl* t_ptr, t_film* e) {
    /*
    Adds e int *t_ptr.

    - htbl* t_ptr : a pointer to the hash table
    - int e       : the element to add to the hash table.
    */

    operation_elementaire();

    int index = hash(e, t_ptr->n);
    list l = (t_ptr->tbl)[index];

    ajout_entete_liste(&l, e);
    // ajout_entete_liste(&((t_ptr->tbl)[index]), e);

    t_ptr->tbl[index] = l;
}

void print_htbl(htbl t) {
    /*
    Prints the hash table t.

    - htbl t : the hash table to print.
    */

    for (int k = 0 ; k < t.n ; k++) {
        operation_elementaire();
        printf("%d : ", k);
        afficher_liste(t.tbl[k]);
    }
}

void free_htbl(htbl** t_ptr) {
    // Frees the hashtable *t_ptr.

    for (int k = 0 ; k < (*t_ptr)->n ; ++k) {
        operation_elementaire();

        liberer_liste((*t_ptr)->tbl[k]);
    }

    free(*t_ptr);
    *t_ptr = NULL;
}
