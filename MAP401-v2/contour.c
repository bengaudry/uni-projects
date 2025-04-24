#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "contour.h"

/* -------------------------------------- */
/*  Fonctions liees au calcul du contour  */
/* -------------------------------------- */

void afficher_orientation(Robot r) {
    switch (r.orientation) {
        case Nord: printf("Nord\n"); return;
        case Est: printf("Est\n"); return;
        case Sud: printf("Sud\n"); return;
        case Ouest: printf("Nord\n"); return;
    }
}

Point trouver_pixel_depart(Image I) {
    UINT largeur = largeur_image(I);
    UINT hauteur = hauteur_image(I);
    int x, y;
    Pixel pixel_actuel, pixel_nord;
    Point pixel_depart;

    for (y = 1; y <= hauteur; y++) {
        for (x =1; x <= largeur; x++) {
            pixel_actuel = get_pixel_image(I, x, y);
            pixel_nord = get_pixel_image(I, x, y-1);

            if (pixel_actuel == NOIR && pixel_nord == BLANC) {
                pixel_depart = set_point(x, y);
                return pixel_depart;
            }
        }
    }
    return set_point(-1, -1);
}

int image_est_vide(Image I) {
    UINT largeur = largeur_image(I);
    UINT hauteur = hauteur_image(I);
    int x, y;

    for (y = 1; y <= hauteur; y++) {
        for (x =1; x <= largeur; x++) {
            if (get_pixel_image(I, x, y) == NOIR) {
                return 1;
            }
        }
    }
    return 0; 
}

void avancer_robot(Robot *r, Image *M) {
    switch (r->orientation) {
        case Nord:
            r->position = set_point(r->position.x, r->position.y-1);
            break;
        case Sud:
            r->position = set_point(r->position.x, r->position.y+1);
            break;
        case Est:
            set_pixel_image(*M, r->position.x+1, r->position.y+1, BLANC);
            r->position = set_point(r->position.x+1, r->position.y);
            break;
        case Ouest:
            r->position = set_point(r->position.x-1, r->position.y);
            break;
        default:
            break;
    }
}

void tourner_droite(Robot *r) {
    switch (r->orientation) {
        case Nord:
            r->orientation = Est;
            break;
        case Est:
            r->orientation = Sud;
            break;
        case Sud:
            r->orientation = Ouest;
            break;
        case Ouest:
            r->orientation = Nord;
            break;
        default:
            break;
    }
}

void tourner_gauche(Robot *r) {
    switch (r->orientation) {
        case Nord:
            r->orientation = Ouest;
            break;
        case Ouest:
            r->orientation = Sud;
            break;
        case Sud:
            r->orientation = Est;
            break;
        case Est:
            r->orientation = Nord;
            break;
        default:
            break;
    }
}

Pixel calcul_voisin_gauche(Image I, Robot r) {
    switch (r.orientation) {
        case Nord: return get_pixel_image(I, r.position.x, r.position.y);
        case Sud: return get_pixel_image(I, r.position.x+1, r.position.y+1);
        case Est: return get_pixel_image(I, r.position.x+1, r.position.y);
        case Ouest: return get_pixel_image(I, r.position.x, r.position.y+1);
    }
}

Pixel calcul_voisin_droite(Image I, Robot r) {
    switch (r.orientation) {
        case Nord: return get_pixel_image(I, r.position.x+1, r.position.y);
        case Sud: return get_pixel_image(I, r.position.x, r.position.y+1);
        case Est: return get_pixel_image(I, r.position.x+1, r.position.y+1);
        case Ouest: return get_pixel_image(I, r.position.x, r.position.y);
    }
}

void calcul_nouvelle_orientation(Image I, Robot *r) {
    Pixel pG = calcul_voisin_gauche(I, *r);
    Pixel pD = calcul_voisin_droite(I, *r);

    if (pG == BLANC && pD == BLANC) tourner_droite(r);
    if (pG == BLANC && pD == NOIR) return;
    if (pG == NOIR && pD == NOIR) tourner_gauche(r);
    if (pG == NOIR && pD == BLANC) tourner_gauche(r);
    return;
}

