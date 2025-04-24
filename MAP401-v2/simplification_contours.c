#include <stdio.h>
#include <stdlib.h>
#include "simplification_contours.h"

Contour simplification_douglas_peucker(Tableau_Point C, int j1, int j2, double d) {
    double dmax, dj;
    int k, j;
    Segment S;
    Liste_Point L, L1, L2;
    
    L = creer_liste_Point_vide();
    S = set_segment(C.tab[j1], C.tab[j2]);
    dmax = 0;
    k = j1;
    for (j = j1+1; j <= j2; j++) {
        dj = distance_segment_point(C.tab[j], S);
        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d) {
       L = ajouter_element_liste_Point(L, S.A);
       //L = ajouter_element_liste_Point(L, S.B);
    }
    else {
        L1 = creer_liste_Point_vide();
        L2 = creer_liste_Point_vide();

        L1 = simplification_douglas_peucker(C, j1, k, d);
        L2 = simplification_douglas_peucker(C, k, j2, d);
        
        L = concatener_liste_Point(L1, L2);
    }
    return L;
}

Liste_Contour simplification_mult_contours(Liste_Contour LC, double d) {
    Tableau_Point T;
    Liste_Point C_simpl;
    Point point_init;
    Cellule_Liste_Liste_Point *C;
    Liste_Contour LCM = creer_liste_liste_Point_vide();
    
    C = LC.first;
    while(C != NULL) {
        T = sequence_points_liste_vers_tableau(C->liste);
        C_simpl = simplification_douglas_peucker(T, 0, T.taille-1, d);
        point_init = C->liste.first->data;
        C_simpl = ajouter_element_liste_Point(C_simpl, point_init);
        //ecrire_contour(C->liste);
        //ecrire_contour(C_simpl);
        LCM = ajouter_element_liste_liste_Point(LCM, C_simpl);
        C = C->suiv;
    }

    return LCM;
}
