/* ==================================== Include    =================================== */
#include <stdio.h>
#include <stdlib.h>

#include "../include/liste.h"
#include "../include/complexite.h"

/* ==================================== Functions and procedures =================================== */
list creer_liste() {
    // list l = malloc(sizeof(struct link_s));

    operation_elementaire();

    return NULL;
}

void ajout_entete_liste(list* l, t_film* elem) {
    // Adds a link in front of this list.

    operation_elementaire();

    // list new_link = (list) malloc(sizeof(struct link_s));
    list new_link = (list) allouer(sizeof(struct link_s));

    new_link->elem = elem;
    new_link->next = *l;

    *l = new_link;
}

list ajouter_entete_fonc(list l, t_film* elem) {
    // Adds a link in front of the list, and return it.
    // This does not copy the list.

    operation_elementaire();

    // list new_link = (list) malloc(sizeof(struct link_s));
    list new_link = (list) allouer(sizeof(struct link_s));

    new_link->elem = elem;
    new_link->next = l;

    return new_link;
}

void afficher_liste(list l) {
    /*
    Print the list l.
    Iterative method.

    - list l : the list to print.
    */

    if (l == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");

    while (l != NULL) {
        operation_elementaire();

        printf("%s, ", l->elem->titre);
        l = l->next;
    }

    printf("\b\b  \b\b]\n");
}

void rec_print(list l) {
    /*
    Recursively prints the list.
    */

    operation_elementaire();

    if (l == NULL)
        return;

    printf("%s, ", l->elem->titre);
    rec_print(l->next);
}

void fafficher_dir_liste(list l) {
    /*
    Print the list l in order.
    Recursive method.
    */

    operation_elementaire();

    printf("[");
    rec_print(l);
    printf("\b\b  \b\b]\n");
}

void rec_print_inv(list l) {
    /*
    Recursively prints the list in opposite order.
    */

    operation_elementaire();

    if (l == NULL)
        return;

    rec_print_inv(l->next);
    printf("%s, ", l->elem->titre);
}

void fafficher_inv_liste(list l) {
    /*
    Print the list l in opposite order.
    Recursive method.
    */

    operation_elementaire();

    printf("[");
    rec_print_inv(l);
    printf("\b\b  \b\b]\n");

}

bool is_in_list(list l, t_film* e) {
    /*
    Checks if e is in l.

    - list l : the list ;
    - int e  : the element to serach for.
    */

    operation_elementaire();

    if (l == NULL)
        return false;

    if (equals(l->elem, e))
        return true;

    return is_in_list(l->next, e);
}

void inv_mis_liste(list* l) {
    // Reverse the list *l.
    // Move every link to the head, one by one.

    if (*l == NULL)
        return; // The list is empty.

    list prev_pos = *l;
    list current_pos = prev_pos->next;

    while (current_pos != NULL) {
        operation_elementaire();

        prev_pos->next = current_pos->next;
        current_pos->next = *l;
        *l = current_pos;

        current_pos = prev_pos->next;
    }
}
list inv_fonc_liste(list l) {
    // Reverse the list l.
    // Move every link to the head, one by one.

    if (l == NULL)
        return l; // The list is empty.

    list prev_pos = l;
    list current_pos = prev_pos->next;

    while (current_pos != NULL) {
        operation_elementaire();

        prev_pos->next = current_pos->next;
        current_pos->next = l;
        l = current_pos;

        current_pos = prev_pos->next;
    }

    return l;
}

int long_env(list l) {
    // Returns the number of elements in the list l.
    // Non tail recursive.

    operation_elementaire();

    if (l == NULL)
        return 0;

    return 1 + long_env(l->next);
}

int long_ter(list l, int aux) {
    // Returns the number of elements in the list l.
    // Tail recursive.

    operation_elementaire();

    if (l == NULL)
        return aux;

    return long_ter(l->next, aux + 1);
}

list add_in_tail(list l, list link) {
    // Moves link to the end of the list *l.

    operation_elementaire();

    if (l == NULL)
        return link;

    list k = l;
    while (k->next != NULL) {
        operation_elementaire();

        k = k->next;
    }

    k->next = link;
    link->next = NULL;

    return l;
}

list inversion_rec_env(list l) {
    // Recursively reverse the list l.
    // Non tail recursive.
    // O(|l|^2)

    operation_elementaire();

    // Empty list
    if (l == NULL)
        return l;

    // List with one element
    if (l->next == NULL)
        return l;

    // At least two elements
    list first_link = l;
    list inv = inversion_rec_env(l->next);

    // list k = inv;
    // while (k->next != NULL)
    //     k = k->next;
    //
    // k->next = first_link;
    // first_link->next = NULL;
    inv = add_in_tail(inv, first_link);

    return inv;
}

list inversion_rec_term(list l, list inv) {
    // Recursively reverses the list l.
    // call it with inv = NULL.
    // tail recursive.

    operation_elementaire();

    if (l == NULL)
        return inv;

    list queue = l->next;
    l->next = inv;

    return inversion_rec_term(queue, l);

    // return inversion_rec_term(l->next, add_in_tail(inv, l));
}

void liberer_liste(list l) {
    // Recursively frees the list l.

    operation_elementaire();

    if (l == NULL)
        return;

    liberer_liste(l->next);
    l->next = NULL;
    free(l);
}
