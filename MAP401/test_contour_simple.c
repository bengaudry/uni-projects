#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "contour.h"
#include "eps.h"
#include "sequence_point.h"

int main (int argc, char **argv) {
    Image I;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm> <mode: 'fill' | 'stroke' | null>\n", argv[0]);
        exit(1);
    }

    I = lire_fichier_image(argv[1]);

    printf("Largeur : %d\n", largeur_image(I));
    printf("Hauteur : %d\n", hauteur_image(I));
    
    Contour c = parcourir_contour(I, trouver_premier_point(I));
    ecrire_contour(c);

    // On convertit notre contour en "séquence de contours" avec un seul élément
    // ce qui évite l'utilisation de deux fonctions différentes
    SequenceContours * seq_contours = initialiser_sequence_contours();
    ajouter_cellule_seq_contours(seq_contours, c);
    exporter_image_eps(I, seq_contours, extraire_nom_fichier(argv[1]), argv[2] == NULL ? "fill" : argv[2]);

    printf("Nombre de segments : %d\n", taille_liste_points(c)-1);

    return 0;
}
