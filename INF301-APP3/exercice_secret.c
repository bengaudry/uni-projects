#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "arbresphylo.h"

int main() {
    arbre racine;
    FILE *f_arbre, *f_dest;
    liste_t carac_seq;

    init_liste_vide(&carac_seq);

    f_arbre = fopen("tests/recherche-AppoLab.test", "r+");

    racine = lire_arbre(f_arbre);
    if (rechercher_espece(racine, "AppoLab", &carac_seq) == 0) {
        //afficher_liste(&carac_seq);
    }

    show_messages(true);

    // EXERCICE 1 //
    connexion("im2ag-appolab.u-ga.fr");
    envoyer("login 12305101 GAUDRY");

    envoyer("unlock ents deracinez-moi");
    envoyer("load ents");

    f_arbre = fopen("tests/ents.test", "r+");
    f_dest = fopen("recherche-appolab.txt", "w");
    racine = lire_arbre(f_arbre);

    afficher_par_niveau(racine, f_dest);
    envoyer("start");
    envoyer("later enriched by Quenya and Sindarin");

    deconnexion();


    // EXERCICE 2 //
    // http://florent.bouchez.free.fr/protected/INF301/Phylogenetique/hero.php?name=BenRemi&gender=m&page=99999999
    connexion("im2ag-appolab.u-ga.fr");
    envoyer("login 12305101 GAUDRY");
    envoyer("load hero");
    envoyer("start");
    envoyer("Ben et Remi");
    envoyer("help");

    deconnexion();
    return 0;
}
