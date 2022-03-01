#include <stdio.h>
#include "calcul_contour.h"

Coord voisin_pixel (Coord couple,Orientation O){
    Coord voisin;
    voisin.posx=couple.posx;
    voisin.posy = couple.posy;
    switch (O){
        case NW :
            voisin.posx --;
            voisin.posy --;
            return voisin;
       case N :
            voisin.posy --;
            return voisin;
        case NE :
            voisin.posx ++;
            voisin.posy --;
            return voisin;
        case W :
            voisin.posx --;
            return voisin;
        case E :
            voisin.posx ++;
            return voisin;
        case SW :
            voisin.posx --;
            voisin.posy ++;
            return voisin;
        case S :
            voisin.posy ++;
            return voisin;
        case SE :
            voisin.posx ++;
            voisin.posy ++;
            return voisin;
    }   
}

Point voisin_point (Point couple, Orientation O){
    Point voisin;
    voisin.x=couple.x;
    voisin.y = couple.y;
    switch (O){
        case N :
            voisin.y --;
            return voisin;
        case W :
            voisin.x --;
            return voisin;
        case E :
            voisin.x ++;
            return voisin;
        case S :
            voisin.y ++;
            return voisin;
        default:
            voisin.x = -1;
            voisin.y = -1;
            printf("error\n");
            return voisin;
        }
}

void position_initiale (Image I, Robot *R){
    double i = 1;
    double j = 1;
    Pixel p = get_pixel_image(I, i, j);
    int h = hauteur_image(I);
    int l = largeur_image(I);
    //char c;
    i = 1;
    while (p != NOIR && j <= h)
    {
        if (i > l)
        {
            i=1;
            //printf("pos i=%d\n",i);
            j++;
            //printf("pos j=%d\n", j);
        }
        i++;
        p = get_pixel_image(I,i, j);

    }
    if(j<h){
        R->x = i-1;
        R->y = j-1;
        R->O = E;
    }
    else{
        printf("erreur, Image blanche");
        R->x=-98;
        R->y = -98;
        R->O = E;
    }
}

void affichage_positions_rob(Robot R){
    printf("(%f,%f);", R.x, R.y);
}

void memoriser_position(Robot R, Contour *L){
    Point elt;
    elt.x=R.x;
    elt.y = R.y;
    //printf("ATTENTION:(%f,%f)\n", elt.x,elt.y);
    //printf("BONSOIR !\n");
    //printf("taille liste:%d\n", L->taille);
    (*L) = ajouter_element_liste_Point((*L), elt);
}

void memoriser_positionT1(Robot R,char *nom_fichier){
    FILE *f;
    f = fopen(nom_fichier, "w");
    fprintf(f, "%f;%f\n", R.x, R.y);
}

void avancer ( Robot *R){
    Point P;
    P.x = R->x;
    P.y = R->y;
    P=voisin_point(P, R->O);
    R->x=P.x;
    R->y = P.y;
    //printf("rob avance\n");
}

void print_orientation(Robot *R){
    switch (R->O) {
        case N:
            printf("Nord\n");
            break;
        case E:
            printf("Est\n");
            break;
        case S:
            printf("Sud\n");
            break;
        case W:
            printf("West\n");
            break;
        default :
            printf("Ta mère la muette !");
            break;
        }
}

void nouvelle_orientation(Image I,Robot *R){
    Pixel pG;
    Pixel pD;
    switch (R->O) {
        case N:
            pG = get_pixel_image(I, R->x, R->y);
            pD = get_pixel_image(I, R->x + 1, R->y);
            break;
        case E :
            pG = get_pixel_image(I,R->x + 1, R->y);
            pD = get_pixel_image(I, R->x + 1, R->y + 1);
            break;
        case S :
            pG = get_pixel_image(I, R->x + 1, R->y+1);
            pD = get_pixel_image(I, R->x, R->y+1);
            break;
        case W :
            pG = get_pixel_image(I, R->x, R->y + 1);
            pD = get_pixel_image(I, R->x, R->y);
            break;
    }
    if(pG==NOIR){
        tourner_gauche(R);
    }
    else if (pD==BLANC){
        tourner_droite(R);
    }
}

