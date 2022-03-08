#include<stdio.h>

typedef struct Segment_t
{
    Point P1;
    Point P2;
    double Longueur;
} Segment;

typedef struct cellule_segment_t{
    Segment seg;
    cellule_segment_t *suivant;
} cellule_segment;

typedef struct Seq_segment_t
{
    int taille;
    cellule_segment *tete;
    cellule_segment *last;
}Seq_segment;
