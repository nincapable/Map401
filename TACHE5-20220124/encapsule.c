#include<stdio.h>
#include "encapsule.h"

void conversion(char *nom_resultat, char *nom_image, char mode){
    FILE *f = fopen(nom_resultat, "w");
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    Image I = lire_fichier_image(nom_image);
    fprintf(f, "%%%%BoundingBox: 0 0 %u %u\n", I.L, I.H);
    fprintf(f, "/l {lineto} def\n");
    fprintf(f, "/m {moveto} def\n");
    fprintf(f, "/s {stroke} def\n");
    fprintf(f, "/f {fill} def\n");

    Robot R;
    Contour C = creer_liste_Point_vide();
    position_initiale(I, &R);
    int nb_seg = contour(I,&R,&C);
    Tableau_Point T=sequence_points_liste_vers_tableau(C);
    int i = 0;
    fprintf(f, "%f %f m ", T.tab[i].x, I.H-T.tab[i].y);
    i++;
    while (i < T.taille)
    {
        double posx = T.tab[i].x;
        double posy = T.tab[i].y;
        fprintf(f, "%f %f l ", posx, I.H-posy);
        i++;
    }
    fprintf(f, "%f %f %c\n", T.tab[0].x, T.tab[0].y,mode);
    fprintf(f, "showpage");
}