Contour calcul_contour_image(Image I) {
    Robot r;
    bool boucle = true;
    Contour C = creer_liste_Point_vide();
    Point pixel_depart = trouver_pixel_depart(I);
    Point position_initiale = set_point(pixel_depart.x-1, pixel_depart.y-1);

    if (pixel_depart.x == -1 && pixel_depart.y == -1) {
        printf("Aucun contour");
        exit(0);
    }

    r.orientation = Est;
    r.position.x = position_initiale.x;
    r.position.y = position_initiale.y;

    while (boucle) {
        //memoriser position
        C = ajouter_element_liste_Point(C, set_point(r.position.x, r.position.y));

        //avancer_robot(&r);
        calcul_nouvelle_orientation(I, &r);

        if (r.orientation == Est && r.position.x == position_initiale.x && r.position.y == position_initiale.y) {
            boucle = false;
        }
    }
    C = ajouter_element_liste_Point(C, position_initiale);
    
    printf("C : ");
    ecrire_contour(C);

    return C;
}

Image calcul_image_masque(Image I) {
    UINT largeur = largeur_image(I);
    UINT hauteur = hauteur_image(I);
    int x, y;
    Pixel pixel_actuel, pixel_nord;
    Image M = creer_image(largeur, hauteur);

    for (y = 1; y <= hauteur; y++) {
        for (x =1; x <= largeur; x++) {
            pixel_actuel = get_pixel_image(I, x, y);
            pixel_nord = get_pixel_image(I, x, y-1);

            if (pixel_actuel == NOIR && pixel_nord == BLANC) {
                set_pixel_image(M, x, y, NOIR);
            }
        }
    }
    return M;
}

Liste_Contour calcul_contours_multiples(Image I) {
    UINT largeur = largeur_image(I);
    UINT hauteur = hauteur_image(I);
    int x,y,nb_contours;
    Image M = calcul_image_masque(I);
    Robot r;
    bool boucle;
    Contour C;
    Point position_initiale;
    Liste_Contour LC = creer_liste_liste_Point_vide();

    
    nb_contours = 0;

    for (y = 1; y <= hauteur; y++) {
        for (x =1; x <= largeur; x++) {
            if (get_pixel_image(M, x, y) == NOIR) {
                nb_contours++;
                boucle = true;
                C = creer_liste_Point_vide();
                position_initiale = set_point(x-1, y-1);

                r.orientation = Est;
                r.position.x = position_initiale.x;
                r.position.y = position_initiale.y;

                while (boucle) {
                    //memoriser position
                    double x = r.position.x;
                    double y = r.position.y;
            
                    C = ajouter_element_liste_Point(C, set_point(x, y));
            
                    avancer_robot(&r, &M);
                    calcul_nouvelle_orientation(I, &r);
            
                    if (r.orientation == Est && r.position.x == position_initiale.x && r.position.y == position_initiale.y) {
                        boucle = false;
                    }
                }
                C = ajouter_element_liste_Point(C, position_initiale);
                //ICI il faudra rajouter les instructions pour ajouter le contour à la liste de liste de contours
                LC = ajouter_element_liste_liste_Point(LC, C);
                //printf("C:");
                //ecrire_contour(C);
            }
        }
    }
    //printf("\nCONTOURS: %d\n", nb_contours);
    return LC;
}

/* ---------------------------------------------- */
/*  Fonctions liees au stockage en liste chainees */
/* ---------------------------------------------- */

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

Cellule_Liste_Liste_Point *creer_element_liste_liste_Point(Liste_Point L) {
    Cellule_Liste_Liste_Point *el;
	el = (Cellule_Liste_Liste_Point *)malloc(sizeof(Cellule_Liste_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste__liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->liste = L;
	el->suiv = NULL;
	return el;
}

Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

Liste_Liste_Point creer_liste_liste_Point_vide() {
    Liste_Liste_Point L = {0, NULL, NULL};
	return L;
}

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

Liste_Liste_Point ajouter_element_liste_liste_Point(Liste_Liste_Point L, Liste_Point e) {
    Cellule_Liste_Liste_Point *el;
	
	el = creer_element_liste_liste_Point(e);
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

Liste_Liste_Point supprimer_liste_liste_Point(Liste_Liste_Point L) {
    Cellule_Liste_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

Liste_Liste_Point concatener_liste_liste_Point(Liste_Liste_Point L1, Liste_Liste_Point L2){
    /* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

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

Liste_Liste_Point supprimer_premier_element_liste_liste_Point(Liste_Liste_Point L) {
    /* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Liste_Point *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Liste_Point *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}

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

void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Contour de %d points\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* recuperer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}

void ecrire_liste_contour(Liste_Liste_Point L) {
    Cellule_Liste_Liste_Point *cel = L.first;
    Liste_Point C;
    int nb = 0;

    while (cel != NULL) {
        C = cel->liste;
        nb++;
        printf("C%d: ", nb);
        ecrire_contour(C);
        cel = cel->suiv;
    }
    printf("\nCONTOURS: %d\n", nb);
}
