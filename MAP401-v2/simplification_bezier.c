#include <stdlib.h>
#include <stdio.h>
#include "simplification_bezier.h"
#include "bezier.h"

Point calcul_point_bezier2(Bezier2 B2, double t) {
    Point a,b,c;

    a = mult_point_scalaire(B2.c0, (1-t)*(1-t));
    b = mult_point_scalaire(B2.c1, (2*(1-t)*t));
    c = mult_point_scalaire(B2.c2, (t*t));
 
    return somme_points(a, somme_points(b, c));
}

Point calcul_point_bezier3(Bezier3 B3, double t) {
    Point a,b,c,d;

    a = mult_point_scalaire(B3.c0, (1-t)*(1-t)*(1-t));
    b = mult_point_scalaire(B3.c1, (3*(1-t)*(1-t)*t));
    c = mult_point_scalaire(B3.c2, (3*(1-t)*t*t));
    d = mult_point_scalaire(B3.c3, (t*t*t));
 
    return somme_points(a, somme_points(b, somme_points(c, d)));
}

Bezier3 bezier2_vers_bezier3(Bezier2 B2) {
    Bezier3 B3;

    B3.c0 = B2.c0;
    B3.c1 = mult_point_scalaire(somme_points(B2.c0, mult_point_scalaire(B2.c1, 2.0)), (double)1/3);
    B3.c2 = mult_point_scalaire(somme_points(B2.c2, mult_point_scalaire(B2.c1, 2.0)), (double)1/3);
    B3.c3 = B2.c2;   

    return B3;
}

