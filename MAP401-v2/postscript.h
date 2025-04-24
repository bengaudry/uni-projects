#ifndef POSTSCRIPT_H
#define POSTSCRIPT_H

#include "contour.h"
#include "bezier.h"
#include "simplification_bezier.h"

/* Extrait le nom d'un fichier de son chemin */
char* extraire_nom_fichier(char* chemin_fichier);

/* crée un fichier postcript à partir d'un tableau de segments */
/* mode est un entier: 1 pour le contour; 2 pour le remplissage */
void sortie_format_postcript(char *nom_fichier, Tableau_Point T, Image I, char *mode);

/* crée un fichier postscript avec plusieurs contours à partir
   d'une liste de contours */
/* mode: "stroke" pour le contour; "fill" pour le remplissage */
void sortie_format_postcript_mult_contours(char *nom_fichier, Liste_Contour L, Image I, char *mode);

/* crée un fichier postscript avec plusieurs contours à partir
   d'une liste de liste de courbes BEZIER de DEGRE 2 */
/* mode: "stroke" pour le contour; "fill" pour le remplissage */
void sortie_format_postcript_bezier2(char *nom_fichier, Liste_Contour_Bezier2 LCB2, Image I, char *mode);

/* crée un fichier postscript avec plusieurs contours à partir
   d'une liste de liste de courbes BEZIER de DEGRE 3 */
/* mode: "stroke" pour le contour; "fill" pour le remplissage */
void sortie_format_postcript_bezier3(char *nom_fichier, Liste_Contour_Bezier3 LCB3, Image I, char *mode);

#endif
