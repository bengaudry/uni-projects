#ifndef _CONTOUR_H
#define _CONTOUR_H
#include "geometrie.h"
#include "image.h"

/* orientation du robot */
typedef enum {Nord, Est, Sud, Ouest} Orientation;

/* type robot : orientation + position */
typedef struct robot_ {
    Orientation orientation;
    Point position;
} Robot;

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type cellule de liste de liste de point  ----*/
typedef struct Cellule_Liste_Liste_Point_
{
   Liste_Point liste;
   struct Cellule_Liste_Liste_Point_ *suiv;
} Cellule_Liste_Liste_Point;

/*---- le type liste de liste de point ----*/
typedef struct Liste_Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Liste_Point;

typedef Liste_Liste_Point Liste_Contour; //type Liste_Contour = Liste de Liste de Points

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;

/* -------------------------------------- */
/*  Fonctions liees au calcul du contour  */
/* -------------------------------------- */

/* afficher orientation */
void afficher_orientation(Robot r);

/* trouver le premier point pour débuter le contour */
Point trouver_pixel_depart(Image I);

/* renvoi 0 si l'image est vide = composee de BLANC uniquement */
int image_est_vide(Image I);

/* avancer robot */
void avancer_robot(Robot *r, Image *M);

/* tourner robot à droite*/
void tourner_droite(Robot *r);

/* tourner robot à gauche */
void tourner_gauche(Robot *r);

/* calcul valeur pixel voisin gauche */
Pixel calcul_voisin_gauche(Image I, Robot r);

/* calcul valeur pixel voisin droite */
Pixel calcul_voisin_droite(Image I, Robot r);

/* calcul et changement de la nouvelle orientation du robot */
void calcul_nouvelle_orientation(Image I, Robot *r);

/* calcul du contour externe de l'image */
Contour calcul_contour_image(Image I);

/* crée et renvoie une image masque pour identifier les différents contours */
Image calcul_image_masque(Image I);

/* calcul d'un contour unitaire à l'aide de l'image masque */
Liste_Contour calcul_contours_multiples(Image I);

/* ---------------------------------------------- */
/*  Fonctions liees au stockage en liste chainees */
/* ---------------------------------------------- */

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

Cellule_Liste_Liste_Point *creer_element_liste_liste_Point(Liste_Point L);

/* creer une liste vide */
Liste_Point creer_liste_Point_vide();

Liste_Liste_Point creer_liste_liste_Point_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

Liste_Liste_Point ajouter_element_liste_liste_Point(Liste_Liste_Point L, Liste_Point e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

Liste_Liste_Point supprimer_liste_liste_Point(Liste_Liste_Point L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

Liste_Liste_Point concatener_liste_liste_Point(Liste_Liste_Point L1, Liste_Liste_Point L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

Liste_Liste_Point supprimer_premier_element_liste_liste_Point(Liste_Liste_Point L);

/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L);

void ecrire_liste_contour(Liste_Liste_Point L);

#endif
