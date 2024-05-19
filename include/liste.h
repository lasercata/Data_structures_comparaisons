#ifndef _LISTE_H
#define _LISTE_H

#include <stdbool.h>
#include "../include/film.h"

// définir le type list (typedef ...)
struct link_s {
    // int elem;
    t_film* elem;
    struct link_s* next;
};
typedef struct link_s* list;


// prototypes des méthodes

// creation liste vide
list creer_liste();
// ajout en tete de liste de element avec modification de la liste
void ajout_entete_liste(list* l, t_film* elem);
// ajout en tete selon une approche fonctionnelle sans modification de la liste
list ajouter_entete_fonc(list l, t_film* elem);

// affichages
// itératif
void afficher_liste(list l);
// récursif dans l ordre de la liste
void fafficher_dir_liste(list l);
// récursif dans l ordre inverse de la liste
void fafficher_inv_liste(list l);

bool is_in_list(list l, t_film* e);



// inversion iterative d'une liste selon une approche MIS
void inv_mis_liste(list* l);
// inversion iterative d'une liste selon une approche fonctionnelle
list inv_fonc_liste(list l);

// comptage du nombre d'elements d'une liste
// selon une approche recursive enveloppee
int long_env(list l);
// selon une approche recursive terminale
int long_ter(list l, int aux);
//
// inversion recursive enveloppee d'une liste
list inversion_rec_env(list l);
// inversion recursive terminale d'une liste
list inversion_rec_term(list l, list inv);

// liberation de la mémoire
void liberer_liste(list l);
#endif
