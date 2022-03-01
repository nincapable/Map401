#include<stdio.h>
#include "encapsule.h"

Image masque(Image I, int *compteur);

typedef struct cellule_contour_{
    Contour C;
    struct cellule_contour_ *suivant;
} cellule_contour;

typedef struct liste_contour_{
    unsigned int taille;
    cellule_contour *tete;
    cellule_contour *last;
} liste_contour;

typedef struct tableau_contour_{
    unsigned int taille;
    Contour *tab;
} tableau_contour;

void
supprimer_pixel(Image M, Coord pix, int *compteur);

int contour_new(Image I, Image *M, Robot *R, Contour *C, int *compte);

void calcul_contour_mult(Image I, Robot *R, liste_contour *L,int *compte);

void calcul(Image I, Robot *R, liste_contour *L);

void ajouter_element_liste_contour( liste_contour *L, Contour C);

cellule_contour* creer_element_liste_contour(Contour C);

tableau_contour sequence_contour_liste_vers_tableau(liste_contour L);

void ecrire_liste_contour(liste_contour L);