#include <stdio.h>
#include <stdlib.h>
#include "../contour.h"
#include "../simplification_contours.h"
#include "../postscript.h"

/* Arg1: fichier.pbm ; Arg2: fichier.eps ; Arg3: mode stroke ou fill ; Arg4: distance-seuil */
int main(int argc, char **argv) {
    if (argc != 5) 
        fprintf(stderr, "Utilisation: %s <chemin_fichier_image> <nom_fichier_sortie> <mode: 'fill' | 'stroke'> <d: distance-seuil>\n", argv[0]),
        exit(1);

    int nb_contours, nb_seg_init, nb_seg_simpl;
    Cellule_Liste_Liste_Point *Cel_init, *Cel_simpl;

    // Récupération de distance seuil
    char **endptr = NULL;
    double d = strtod(argv[4], endptr);
    
    Image I = lire_fichier_image(argv[1]);

    //liste de contours avant simplification
    Liste_Contour LC = calcul_contours_multiples(I);
    //liste de contours après siplification
    Liste_Contour L =  simplification_mult_contours(LC, d);

    /* Statistiques des contours initiaux et simplifiés */
    nb_contours = LC.taille;
    nb_seg_init = 0;
    nb_seg_simpl = 0;

    Cel_init = LC.first;
    Cel_simpl = L.first;
    while (Cel_init != NULL) {
        nb_seg_init += Cel_init->liste.taille-1;
        nb_seg_simpl += Cel_simpl->liste.taille-1;
        Cel_init = Cel_init->suiv;
        Cel_simpl = Cel_simpl->suiv;
    }

    /* Affichage des stats */
    printf("\nNombre de contours: %d\n", nb_contours);
    printf("Nombre de segments initiaux: %d\n", nb_seg_init);
    printf("Nombre de segments simplifiés: %d\n\n", nb_seg_simpl);
    
    //ecrire_image(I);
    sortie_format_postcript_mult_contours(argv[2], L, I, argv[3]);


    return 0;
}
