#include<stdio.h>
#include <math.h>

typedef struct point_t{
    double x;
    double y;
} Point;

typedef struct vecteur_t{
    double X;
    double Y;
} Vecteur;

double Norme_vect(Vecteur vect);

Point set_point(double x,double y);

Vecteur set_vecteur(Point A, Point B);

Point add_point(Point A, Point B);

Vecteur add_vect(Vecteur V1, Vecteur V2);

double prod_scal(Vecteur V1, Vecteur V2);

double distance_point(Point A, Point B);

Vecteur prod_vecteur(Vecteur V1, double lambda);

Point prod_point(Point A, double lambda);
