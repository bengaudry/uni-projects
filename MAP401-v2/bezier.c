#include <stdlib.h>
#include <stdio.h>
#include "bezier.h"

void afficher_bezier2(Bezier2 B2) {
    printf("Affichage Bezier 2:\n");
    affiche_point("C0", B2.c0);
    affiche_point("C1", B2.c1);
    affiche_point("C2", B2.c2);
    printf("\n");
}

void afficher_bezier3(Bezier3 B3) {
    printf("Affichage Bezier 3:\n");
    affiche_point("C0", B3.c0);
    affiche_point("C1", B3.c1);
    affiche_point("C2", B3.c2);
    affiche_point("C3", B3.c3);
    printf("\n");
}

/*---------------------------------------*/
/* FONCTIONS SUR LES LISTES DE BEZIERS 2 */
/*---------------------------------------*/

Cellule_Liste_Bezier2 *creer_element_liste_Bezier2(Bezier2 B2){
    Cellule_Liste_Bezier2 *el;
	el = (Cellule_Liste_Bezier2 *)malloc(sizeof(Cellule_Liste_Bezier2));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Bezier2 : allocation impossible\n");
		exit(-1);
	}
	el->data = B2;
	el->suiv = NULL;
	return el;
}

Liste_Bezier2 creer_liste_Bezier2_vide() {
    Liste_Bezier2 L = {0, NULL, NULL};
	return L;
}

Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 L, Bezier2 B2){
    Cellule_Liste_Bezier2 *el;
	
	el = creer_element_liste_Bezier2(B2);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

Liste_Bezier2 supprimer_liste_Bezier2(Liste_Bezier2 L){
    Cellule_Liste_Bezier2 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Bezier2 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 L1, Liste_Bezier2 L2){
    /* cas où l'une des deux listes est vide */
    if (L1.taille == 0) return L2; 
    if (L2.taille == 0) return L1;

    /* les deux listes sont non vides */
    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
    L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
    L1.taille += L2.taille;   /* nouvelle taille pour L1 */
    return L1;
}

void ecrire_contour_Bezier2(Liste_Bezier2 L){
    Cellule_Liste_Bezier2 *cel = L.first;
    Bezier2 B2;
    int nb = 0;

    while (cel != NULL) {
        B2 = cel->data;
        nb++;
        printf("B%d: ", nb);
        afficher_bezier2(B2);
        cel = cel->suiv;
    }
    printf("\nNombre de Bézier 2: %d\n", nb);
}

/*------------------------------------------------*/
/* FONCTIONS SUR LES LISTES DE LISTE DE BEZIERS 2 */
/*------------------------------------------------*/

Cellule_Liste_Liste_Bezier2 *creer_element_liste_liste_Bezier2(Liste_Bezier2 B2){
    Cellule_Liste_Liste_Bezier2 *el;
	el = (Cellule_Liste_Liste_Bezier2 *)malloc(sizeof(Cellule_Liste_Liste_Bezier2));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste__liste_Bezier2 : allocation impossible\n");
		exit(-1);
	}
	el->data = B2;
	el->suiv = NULL;
	return el;
}

Liste_Liste_Bezier2 creer_liste_liste_Bezier2_vide() {
    Liste_Liste_Bezier2 L = {0, NULL, NULL};
	return L;
}

