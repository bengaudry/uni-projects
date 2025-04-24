#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "image.h"
#include "contour.h"
#include "postscript.h"
#include "simplification_bezier.h"
#include "simplification_contours.h"

int main (int argc, char **argv) {
    Image I;
    Liste_Contour seq_contours, seq_contours_simple;
    Liste_Contour_Bezier2 seq_contours_bezier2;
    Liste_Contour_Bezier3 seq_contours_bezier3;
    clock_t t_begin = 0, t_end = 0;
    
    if (argc != 2)
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm>\n", argv[0]),
        exit(1);

    // Mode par défaut : fill
    char mode[10] = "fill";

    // Lecture du fichier image en entrée, et génération des noms en sortie
    I = lire_fichier_image(argv[1]);
    char *nom_sortie = extraire_nom_fichier(argv[1]);
    char nom_sortie_simple[50];
    strcpy(nom_sortie_simple, nom_sortie);
    strcat(nom_sortie_simple, "_simple");
    strcat(nom_sortie, ".eps");
    strcat(nom_sortie_simple, ".eps");

    printf("Image : %s (%dx%d)\n", nom_sortie, largeur_image(I), hauteur_image(I));

    // Lecture de la séquence de contours
    seq_contours = creer_liste_liste_Point_vide();
    seq_contours = calcul_contours_multiples(I);

    // Affichage du menu de simplification
    printf("\n============ CHOIX DE LA SIMPLIFICATION ============\n");
    printf("(1) Simplification par segments\n");
    printf("(2) Simplification par courbes de Bézier de degré 2\n");
    printf("(3) Simplification par courbes de Bézier de degré 3\n");

    // Lecture du choix de l'utilisateur
    int choix = -1;
    do {
        printf("> ");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 3);

    // Lecture de la distance seuil choisie par l'utilisateur
    printf("Choisir une distance seuil :\n");
    double d = -1.0;
    do {
        printf("> ");
        scanf("%lf", &d);
    } while (d < 0);

    /* Comptage du nombre de segments initiaux */
    int nb_segments = 0;
    Cellule_Liste_Liste_Point* cel = seq_contours.first;
    while (cel != NULL) {
        nb_segments += cel->liste.taille-1;
        cel = cel->suiv;
    }

    switch (choix) {
        case 1:
            /* Choix du mode de remplissage : */
            printf("Choisir un mode de remplissage (stroke | fill) :\n");
            do {
                printf("> ");
                scanf("%9s", mode);
            } while (strcmp(mode, "fill") != 0 && strcmp(mode, "stroke") != 0);

            t_begin = clock();
            seq_contours_simple = simplification_mult_contours(seq_contours, d);
            t_end = clock();
            
            // Export au format eps
            sortie_format_postcript_mult_contours(nom_sortie, seq_contours, I, mode);               // export de l'image de base
            sortie_format_postcript_mult_contours(nom_sortie_simple, seq_contours_simple, I, mode); // export de l'image simplifiée

            /* Comptage des éléments */
            int nb_segments_simplifies = 0;
            Cellule_Liste_Liste_Point* cel_simpl = seq_contours_simple.first;
            while (cel_simpl != NULL) {
                nb_segments_simplifies += cel_simpl->liste.taille-1;
                cel_simpl = cel_simpl->suiv;
            }

            /* Affichage des stats */
            printf("\nNombre de contours            : %d\n", seq_contours.taille);
            printf("Nombre de segments initiaux   : %d\n", nb_segments);
            printf("Segments après simplification : %d\n", nb_segments_simplifies);
            printf("Taux de compression           : %d %%\n", nb_segments*100/nb_segments_simplifies);
            break;
        case 2:
            t_begin = clock();
            seq_contours_bezier2 = simplification_bezier2(seq_contours, d);
            t_end = clock();

            // Export au format eps
            sortie_format_postcript_mult_contours(nom_sortie, seq_contours, I, mode);          // export de l'image de base
            sortie_format_postcript_bezier2(nom_sortie_simple, seq_contours_bezier2, I, mode); // export de l'image simplifiée

            /* Comptage des éléments */
            int nb_courbes_b2_simplifies = 0;
            Cellule_Liste_Liste_Bezier2* cel_simpl_b2 = seq_contours_bezier2.first;
            while (cel_simpl_b2 != NULL) {
                nb_courbes_b2_simplifies += cel_simpl_b2->data.taille-1;
                cel_simpl_b2 = cel_simpl_b2->suiv;
            }

            /* Affichage des stats */
            printf("\nNombre de contours            : %d\n", seq_contours.taille);
            printf("Nombre de segments initiaux   : %d\n", nb_segments);
            printf("Nombre de courbes bezier2     : %d\n", nb_courbes_b2_simplifies);
            printf("Taux de compression           : %d %%\n", nb_segments*100/nb_courbes_b2_simplifies);
            break;
        case 3:
            t_begin = clock();
            seq_contours_bezier3 = simplification_bezier3(seq_contours, d);
            t_end = clock();

            // Export au format eps
            sortie_format_postcript_mult_contours(nom_sortie, seq_contours, I, mode);          // export de l'image de base
            sortie_format_postcript_bezier3(nom_sortie_simple, seq_contours_bezier3, I, mode); // export de l'image simplifiée

            /* Comptage des éléments */
            int nb_courbes_b3_simplifies = 0;
            Cellule_Liste_Liste_Bezier3* cel_simpl_b3 = seq_contours_bezier3.first;
            while (cel_simpl_b3 != NULL) {
                nb_courbes_b3_simplifies += cel_simpl_b3->data.taille-1;
                cel_simpl_b3 = cel_simpl_b3->suiv;
            }

            /* Affichage des stats */
            printf("\nNombre de contours            : %d\n", seq_contours.taille);
            printf("Nombre de segments initiaux   : %d\n", nb_segments);
            printf("Nombre de courbes bezier3     : %d\n", nb_courbes_b3_simplifies);
            printf("Taux de compression           : %d %%\n", nb_segments*100/nb_courbes_b3_simplifies);
            break;
        default: break; // n'arrive jamais
    }
    printf("Durée de la transformation    : %ldms \n", 1000*(t_end-t_begin)/CLOCKS_PER_SEC);
    
    return 0;
}
