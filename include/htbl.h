#ifndef __HTBL_H
#define __HTBL_H

#include <stdbool.h>
#include "liste.h"

typedef struct htbl_s {
    int n; // The size of the tbl array
    list* tbl; // the array of lists.
} htbl;

htbl* init_htbl(int n);
bool is_in_htbl(htbl t, t_film* e);
void add_elem_htbl(htbl* t_ptr, t_film* e);

void print_htbl(htbl t);

void free_htbl(htbl** t_ptr);

#endif
