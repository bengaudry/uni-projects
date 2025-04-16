#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void affiche_vache(char eyes[], char tong[], int len_legs) {
    printf("                         ^__ ^\n\
                         (%s)\\ _______\n\
                         (%s)\\         )\\/\\\n\
                             || - - - -w |\n\
                             ||         ||\n", eyes, tong);
    for (int i=0; i<len_legs; i++) { printf("                             ||         ||\n"); }
}

void update() { printf("\033[H\033[J") ;}
void gotoxy(x,y) { printf("\033[%d;%dH",x,y);}

void wild_cow() {
    for (int i=0; i<100; i++) {
        update();
        gotoxy(i*3,0);
        affiche_vache("00", "__", 3);
        sleep(1);
        update();
        gotoxy(i*3,0);
        affiche_vache("^^", "u ", 1);
        sleep(1);
    }
}


int main(int argc,char *argv[]) {
    char eyes[]="00";
    char tong[]="__";
    int len_legs=0;

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i],"--eyes")==0) strcpy(eyes, argv[i+1]);
        if (strcmp(argv[i],"--tong")==0) strcpy(tong, argv[i+1]);
        if (strcmp(argv[i],"--legs")==0) sscanf(argv[i+1], "%d", &len_legs);
        if (strcmp(argv[i],"--wild")==0) { wild_cow(); return 0; }
    }

    affiche_vache(eyes,tong,len_legs);
    return 0;
}
