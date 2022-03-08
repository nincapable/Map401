#include<stdio.h>
#include "geometrie_2D.h"
#include "image.h"

typedef enum
{
    N,
    NE,
    NW,
    E,
    W,
    S,
    SW,
    SE,
}
Orientation;

typedef struct Coord_P {
    double posx;
    double posy;
} Coord;

typedef struct Robot_R
{
    double x, y;
    Orientation O;
} Robot;

typedef struct Cellule_Liste_Point_{
    Point data;
    struct Cellule_Liste_Point_* suiv;
} Cellule_Liste_Point;

typedef struct Liste_Point_{
    unsigned int taille;
    Cellule_Liste_Point *first;
    Cellule_Liste_Point* last;
} Liste_Point;

typedef Liste_Point Contour;

typedef struct Tableau_Point_ {
    unsigned int taille;
    Point *tab;
} Tableau_Point;

Coord
voisin_pixel(Coord couple, Orientation O);

Point voisin_point(Point couple, Orientation O);

void position_initiale (Image I, Robot *R);

void affichage_positions_rob(Robot R);

void memoriser_position(Robot R, Contour *L);

void memoriser_positionT1(Robot R, char *nom_fichier);

void avancer ( Robot *R);

void print_orientation(Robot *R);

void nouvelle_orientation(Image I, Robot *R);

void tourner_droite(Robot *R);

void tourner_gauche(Robot *R);

void contourT1(Image I, Robot *R, char *nom_fichier);

int contour(Image I,Robot *R, Contour *L);



Cellule_Liste_Point *creer_element_liste_Point(Point v);

Contour creer_liste_Point_vide();

Contour ajouter_element_liste_Point(Contour L, Point e);

Contour supprimer_liste_Point(Contour L);

Contour concatener_liste_Point(Contour L1, Contour L2);

Tableau_Point sequence_points_liste_vers_tableau(Contour L);

void ecrire_contour(Contour L);

void ecrire_contour_fichier(Contour L, FILE *nom_fichier);

void ecrire_info_fichier(Contour L, FILE *nom_fichier);