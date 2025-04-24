#ifndef _SIMPLIFICATION_CONTOURS_H
#define _SIMPLIFICATION_CONTOURS_H
#include "contour.h"

/* algorithme de douglas peucker pour la simplification par segments */
/* prend en argument un tableau de contours,
    premier indice, seconde indice, distance seuil */
Contour simplification_douglas_peucker(Tableau_Point C, int j1, int j2, double d);

Liste_Contour simplification_mult_contours(Liste_Contour LC, double d);

#endif
