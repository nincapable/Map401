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
        L->tete= L->last = el;
    }
    else{
        L->last->suivant = el;
        L->last = el;
        el->suivant = NULL;
    }
    L->taille++;
    //return L;
}

void calcul_contour_mult(Image I, Robot *R, liste_contour *L,int *compte){
    Contour *C=(Contour*)malloc(sizeof(Contour));
    Image M = masque(I, compte);

    while ((*compte) > 0)
    {
        position_initiale(M,R);
        contour_new(I,&M, R, C,compte);
        ajouter_element_liste_contour(L, (*C));
        printf("L->taille :%d\n", L->taille);
        // printf("%d\n", (*compte));
    }
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
    printf("temp->taille : %d\n", temp->taille);
    while (L.tete != NULL)
    {
        printf("i = %d\n", i);
        C = L.tete->C;
        printf("i = %d\n", i);
        ecrire_contour(C);
        printf("i = %d\n", i);
        L.tete = L.tete->suivant;
        L.taille--;
        i = i + 1;
        printf("i = %d\n", i);
        printf("L->taille : %d\n", L.taille);
    }
    //int Taille = Tableau.taille;
    
    // printf("nP=%u\n", nP);

    //printf("%d contours : [\n", Taille);
    /*for (k = 2; k < nP;k++){
        printf("\n");
        P = TP.tab[0];
        printf("contour:%d\n", k);
        ecrire_contour(P);
        //printf("(%f, %f)\n", P.x, P.y);
    }*/
    //C = Tableau.tab[0];
    //ecrire_contour(C);
    //Contour P = Tableau.tab[1];
    //ecrire_contour(P);
    //Contour P1 = Tableau.tab[1];
    //Contour P2 = Tableau.tab[2];
    //ecrire_contour(C);
    //ecrire_contour(TP.tab[1]);
    //ecrire_contour(P2);
    printf("cuicui les ptits zoizo\n");

    //free(Tableau.tab);
    printf("carottes\n");
}