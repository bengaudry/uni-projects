#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "sequence_point.h"
#include "geometrie.h"
#include "image.h"
#include "contour.h"


/* Renvoie les coordonnées du point correspondant au premier pixel noir de l'image */
Point trouver_premier_point(Image I) {
    int x, y;
    int H, L;
    Pixel pixel_courant, pixel_nord;

    H = hauteur_image(I);
    L = largeur_image(I);

    for (y = 1; y <= H; y++) {
        for (x = 1; x <= L; x++) {
            pixel_courant = get_pixel_image(I, x, y);
            pixel_nord = get_pixel_image(I, x, y-1);

            if (pixel_courant == NOIR && pixel_nord == BLANC) {
                return set_point(x-1, y-1);
            }
        }
    }

    return set_point(-1, -1); // Ne devrait pas arriver
}

/* Renvoie un tableau de dimensions egales à celles de l'image,
 * qui contient NOIR si le pixel est candidat, BLANC sinon
*/
Image pixels_candidats(Image I) {
    int x, y;
    int H, L;
    Pixel pixel_courant, pixel_nord;
    Image Masque;


    H = hauteur_image(I);
    L = largeur_image(I);

    Masque = creer_image(L, H);

    for (y = 1; y <= H; y++) {
        for (x = 1; x <= L; x++) {
            pixel_courant = get_pixel_image(I, x, y);
            pixel_nord = get_pixel_image(I, x, y-1);

            set_pixel_image(Masque, x, y, (pixel_courant == NOIR && pixel_nord == BLANC) ? NOIR : BLANC);
        }
    }
    
    return Masque;
}

Orientation tourner_a_gauche(Orientation O) {
    switch (O) {
        case Ouest: return Sud;
        case Sud: return Est;
        case Est: return Nord;
        case Nord: return Ouest;
    }
}

Orientation tourner_a_droite(Orientation O) {
    switch (O) {
        case Nord: return Est;
        case Est: return Sud;
        case Sud: return Ouest;
        case Ouest: return Nord;
    }
}

Point calculer_nouvelle_position_robot(Point P, Orientation or_robot) {
    switch (or_robot) {
        case Est: return set_point(P.x+1, P.y);
        case Sud: return set_point(P.x, P.y+1);
        case Ouest: return set_point(P.x-1, P.y);
        case Nord: return set_point(P.x, P.y-1);
    }
}

Pixel pixel_gauche(Image I, Point P, Orientation O) {
    switch (O) {
        case Nord: return get_pixel_image(I, P.x, P.y);
        case Est: return get_pixel_image(I, P.x+1, P.y);
        case Sud: return get_pixel_image(I, P.x+1, P.y+1);
        case Ouest: return get_pixel_image(I, P.x, P.y+1);
    }
}

Pixel pixel_droit(Image I, Point P, Orientation O) {
    switch (O) {
        case Nord: return get_pixel_image(I, P.x+1, P.y);
        case Est: return get_pixel_image(I, P.x+1, P.y+1);
        case Sud: return get_pixel_image(I, P.x, P.y+1);
        case Ouest: return get_pixel_image(I, P.x, P.y);
    }
}

/* Parcours de contours multiples */
void parcourir_contours(Image I, SequenceContours *seq_contours) {
    Orientation or_robot;
    Point pos_robot, pos_initial_robot;
    Contour contour;
    Image Masque;

    Masque = pixels_candidats(I);

    for (int y = 1; y <= hauteur_image(I); y++) {
        for (int x = 1; x <= largeur_image(I); x++) {
            // Si le pixel est candidat
            if (get_pixel_image(Masque, x, y) == NOIR) {
                contour = creer_liste_Point_vide();
                or_robot = Est;
                pos_initial_robot = set_point(x-1, y-1);
                pos_robot = pos_initial_robot;

                do {
                    contour = ajouter_element_liste_Point(contour, set_point(pos_robot.x, pos_robot.y));
                    pos_robot = calculer_nouvelle_position_robot(pos_robot, or_robot); // On avance le robot de 1
                
                    if (pixel_gauche(I, pos_robot, or_robot) == NOIR) or_robot = tourner_a_gauche(or_robot);
                    else if (pixel_droit(I, pos_robot, or_robot) == BLANC) or_robot = tourner_a_droite(or_robot);

                    // Supprimer le pixel candidat correspondant si le robot regarde vers l'Est
                    if (or_robot == Est) {
                        set_pixel_image(Masque, (int)pos_robot.x+1, (int)pos_robot.y+1, BLANC);
                    }
                } while (!points_egaux(pos_robot, pos_initial_robot) || or_robot != Est);
                
                contour = ajouter_element_liste_Point(contour, pos_robot);
                ajouter_cellule_seq_contours(seq_contours, contour);
            }
        }
    }
}

Contour parcourir_contour(Image I, Point pos_initial_robot) {
    Orientation or_robot;
    Point pos_robot;
    Contour contour;

    contour = creer_liste_Point_vide();

    or_robot = Est;

    if (pos_initial_robot.x == -1 && pos_initial_robot.y == -1) {
        fprintf(stderr, "Pas de contour a détecter\n");
        exit(1);
    };

    pos_robot = pos_initial_robot;
    do {
        contour = ajouter_element_liste_Point(contour, pos_robot);
        pos_robot = calculer_nouvelle_position_robot(pos_robot, or_robot); // On avance le robot de 1
    
        if (pixel_gauche(I, pos_robot, or_robot) == NOIR) or_robot = tourner_a_gauche(or_robot);
        else if (pixel_droit(I, pos_robot, or_robot) == BLANC) or_robot = tourner_a_droite(or_robot);
    } while (!points_egaux(pos_robot, pos_initial_robot) || or_robot != Est);
    
    contour = ajouter_element_liste_Point(contour, pos_robot);
    return contour;
}