void tourner_droite(Robot *R){
    switch (R->O){
        case N:
            R->O = E;
            break;
        case E :
            R->O = S;
            break;
        case S :
            R->O = W;
            break;
        case W :
            R->O = N;
            break;
    }
    //printf("tourne droite\n");
}

void tourner_gauche(Robot *R){
    switch (R->O){
        case N:
            R->O = W;
            break;
        case W :
            R->O = S;
            break;
        case S :
            R->O = E;
            break;
        case E :
            R->O = N;
            break;
    }
    //printf("tourne gauche\n");
}

void contourT1(Image I,Robot *R,char *nom_fichier){
    position_initiale(I, R);
    //printf("position rob==%f;%f\n", R->x, R->y);
    int boucle = 1;
    
    Point position;
    position.x=R->x;
    position.y = R->y;
    while (boucle)
    {
        //printf("position rob=%f,%f\n", position.x, position.y);
        memoriser_positionT1(*R, nom_fichier);
        avancer(R);

        nouvelle_orientation(I, R);
        if(position.x==R->x && position.y==R->y && R->O==E){
            boucle = 0;
        }
    }
    memoriser_positionT1(*R, nom_fichier);
    
}

int contour(Image I,Robot *R, Contour *L){;
    position_initiale(I, R);
    //printf("position rob==%f;%f\n", R->x, R->y);
    int boucle = 1;
    Point position;
    int segment = 0;
    position.x=R->x;
    position.y = R->y;
    while (boucle)
    {
        //printf("position rob=%f,%f\n", position.x, position.y);
        memoriser_position(*R,L);
        //printf("%d\n", L->taille);
        avancer(R);
        segment++;
        nouvelle_orientation(I, R);
        if(position.x==R->x && position.y==R->y && R->O==E){
            boucle = 0;
        }
    }
    memoriser_position(*R,L);
    return segment;
}

Cellule_Liste_Point *creer_element_liste_Point(Point v){
    Cellule_Liste_Point *el;
    el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
    if ( el == NULL ){
        fprintf(stderr, "creer_element_liste_Point : allocation impossible \n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

Contour creer_liste_Point_vide(){
    Contour L = {0, NULL, NULL};
    return L;
}

Contour ajouter_element_liste_Point( Contour L, Point e){
    Cellule_Liste_Point *el;

    el = creer_element_liste_Point(e);
    if ( L.taille == 0 ){
        L.first = L.last = el;
    }
    else{
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

Contour supprimer_liste_Point( Contour L ){
    Cellule_Liste_Point *el = L.first;

    while( el ){
        Cellule_Liste_Point *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Contour concatener_liste_Point ( Contour L1, Contour L2 ){
    if ( L1.taille == 0 ) return L2;
    if ( L2.taille == 0 ) return L1;

    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

Tableau_Point sequence_points_liste_vers_tableau ( Contour L ){
    Tableau_Point T;

    T.taille = L.taille;

    T.tab = malloc(sizeof(Point) * T.taille);
    if (T.tab == NULL){
        fprintf(stderr, "sequence_points_liste_vers_tableau :");
        fprintf(stderr, "allocation impossible \n");
        exit(-1);
    }

    int k=0;
    Cellule_Liste_Point *el = L.first;
    while( el ){
        T.tab[k] = el->data ;
        k++;
        el = el->suiv;
    }
    return T;
}

void ecrire_contour( Contour L ){
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;

    printf("%d points : [\n", nP);
    for (k = 0; k < nP;k++){
        Point P = TP.tab[k];
        printf("(%f, %f)\n", P.x, P.y);
    }
    printf("]\n");

    free(TP.tab);
}

void ecrire_contour_fichier(Contour L,FILE *nom_fichier)
{
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;
    fprintf(nom_fichier, "%d points : [\n", nP);
    for (k = 0; k < nP;k++){
        Point P = TP.tab[k];
        fprintf(nom_fichier,"(%f, %f)\n", P.x, P.y);
    }
    fprintf(nom_fichier,"]\n");

    free(TP.tab);
}

void ecrire_info_fichier(Contour L,FILE *nom_fichier)
{
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;
    fprintf(nom_fichier, "%d points : [\n", nP);
    for (k = 0; k < nP;k++){
        Point P = TP.tab[k];
        //fprintf(f,"(%f, %f)\n", P.x, P.y);
    }
    //fprintf(f,"]\n");

    free(TP.tab);
}
