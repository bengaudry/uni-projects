#include <stdlib.h>
#include <stdio.h>
#include "../contour.h"

int main(int argc, char **argv) {
    if (argc != 2) 
        fprintf(stderr, "Utilisation: %s <chemin_fichier_image>\n", argv[0]),
        exit(1);

    //Point pixel_depart;
    Image I = lire_fichier_image(argv[1]);

    //TEST calcul_contour_image
    ecrire_image(I);
    calcul_contour_image(I);    

    return 0;
}






