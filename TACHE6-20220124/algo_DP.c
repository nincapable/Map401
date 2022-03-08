#include <stdio.h>
#include "algo_DP.h"
#include"calcul_contour_multiples.h"

Seq_segment simplification_DP(Contour C,int j1,int j2,double d){
    Segment S;
    Seq_segment L;
    Seq_segment *temp = L.tete;
    // Contour *S = (Contour *)malloc(sizeof(Contour));
    // liste_contour *L=(liste_contour *)malloc(sizeof(liste_contour));
    // S->taille = 0;
    // L->taille = 0;
    // Point P1;
    // Point P2;
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    S.P1 = T.tab[j1];
    S.P2 = T.tab[j2];
    double Dmax=0;
    int k = j1;
    for(int l=j1+1;l<j2;l++){
        double dj = distance_point_segment(T.tab[l],S);
        if (Dmax<dj){
            Dmax=dj;
            k = l;
        }
    }
    if(Dmax<=d){
        L.last->seg = S;
        L.last
    }
    else{
        Seq_segment L1;
        Seq_segment L2;
        L1=simplification_DP(C,j1,k,d);
        L2 = simplification_DP(C, k, j2, d);
        L = concatenation(L1, L2);
    }
}