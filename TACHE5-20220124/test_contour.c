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

    Robot R,R2;
    int compte = 0;
    int compte2 = 0;
    liste_contour *L = (liste_contour *)malloc(sizeof(liste_contour *));
    liste_contour *L2= (liste_contour *)malloc(sizeof(liste_contour *));
    Image Image = lire_fichier_image("image1_poly.pbm");
    //calcul_contour_mult(I, &R2, L2, &compte2);
    int calc=calcul_contour_mult(Image, &R, L, &compte);
    //printf("resultat seg=%d\n", calc);
    //printf("liste=%d\n", L->taille);
    //printf("taille c:%u\n", L->tete->C.taille);
    FILE *f = fopen("res", "w");
    
    ecrire_liste_contour_fichier(f, (*L));
    fclose(f);
    conversion_mult("image1_poly.eps", "image1_poly.pbm", 'f');
    printf("im1\n");
    conversion_mult("image2_poly.eps", "image2_poly.pbm", 'f');
    printf("im2\n");
    conversion_mult("animaux.eps", "animaux.pbm", 'f');
    printf("animaux\n");
    conversion_mult("Bugs_Bunny.eps", "Bugs_Bunny.pbm", 'f');
    printf("Bugs_Bunny\n");
    conversion_mult("Charlot.eps", "Charlot.pbm", 'f');
    printf("charlot\n");
    conversion_mult("chat.eps", "chat.pbm", 'f');
    printf("chat\n");
    conversion_mult("damier_4_5_1.eps", "damier_4_5_1.pbm", 'f');
    printf("damier\n");
    conversion_mult("dessin-delius.eps", "dessin-delius.pbm", 'f');
    printf("dessin\n");
    conversion_mult("deux-des.eps", "deux-des.pbm", 'f');
    printf("deux-des\n");
    conversion_mult("Droopy_Wolf.eps", "Droopy_Wolf.pbm", 'f');
    printf("droppy\n");
    conversion_mult("FranceRegions.eps", "FranceRegions.pbm", 'f');
    printf("FR\n");
    conversion_mult("gai-luron.eps", "gai-luron.pbm", 'f');
    printf("gai-luron\n");
    conversion_mult("papillon.eps", "papillon2.pbm", 'f');
    printf("papillon\n");
}