Liste_Liste_Bezier2 ajouter_element_liste_liste_Bezier2(Liste_Liste_Bezier2 L, Liste_Bezier2 B2){
    Cellule_Liste_Liste_Bezier2 *el;
	
	el = creer_element_liste_liste_Bezier2(B2);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

Liste_Liste_Bezier2 supprimer_liste_liste_Bezier2(Liste_Liste_Bezier2 L) {
    Cellule_Liste_Liste_Bezier2 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Liste_Bezier2 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Liste_Bezier2 concatener_liste_liste_Bezier2(Liste_Liste_Bezier2 L1, Liste_Liste_Bezier2 L2){
    /* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

void ecrire_liste_contour_Bezier2(Liste_Liste_Bezier2 L){
    Cellule_Liste_Liste_Bezier2 *cel = L.first;
    Liste_Bezier2 C;
    int nb = 0;

    while (cel != NULL) {
        C = cel->data;
        nb++;
        printf("C%d: ", nb);
        ecrire_contour_Bezier2(C);
        cel = cel->suiv;
    }
    printf("\nCONTOURS: %d\n", nb);
}


/*---------------------------------------*/
/* FONCTIONS SUR LES LISTES DE BEZIERS 3 */
/*---------------------------------------*/

Cellule_Liste_Bezier3 *creer_element_liste_Bezier3(Bezier3 B3){
    Cellule_Liste_Bezier3 *el;
	el = (Cellule_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Bezier3));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Bezier3 : allocation impossible\n");
		exit(-1);
	}
	el->data = B3;
	el->suiv = NULL;
	return el;
}

Liste_Bezier3 creer_liste_Bezier3_vide() {
    Liste_Bezier3 L = {0, NULL, NULL};
	return L;
}

Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 L, Bezier3 B3){
    Cellule_Liste_Bezier3 *el;
	
	el = creer_element_liste_Bezier3(B3);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L){
    Cellule_Liste_Bezier3 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Bezier3 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2){
    /* cas où l'une des deux listes est vide */
    if (L1.taille == 0) return L2; 
    if (L2.taille == 0) return L1;

    /* les deux listes sont non vides */
    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
    L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
    L1.taille += L2.taille;   /* nouvelle taille pour L1 */
    return L1;
}

void ecrire_contour_Bezier3(Liste_Bezier3 L){
    Cellule_Liste_Bezier3 *cel = L.first;
    Bezier3 B3;
    int nb = 0;

    while (cel != NULL) {
        B3 = cel->data;
        nb++;
        printf("B%d: ", nb);
        afficher_bezier3(B3);
        cel = cel->suiv;
    }
    printf("\nNombre de Bézier 3: %d\n", nb);
}

/*------------------------------------------------*/
/* FONCTIONS SUR LES LISTES DE LISTE DE BEZIERS 3 */
/*------------------------------------------------*/


Cellule_Liste_Liste_Bezier3 *creer_element_liste_liste_Bezier3(Liste_Bezier3 B3){
    Cellule_Liste_Liste_Bezier3 *el;
	el = (Cellule_Liste_Liste_Bezier3 *)malloc(sizeof(Cellule_Liste_Liste_Bezier3));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste__liste_Bezier3 : allocation impossible\n");
		exit(-1);
	}
	el->data = B3;
	el->suiv = NULL;
	return el;
}

Liste_Liste_Bezier3 creer_liste_liste_Bezier3_vide() {
    Liste_Liste_Bezier3 L = {0, NULL, NULL};
	return L;
}

Liste_Liste_Bezier3 ajouter_element_liste_liste_Bezier3(Liste_Liste_Bezier3 L, Liste_Bezier3 B3){
    Cellule_Liste_Liste_Bezier3 *el;
	
	el = creer_element_liste_liste_Bezier3(B3);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

Liste_Liste_Bezier3 supprimer_liste_liste_Bezier3(Liste_Liste_Bezier3 L) {
    Cellule_Liste_Liste_Bezier3 *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Liste_Bezier3 *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Liste_Bezier3 concatener_liste_liste_Bezier3(Liste_Liste_Bezier3 L1, Liste_Liste_Bezier3 L2){
    /* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

void ecrire_liste_contour_Bezier3(Liste_Liste_Bezier3 L){
    Cellule_Liste_Liste_Bezier3 *cel = L.first;
    Liste_Bezier3 C;
    int nb = 0;

    while (cel != NULL) {
        C = cel->data;
        nb++;
        printf("C%d: ", nb);
        ecrire_contour_Bezier3(C);
        cel = cel->suiv;
    }
    printf("\nCONTOURS: %d\n", nb);
}
