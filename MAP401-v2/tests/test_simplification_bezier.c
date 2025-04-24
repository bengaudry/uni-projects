#include <stdio.h>
#include "../simplification_bezier.h"
#include "../contour.h"
#include "../bezier.h"

int main() {
    Contour C;
    Tableau_Point T;
    Bezier2 B2;
    int n;

    printf("===== TEST A =====\n");
    C = creer_liste_Point_vide();
    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(-2, -2));

    T = sequence_points_liste_vers_tableau(C);
    B2 = approx_bezier2(T, 0, 1);
    supprimer_liste_Point(C);
    afficher_bezier2(B2);

   
    printf("===== TEST B - Bezier 2 =====\n");
    C = creer_liste_Point_vide();
    B2.c0 = set_point(0, 2);
    B2.c1 = set_point(0, 9);
    B2.c2 = set_point(2, 5);

    n = 4;
    C = ajouter_element_liste_Point(C, calcul_point_bezier2(B2, (double)0/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier2(B2, (double)1/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier2(B2, (double)2/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier2(B2, (double)3/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier2(B2, (double)4/n));

    T = sequence_points_liste_vers_tableau(C);

    printf("Courbe de bézier originale: \n");
    afficher_bezier2(B2);
    printf("Courbe de bézier approximative: \n");
    afficher_bezier2(approx_bezier2(T, 0, 4));

    supprimer_liste_Point(C);


    printf("===== TEST C =====\n");
    C = creer_liste_Point_vide();
    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 1));
    C = ajouter_element_liste_Point(C, set_point(1, 2));
    C = ajouter_element_liste_Point(C, set_point(2, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 3));
    C = ajouter_element_liste_Point(C, set_point(4, 3));
    C = ajouter_element_liste_Point(C, set_point(5, 3));

    T = sequence_points_liste_vers_tableau(C);
    B2 = approx_bezier2(T, 0, 8);
    supprimer_liste_Point(C);
    afficher_bezier2(B2);

    return 0;
}
