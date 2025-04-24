#ifndef _BEZIER_H
#define _BEZIER_H

#include "geometrie.h"

/*  Type Bezier2: les 3 points de contrôle   */
/*    d'une courbe de bézier de degré 2     */
typedef struct {
    Point c0, c1, c2;
} Bezier2;

/*  Type Bezier3: les 4 points de contrôle   */
/*    d'une courbe de bézier de degré 3    */
typedef struct {
    Point c0, c1, c2, c3;
} Bezier3;

/*-----------------------------------------------*/
/* Definition du type Liste de Bezier 2 */
/*-----------------------------------------------*/

/*---- le type cellule de liste de Bezier2 ----*/
typedef struct Cellule_Liste_Bezier2_
{
	Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier2_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier2;

/*---- le type liste de Bezier2 ----*/
typedef struct Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier2 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier2 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier2;

typedef Liste_Bezier2 Contour_Bezier2; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Bezier2_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier2 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier2;

/*-----------------------------------------------*/
/* Definition du type Liste de Liste de Bezier 2 */
/*-----------------------------------------------*/

/*---- le type cellule de liste de liste de Bezier2 ----*/
typedef struct Cellule_Liste_Liste_Bezier2_
{
	Liste_Bezier2 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Liste_Bezier2_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Liste_Bezier2;

/*---- le type liste de Liste de Bezier2 ----*/
typedef struct Liste_Liste_Bezier2_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Liste_Bezier2 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Liste_Bezier2 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Liste_Bezier2;

typedef Liste_Liste_Bezier2 Liste_Contour_Bezier2; /* type Contour = type Liste_Point */

/*-----------------------------------------------*/
/* Definition du type Liste de Bezier 3 */
/*-----------------------------------------------*/

/*---- le type cellule de liste de Bezier3 ----*/
typedef struct Cellule_Liste_Bezier3_
{
	Bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Bezier3_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Bezier3;

/*---- le type liste de Bezier3 ----*/
typedef struct Liste_Bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Bezier3 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Bezier3 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Bezier3;

typedef Liste_Bezier3 Contour_Bezier3; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Bezier3_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Bezier3 *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Bezier3;

/*-----------------------------------------------*/
/* Definition du type Liste de Liste de Bezier 3 */
/*-----------------------------------------------*/

/*---- le type cellule de liste de liste de Bezier3 ----*/
typedef struct Cellule_Liste_Liste_Bezier3_
{
	Liste_Bezier3 data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Liste_Bezier3_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Liste_Bezier3;

/*---- le type liste de Liste de Bezier3 ----*/
typedef struct Liste_Liste_Bezier3_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Liste_Bezier3 *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Liste_Bezier3 *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Liste_Bezier3;

typedef Liste_Liste_Bezier3 Liste_Contour_Bezier3; /* type Contour = type Liste_Point */

/* FONCTIONS d'AFFICHAGE */

/* affichage d'une Bezier 2 */
void afficher_bezier2(Bezier2 B2);

/* affichage d'une Bezier 3 */
void afficher_bezier3(Bezier3 B3);

/*---------------------------------------*/
/* FONCTIONS SUR LES LISTES DE BEZIERS 2 */
/*---------------------------------------*/

/* creer une cellule de liste avec l'element B2 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 B2);

/* creer une liste vide */
Liste_Bezier2 creer_liste_Bezier2_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 B2);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Bezier2 supprimer_liste_Bezier2(Liste_Bezier2 L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2);

/* ecrire le contour L a l'ecran */
void ecrire_contour_Bezier2(Liste_Bezier2 L);

/*------------------------------------------------*/
/* FONCTIONS SUR LES LISTES DE LISTE DE BEZIERS 2 */
/*------------------------------------------------*/

/* creer une cellule de liste avec l'element B2 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Liste_Bezier2 *creer_element_liste_liste_Bezier2(Liste_Bezier2 B2);

/* creer une liste vide */
Liste_Liste_Bezier2 creer_liste_liste_Bezier2_vide();

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Liste_Bezier2 ajouter_element_liste_liste_Bezier2(Liste_Liste_Bezier2 L, Liste_Bezier2 B2);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Liste_Bezier2 supprimer_liste_liste_Bezier2(Liste_Liste_Bezier2 L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Liste_Bezier2 concatener_liste_liste_Bezier2(Liste_Liste_Bezier2 L1, Liste_Liste_Bezier2 L2);

/* ecrire le contour L a l'ecran */
void ecrire_liste_contour_Bezier2(Liste_Liste_Bezier2 L);

/*---------------------------------------*/
/* FONCTIONS SUR LES LISTES DE BEZIERS 3 */
/*---------------------------------------*/

/* creer une cellule de liste avec l'element B3 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
   Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 B3);

   /* creer une liste vide */
   Liste_Bezier3 creer_liste_Bezier3_vide();
   
   /* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
   Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 L, Bezier3 B3);
   
   /* supprimer tous les elements de la liste, renvoie la liste L vide */
   Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L);
   
   /* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
   Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2);
   
   /* ecrire le contour L a l'ecran */
   void ecrire_contour_Bezier3(Liste_Bezier3 L);
   
   /*------------------------------------------------*/
   /* FONCTIONS SUR LES LISTES DE LISTE DE BEZIERS 3 */
   /*------------------------------------------------*/
   
   /* creer une cellule de liste avec l'element B3 
	  renvoie le pointeur sur la cellule de liste creee
	  la fonction s'arrete si la creation n'a pas pu se faire */
   Cellule_Liste_Liste_Bezier3 *creer_element_liste_liste_Bezier3(Liste_Bezier3 B3);
   
   /* creer une liste vide */
   Liste_Liste_Bezier3 creer_liste_liste_Bezier3_vide();
   
   /* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
   Liste_Liste_Bezier3 ajouter_element_liste_liste_Bezier3(Liste_Liste_Bezier3 L, Liste_Bezier3 B3);
   
   /* supprimer tous les elements de la liste, renvoie la liste L vide */
   Liste_Liste_Bezier3 supprimer_liste_liste_Bezier3(Liste_Liste_Bezier3 L);
   
   /* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
   Liste_Liste_Bezier3 concatener_liste_liste_Bezier3(Liste_Liste_Bezier3 L1, Liste_Liste_Bezier3 L2);
   
   /* ecrire le contour L a l'ecran */
   void ecrire_liste_contour_Bezier3(Liste_Liste_Bezier3 L);

#endif
