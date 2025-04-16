#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void update() { printf("\033[H\033[J") ;}

void afficher_bulle(char phrase[]) {
    int len = strlen(phrase);

    printf(" -");
    for (int i=0; i<len; i++) {
        printf("-");
    }
    printf("-\n");
    printf("< %s >\n", phrase);
    printf(" -");
    for (int i=0; i<len; i++) {
        printf("-");
    }
    printf("-\n");
}

void read_cow(FILE *f) {
    char c;
    char phrs[50]="";
    int len=0;

    if (f==NULL) {printf("fichier inexistant\n"); return;}

    //affichage du premier caractère
    update();
    fscanf(f, "%c",&c);
    afficher_bulle(phrs);
    printf("          ^__^\n\
          (oo)\\ _______\n\
          (__)\\         )\\/\\\n\
           %c  || - - - -w |\n\
              ||         ||\n", c);
    phrs[len]=c;
    len++;

    //on attend et on clear
    sleep(1);
    update();

    //affichage pour chaque caractère
    fscanf(f, "%c", &c);
    while (!feof(f)) {
        afficher_bulle(phrs);
        printf("          ^__^\n\
          (oo)\\ _______\n\
          (__)\\         )\\/\\\n\
           %c  || - - - -w |\n\
              ||         ||\n", c);
        phrs[len]=c;
        len++;
        fscanf(f, "%c", &c);
        //on attend et on clear
        sleep(1);
        update();
    }

    //affichage du dernier caractère
    afficher_bulle(phrs);
    printf("          ^__^\n\
          (oo)\\ _______\n\
          (__)\\         )\\/\\\n\
              || - - - -w |\n\
              ||         ||\n");

}


int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");

    read_cow(f);

    return 0;
}