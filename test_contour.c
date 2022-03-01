#include <stdio.h>
#include"calcul_contour_multiples.h"

int main(int argc, char **argv){

    Image I = creer_image(7,9);
    set_pixel_image(I, 3, 1, NOIR);
    set_pixel_image(I, 4, 1, NOIR);
    set_pixel_image(I, 5, 1, NOIR);
    set_pixel_image(I, 6, 1, NOIR);
    set_pixel_image(I, 2, 2, NOIR);
    set_pixel_image(I, 3, 2, NOIR);
    set_pixel_image(I, 4, 2, NOIR);
    set_pixel_image(I, 6, 2, NOIR);
    set_pixel_image(I, 2, 3, NOIR);
    set_pixel_image(I, 6, 3, NOIR);
    set_pixel_image(I, 7, 3, NOIR);
    set_pixel_image(I, 2, 4, NOIR);
    set_pixel_image(I, 3, 4, NOIR);
    set_pixel_image(I, 4, 4, NOIR);
    set_pixel_image(I, 5, 4, NOIR);
    set_pixel_image(I, 6, 4, NOIR);
    set_pixel_image(I, 3, 5, NOIR);
    set_pixel_image(I, 4, 5, NOIR);
    set_pixel_image(I, 5, 5, NOIR);

    set_pixel_image(I, 1, 6, NOIR);
    set_pixel_image(I, 1, 7, NOIR);
    set_pixel_image(I, 2, 7, NOIR);
    set_pixel_image(I, 3, 7, NOIR);
    set_pixel_image(I, 1, 8, NOIR);
    set_pixel_image(I, 2, 8, NOIR);
    set_pixel_image(I, 3, 8, NOIR);
    set_pixel_image(I, 5, 8, NOIR);
    set_pixel_image(I, 6, 8, NOIR);
    set_pixel_image(I, 7, 8, NOIR);
    set_pixel_image(I, 2, 9, NOIR);
    set_pixel_image(I, 3, 9, NOIR);
    set_pixel_image(I, 4, 9, NOIR);
    set_pixel_image(I, 5, 9, NOIR);
    set_pixel_image(I, 6, 9, NOIR);
    set_pixel_image(I, 7, 9, NOIR);

    Robot R;
    int compte = 0;
    liste_contour *L = (liste_contour *)malloc(sizeof(liste_contour *));
    calcul_contour_mult(I, &R, L,&compte);
    //ecrire_contour(L->tete->C);
    ecrire_liste_contour((*L));
}