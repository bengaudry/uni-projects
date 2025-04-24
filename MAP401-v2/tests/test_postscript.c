#include <stdio.h>
#include <stdlib.h>
#include "../postscript.h"
#include "../contour.h"

/* Arg1: fichier.pbm ; Arg2: fichier.eps ; Arg3: mode stroke ou fill */
int main(int argc, char **argv){
    if (argc != 4) 
        fprintf(stderr, "Utilisation: %s <chemin_fichier_image> <nom_fichier_sortie> <mode: 'fill' | 'stroke'>\n", argv[0]),
        exit(1);

    Image I = lire_fichier_image(argv[1]);
    Liste_Contour L = calcul_contours_multiples(I);

    //ecrire_image(I);
    sortie_format_postcript_mult_contours(argv[2], L, I, argv[3]);
    ecrire_liste_contour(L);

    return 0;
}
