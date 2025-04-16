#include<stdio.h>  /* utilisation des entrees-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include "sequence_point.h"

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}
/* creer une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
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

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas où l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;

	if (points_egaux(L1.last->data, L2.first->data)) {
		L1.last->suiv = L2.first->suiv;
		L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
		L1.taille += L2.taille-1;
		return L1;
	} else {
		/* les deux listes sont non vides */
		L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
		L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
		L1.taille += L2.taille;   /* nouvelle taille pour L1 */
		return L1;
	}
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Point *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Point *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

unsigned int taille_liste_points(Liste_Point L) {
	return L.taille;
}

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Contour avec %d points\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* recuperer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}



////// SEQUENCES DE CONTOURS ///////

SequenceContours* initialiser_sequence_contours() {
	SequenceContours* seq;
	seq = malloc(sizeof(SequenceContours));
	seq->taille = 0;
	seq->first = NULL;
	seq->last = NULL;
	return seq;
}

/* Ajoute une cellule à la fin d'une séquence de contours */
void ajouter_cellule_seq_contours(SequenceContours* seq, Contour value) {
	CelluleSeqContours* cel_seq;

	if (seq == NULL) {
		fprintf(stderr, "Sequence non initialisée, arret.\n");
		exit(1);
	}

	cel_seq = malloc(sizeof(CelluleSeqContours));
	cel_seq->value = value;
	cel_seq->suiv = NULL;

	if (seq->first == NULL) {
		seq->first = cel_seq;
		seq->last = cel_seq;
		seq->taille = 1;
		return;
	}

	seq->last->suiv = cel_seq;
	seq->taille = seq->taille + 1;
	seq->last = cel_seq;
}
