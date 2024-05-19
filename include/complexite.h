#ifndef __COMPLEXITE_H
#define __COMPLEXITE_H

#include <stdlib.h>

extern size_t compteur_memoire;
extern size_t compteur_op_elementaire;

void init_memory();
void *allouer(size_t taille);
void show_memory();

void initialiser_comp_op_elementaire();
void operation_elementaire();
void afficher_op_elem();

void demarrer_chrono();
void arreter_chrono();
long int temps_chrono();
void stop_chrono_and_print_time(int n);

void afficher_resultat_complexite();
#endif
