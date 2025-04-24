#ifndef _SIMPLIFICATION_BEZIER_H
#define _SIMPLIFICATION_BEZIER_H

#include "geometrie.h"
#include "contour.h"
#include "bezier.h"


/* Calcul du point C(t) d'une Bezier de degré 2, 0<=t<=1 */
Point calcul_point_bezier2(Bezier2 B2, double t);

/* Calcul du point C(t) d'une Bezier de degré 3, 0<=t<=1 */
Point calcul_point_bezier3(Bezier3 B3, double t);

/* Conversion d'une Bézier de degré 2 en degré 3 */
Bezier3 bezier2_vers_bezier3(Bezier2 B2);

/* approximation d'une ligne polygonale par une
    courbe de bezier de degré 2 
    j2 - j1 >= 1                                */
Bezier2 approx_bezier2(Tableau_Point T, int j1, int j2);

/* simplification d'un contour polygonal en bezier de degré 2 */
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point T, int j1, int j2, double d);

/* simplification de tous les contours polygonals d'une image
    en bezier de degré 2 */
Liste_Contour_Bezier2 simplification_bezier2(Liste_Contour LC, double d);

/* calcul de gamma utilisé dans la fonction approx_bezier3 */
double gamma(double k, double n);

/* approximation d'une ligne polygonale par une
    courbe de bezier de degré 3
    j2 - j1 >= 1                                */
Bezier3 approx_bezier3(Tableau_Point T, int j1, int j2);

/* simplification d'un contour polygonal en bezier de degré 3 */
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point T, int j1, int j2, double d);

/* simplification de tous les contours polygonals d'une image
    en bezier de degré 3 */
Liste_Contour_Bezier3 simplification_bezier3(Liste_Contour LC, double d);

#endif
