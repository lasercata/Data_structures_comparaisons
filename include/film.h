#ifndef __FILM_H
#define __FILM_H

#include <stdbool.h>

typedef struct {
    int num;
    char* titre;
    int annee;
} t_film;

t_film* creer_film(char* data);
void liberer_film(t_film *pt_film);

char* titre_film(t_film* pt_film);
int annee_film(t_film* pt_film);
void afficher_film(t_film *pt_film);

bool equals(t_film* f1, t_film* f2);
bool le(t_film* f1, t_film* f2);

#endif
