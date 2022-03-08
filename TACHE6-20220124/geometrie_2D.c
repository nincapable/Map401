#include<stdio.h>
#include"geometrie_2D.h"

double Norme_vect(Vecteur vect){
    return (double)sqrt(vect.X*vect.X+vect.Y*vect.Y);
};
Point set_point(double x,double y){
    Point P = {x, y};
    return P;
};
Vecteur set_vecteur(Point A, Point B){
    Vecteur V = {B.x - A.x, B.y - A.y};
    return V;
};
Point add_point(Point A, Point B){
    return set_point(A.x + B.x, A.y + B.y);
};
Vecteur add_vect(Vecteur V1, Vecteur V2){
    Vecteur V;
    V.X = V1.X + V2.X;
    V.Y = V1.Y + V2.Y;
    return V;
};
double prod_scal(Vecteur V1, Vecteur V2){
    return V1.X * V2.X + V1.Y * V2.Y;
};
double distance_point(Point A, Point B){
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
};
Vecteur prod_vecteur(Vecteur V1, double lambda){
    Vecteur V;
    V.X = V1.X * lambda;
    V.Y = V1.Y * lambda;
    return V;
};
Point prod_point(Point A, double lambda){
    Point P;
    P.x = A.x * lambda;
    P.y = A.y * lambda;
    return P;
};