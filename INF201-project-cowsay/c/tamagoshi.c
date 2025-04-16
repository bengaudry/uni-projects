#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define byebyelife 0
#define lifesucks 1
#define liferocks 2

typedef int etat;

void update() {
    printf("\033[H\033[J") ;
}

etat etat_initial() {
    return liferocks;
}

int est_final(etat Q) {
    return Q == byebyelife;
}

//affichage de la vache en fonction de l'etat
void afficher_vache(etat Q) {
    switch (Q) {
        case byebyelife :
            printf("              ^__^\n\
              (xx)\\ _______\n\
              (_p)\\         )\\/\\\n\
               / || - ~ ~ -w |\n\
                 /x         */\n");
            return;
        case lifesucks :
            printf("              ^__^\n\
              (oo)\\ _______\n\
              (~~)\\         )\\/\\\n\
                  || - - - -w |\n\
                  ||         ||\n");
            return;
        case liferocks :
            printf("              ^__^\n\
              (00)\\ _______\n\
              (__)\\         )\\/\\\n\
                  || - - - -w |\n\
                  ||         ||\n");
            return;
        default :
            printf("?????\n");
            break;
    }
}

//met à jour le stock
void stock_update(int *stock, int lunch) {
    int crop;
    time_t t;
    srand ((unsigned) time(&t));

    crop = (rand() % 7)-3;
    *stock = (*stock-lunch)+crop;
}

//met à jour la santé
void fitness_update(int *fitness, int lunch) {
    int digestion;
    time_t t;
    srand ((unsigned) time(&t));

    digestion = (rand() % 4)-3;
    *fitness = (*fitness+lunch)+digestion;
}

//transitions des états
etat transition(etat Q, int fitness) {
    int etat_suivant;

    switch (Q) {
        case liferocks : switch (fitness) {
                case 1 :
                case 2 :
                case 3 :
                case 7 :
                case 8 :
                case 9 :
                    etat_suivant = lifesucks;
                    break;
                case 0 :
                case 10 :
                    etat_suivant = byebyelife;
                    break;
                case 4 :
                case 5 :
                case 6 :
                    etat_suivant = liferocks;
                    break;
            }
        case lifesucks : switch (fitness) {
                case 4 :
                case 5 :
                case 6 :
                    etat_suivant = liferocks;
                    break;
                case 0 :
                case 10 :
                    etat_suivant = byebyelife;
                    break;
                case 1 :
                case 2 :
                case 3 :
                case 7 :
                case 8 :
                case 9 :
                    etat_suivant = lifesucks;
                    break;
            }
            break;
    }
    return etat_suivant;
}

int main() {
    int fitness = 5;
    int stock = 5;
    int duree_de_vie = 0;
    int lunchfood;
    int etat_courant = etat_initial();

    //boucle du jeu
    while (est_final(etat_courant)==0) {
        update();
        afficher_vache(etat_courant);

        printf("Nourriture disponible : %d\n", stock);

        //nourrir la vache
        printf("Combien va manger la vache ? ");
        scanf("%d", &lunchfood);
        while (lunchfood<0 || lunchfood>stock) {
            printf("Stock insuffisant : ");
            scanf("%d", &lunchfood);
        }

        //maj de fitness et stock
        fitness_update(&fitness, lunchfood);
        if (fitness>10) fitness=10;
        if (fitness<0) fitness=0;
        stock_update(&stock, lunchfood);
        if (stock>10) stock=10;
        if (stock<0) stock=0;

        //transition de l'etat
        etat_courant = transition(etat_courant, fitness);
        duree_de_vie++;
    }

    //fin du jeu
    update();
    afficher_vache(etat_courant);
    printf("Marguerite est morte :/ ...\nElle aura survecu %d fois\n", duree_de_vie);

    return 0;
}
