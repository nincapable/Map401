#include <stdio.h>
#include "calcul_contour_multiples.h" 


Image masque(Image I, int *compteur){
    double l = largeur_image(I);
    double h = hauteur_image(I);
    Image masque_I = creer_image(l, h);
    Coord current;
    Coord voisin;
    Pixel actuel;
    Pixel superieur;
    double vj;
    double vi;
    for (int j = 1; j <= h; j++)
    {
        for (int i = 1; i <= l; i++)
        {
            current.posx = i;
            current.posy = j;
            voisin = voisin_pixel(current, N);
            vi = voisin.posx;
            vj = voisin.posy;
            actuel = get_pixel_image(I, i, j);
            superieur = get_pixel_image(I, vi, vj);
            if ((actuel == NOIR) && (superieur==BLANC)){
                set_pixel_image(masque_I, i, j, NOIR);
                *compteur=*compteur+1;
            }
            else{
                set_pixel_image(masque_I, i, j, BLANC);
            }
        }
    }
    return masque_I;
}

void supprimer_pixel(Image I, Coord pixel, int* compteur){
    double posx=pixel.posx;
    double posy = pixel.posy;
    set_pixel_image(I,posx,posy,BLANC);
    (*compteur) = (*compteur) - 1;
}

int contour_new(Image I,Image *M,Robot *R, Contour *C,int *compte){;
    int boucle = 1;
    Point position;
    int segment = 0;
    Coord ixel ;
    position.x=R->x;
    position.y = R->y;
    while (boucle)
    {
        memoriser_position(*R,C);
        
        ixel.posx = R->x+1;
        ixel.posy = R->y+1;

        Pixel pix = get_pixel_image((*M), ixel.posx, ixel.posy);

        if ((R->O==E)&&(pix == NOIR))
        {
            supprimer_pixel((*M), ixel, compte);
        }
        avancer(R);
        segment++;
        nouvelle_orientation(I, R);
        if(position.x==R->x && position.y==R->y && R->O==E){
            boucle = 0;
        }
    }
    memoriser_position(*R,C);
    return segment;
}



cellule_contour *creer_element_liste_contour(Contour C){
    cellule_contour *el;
    el = (cellule_contour *)malloc(sizeof(cellule_contour));
    if ( el == NULL ){
        fprintf(stderr, "creer_element_liste_Point : allocation impossible \n");
        exit(-1);
    }
    el->C = C;
    el->suivant = NULL;
    return el;
}

void ajouter_element_liste_contour( liste_contour *L, Contour C){
    cellule_contour *el;
    el = creer_element_liste_contour(C);
    if ( L->taille == 0 ){
        L->tete = L->last = el;
    }
    else{
        L->last->suivant = el;
        L->last = el;
        el->suivant = NULL;
    }
    L->taille++;
    // return L;
}

int calcul_contour_mult(Image I, Robot *R, liste_contour *L,int *compte){
    int compteurf = 0;
    Image M = masque(I, compte);
    //printf("compteur masque=%d\n", (*compte));
    while ((*compte) > 0)
    {
        Contour *C=(Contour*)malloc(sizeof(Contour));
        C->taille = 0;
        position_initiale(M, R);
        int cont=contour_new(I, &M, R, C, compte);
        //printf("passe ton tour\n");
        ajouter_element_liste_contour(L, (*C));
        compteurf = compteurf + cont;
        // printf("L->taille :%d\n", L->taille);
        free(C);
        //ecrire_image(M);
        //printf("compteur:%d\n", (*compte));
        // printf("%d\n", (*compte));
    }
    //printf("L->taille :%d\n", L->taille);
    return compteurf;
}

/*tableau_contour sequence_contour_liste_vers_tableau(liste_contour L){
    tableau_contour T;
    T.taille = L.taille;
    T.tab = malloc(sizeof(Contour) * T.taille);
    if (T.tab == NULL){
        fprintf(stderr, "sequence_points_liste_vers_tableau :");
        fprintf(stderr, "allocation impossible \n");
        exit(-1);
    }
    int k=0;
    cellule_contour *el = L.tete;
    while( el ){
        T.tab[k] = el->C ;
        k++;
        el = el->suivant;
    }
    return T;
}*/

void ecrire_liste_contour( liste_contour L ){
    //tableau_contour Tableau = sequence_contour_liste_vers_tableau(L);
    int i = 0;
    Contour C;
    liste_contour *temp=(liste_contour*)malloc(sizeof(liste_contour));;
    temp->tete = L.tete;
    temp->taille = L.taille;
    //printf("temp->taille : %d\n", temp->taille);
    while (L.tete != NULL)
    {
        //printf("i = %d\n", i);
        C = L.tete->C;
        //printf("taille c%d:%u\n", i, L.tete->C.taille);
        //printf("i = %d\n", i);
        ecrire_contour(C);
        //printf("i = %d\n", i);
        L.tete = L.tete->suivant;
        L.taille--;
        i = i + 1;
        //printf("i = %d\n", i);
        //printf("L->taille : %d\n", L.taille);
    }
}

void ecrire_liste_contour_fichier( FILE *f, liste_contour L ){
    int i = 0;
    Contour C;
    liste_contour *temp=(liste_contour*)malloc(sizeof(liste_contour));
    temp->tete = L.tete;
    temp->taille = L.taille;
    fprintf(f,"%u\n\n",L.taille);
    while (L.tete != NULL)
    {
        C = L.tete->C;
        ecrire_contour_fichier(C,f);
        L.tete = L.tete->suivant;
        L.taille--;
        i = i + 1;
    }
}

void conversion_mult(char *nom_resultat, char *nom_image, char mode){
    FILE *f = fopen(nom_resultat, "w");
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    Image I = lire_fichier_image(nom_image);
    fprintf(f, "%%%%BoundingBox: 0 0 %u %u\n", I.L, I.H);
    fprintf(f, "/l {lineto} def\n");
    fprintf(f, "/m {moveto} def\n");
    fprintf(f, "/s {stroke} def\n");
    fprintf(f, "/f {fill} def\n");

    Robot R;
    int compte = 0;
    Contour C = creer_liste_Point_vide();
    //Contour *C;
    position_initiale(I, &R);
    liste_contour *L = (liste_contour *)malloc(sizeof(liste_contour*));
    L->taille = 0;
    int nb_seg = calcul_contour_mult(I, &R, L, &compte);
    int j = 0;
    liste_contour *temp = L;
    while (j < L->taille)
    {
        C = temp->tete->C;

        Tableau_Point T = sequence_points_liste_vers_tableau(C);
        int i = 0;
        fprintf(f, "%f %f m ", T.tab[i].x, I.H-T.tab[i].y);
        j++;
        while (i < T.taille)
        {
            double posx = T.tab[i].x;
            double posy = T.tab[i].y;
            fprintf(f, "%f %f l ", posx, I.H-posy);
            i++;
        }
        fprintf(f, "%f %f\n\n", T.tab[0].x, T.tab[0].y);
        temp->tete = temp->tete->suivant;
    }
    fprintf(f, "%f %f %c\n", L->last->C.first->data.x,L->last->C.first->data.y,mode);
    fprintf(f, "showpage");
}