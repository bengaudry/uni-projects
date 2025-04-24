#include <stdio.h>
#include <stdlib.h>
#include "../simplification_contours.h"
#include "../postscript.h"

/* Arg1: fichier.pbm ; Arg2: fichier.eps ; Arg3: mode stroke ou fill ; Arg4: distance-seuil */
int main(int argc, char **argv){
    int nb_contours, nb_seg_init, nb_seg_simpl;
    Cellule_Liste_Liste_Point *Cel_init;
    Cellule_Liste_Liste_Bezier2 *Cel_simpl;

    if (argc != 5) 
        fprintf(stderr, "Utilisation: %s <chemin_fichier_image> <nom_fichier_sortie> <mode: 'fill' | 'stroke'> <d: distance-seuil>\n", argv[0]),
        exit(1);

    // Récupération de distance seuil
    char **endptr = NULL;
    double d = strtod(argv[4], endptr);

    Image I = lire_fichier_image(argv[1]);

    Liste_Contour LC = calcul_contours_multiples(I);
    Liste_Contour_Bezier2 LCB2 = simplification_bezier2(LC, d);

    sortie_format_postcript_bezier2(argv[2], LCB2, I, argv[3]);

    /* Statistiques des contours initiaux et simplifiés */
    nb_contours = LC.taille;
    nb_seg_init = 0;
    nb_seg_simpl = 0;

    Cel_init = LC.first;
    Cel_simpl = LCB2.first;
    while (Cel_init != NULL) {
        nb_seg_init += Cel_init->liste.taille-1;
        nb_seg_simpl += Cel_simpl->data.taille;
        Cel_init = Cel_init->suiv;
        Cel_simpl = Cel_simpl->suiv;
    }

    /* Affichage des stats */
    printf("\nNombre de contours: %d\n", nb_contours);
    printf("Nombre de segments initiaux: %d\n", nb_seg_init);
    printf("Nombre de courbes bezier2: %d\n\n", nb_seg_simpl);

    return 0;
}