Bezier2 approx_bezier2(Tableau_Point T, int j1, int j2) {
    Bezier2 B2;
    Point Pj1, Pj2, C1, Psomme;
    double n = (double)(j2 -j1);
    double a, b;

    Pj1 = T.tab[j1];
    Pj2 = T.tab[j2];
    B2.c0 = Pj1;
    B2.c2 = Pj2;

    if (n==1) { 
        B2.c1 = mult_point_scalaire(somme_points(Pj1, Pj2), (double)1/2);
        return B2;
    }

    //cas où n >= 2
    a = (3*n)/(n*n - 1);
    b= (1 - 2*n)/(2*n + 2);
    Psomme = set_point(0, 0);

    for (int i=1; i<n; i++) {
        Psomme = somme_points(Psomme, T.tab[j1 + i]);
    }

    C1 = somme_points(mult_point_scalaire(Psomme, a), mult_point_scalaire(somme_points(Pj1, Pj2), b));
    B2.c1 = C1;

    return B2;
}

Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point T, int j1, int j2, double d){
    Bezier2 B2;
    Liste_Bezier2 L, L1, L2;
    double n, dmax, ti, dj;
    int i, j, k;


    n = (double)(j2-j1);
    dmax = 0;
    k = j1;
    B2 = approx_bezier2(T, j1, j2);

    for (j = j1+1; j <= j2; j++) {

        i = j - j1;
        ti = (double)(i)/n;
        dj = distance_points(T.tab[j], calcul_point_bezier2(B2, ti));

        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    L = creer_liste_Bezier2_vide();
    if (dmax <= d) {
        L = ajouter_element_liste_Bezier2(L, B2);
    }
    else {
        L1 = simplification_douglas_peucker_bezier2(T, j1, k, d);
        L2 = simplification_douglas_peucker_bezier2(T, k, j2, d);

        L = concatener_liste_Bezier2(L1, L2);
    }
    return L;
}

Liste_Contour_Bezier2 simplification_bezier2(Liste_Contour LC, double d){
    Cellule_Liste_Liste_Point *cel;
    Contour C;
    Tableau_Point T;
    Liste_Bezier2 Liste_B2;
    Liste_Contour_Bezier2 LC_B2; 
    
    LC_B2 = creer_liste_liste_Bezier2_vide();
    cel = LC.first;

    for (int i = 0; i < LC.taille; i++) {
        C = cel->liste;
        T = sequence_points_liste_vers_tableau(C);
        Liste_B2 = simplification_douglas_peucker_bezier2(T, 0, T.taille-1, d);
        LC_B2 = ajouter_element_liste_liste_Bezier2(LC_B2, Liste_B2);
        cel = cel->suiv;
    }
    return LC_B2;
}

double gamma(double k, double n){
    return (6*k*k*k*k - 8*n*k*k*k + 6*k*k - 4*n*k + n*n*n*n - n*n);
}

Bezier3 approx_bezier3(Tableau_Point T, int j1, int j2) {
    Bezier3 B3;
    Point Pj1, Pj2, C1somme, C2somme;
    double n = (double)(j2 -j1);
    double a, b, l;

    if (n < 3) {
        B3 = bezier2_vers_bezier3(approx_bezier2(T, j1, j2));
        return B3;
    }

    //cas où n >= 3
    a = (-15*n*n*n + 5*n*n + 2*n + 4)/(3*(n+2)*(3*n*n + 1));
    b = (10*n*n*n - 15*n*n + n + 2)/(3*(n+2)*(3*n*n + 1));
    l = (70*n)/(3*(n*n - 1)*(n*n - 4)*(3*n*n + 1));

    Pj1 = T.tab[j1];
    Pj2 = T.tab[j2];
    B3.c0 = Pj1;
    B3.c3 = Pj2;

    C1somme = set_point(0, 0);
    C2somme = set_point(0, 0);

    for (int i=1; i < n; i++) {
        C1somme = somme_points(C1somme, mult_point_scalaire(T.tab[j1 + i], gamma((double)i, n)));
        C2somme = somme_points(C2somme, mult_point_scalaire(T.tab[j1 + i], gamma(n-(double)i, n)));
    }

    B3.c1 = somme_points(mult_point_scalaire(Pj1, a), somme_points(mult_point_scalaire(C1somme, l), mult_point_scalaire(Pj2, b)));
    B3.c2 = somme_points(mult_point_scalaire(Pj1, b), somme_points(mult_point_scalaire(C2somme, l), mult_point_scalaire(Pj2, a)));

    return B3;
}


Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point T, int j1, int j2, double d){
    Bezier3 B3;
    Liste_Bezier3 L, L1, L2;
    double n, dmax, ti, dj;
    int i, j, k;


    n = (double)(j2-j1);
    dmax = 0;
    k = j1;
    B3 = approx_bezier3(T, j1, j2);

    for (j = j1+1; j <= j2; j++) {

        i = j - j1;
        ti = (double)(i)/n;
        dj = distance_points(T.tab[j], calcul_point_bezier3(B3, ti));

        if (dmax < dj) {
            dmax = dj;
            k = j;
        }
    }

    L = creer_liste_Bezier3_vide();
    if (dmax <= d) {
        L = ajouter_element_liste_Bezier3(L, B3);
    }
    else {
        L1 = simplification_douglas_peucker_bezier3(T, j1, k, d);
        L2 = simplification_douglas_peucker_bezier3(T, k, j2, d);

        L = concatener_liste_Bezier3(L1, L2);
    }
    return L;
}

Liste_Contour_Bezier3 simplification_bezier3(Liste_Contour LC, double d){
    Cellule_Liste_Liste_Point *cel;
    Contour C;
    Tableau_Point T;
    Liste_Bezier3 Liste_B3;
    Liste_Contour_Bezier3 LC_B3; 
    
    LC_B3 = creer_liste_liste_Bezier3_vide();
    cel = LC.first;

    for (int i = 0; i < LC.taille; i++) {
        C = cel->liste;
        T = sequence_points_liste_vers_tableau(C);
        Liste_B3 = simplification_douglas_peucker_bezier3(T, 0, T.taille-1, d);
        LC_B3 = ajouter_element_liste_liste_Bezier3(LC_B3, Liste_B3);
        cel = cel->suiv;
    }
    return LC_B3;
}
