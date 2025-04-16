#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "newcow.h"

void affiche_vache(Settings settings)
{
    char tongue = ' ';
    char *eyes_content;
    eyes_content = settings.eyes_content;

    // Change le contenu des yeux et affiche la langue pendante si la vache est morte
    if (settings.is_dead) {
        tongue = 'U'; 
        eyes_content = "xx";
    } 

    printf("    ^__^\n    (%s)\\_______\n    (%s)\\       )\\/\\\n     %c  ||----w |\n", eyes_content, settings.tongue_content, tongue);

    for (int i = 1; i <= settings.height; i++)
    {
        printf("        ||     ||\n");
    }
}

// Modifie une string à partir d'un index n donné, et enlève le début
char *strcut(char *str, int n)
{
    if (str == NULL || n < 0)
        return "";

    int i, j;
    // Déplacer les caractères à partir de la n-ième position vers le début
    for (i = 0, j = n; str[j] != '\0'; ++i, ++j)
    {
        str[i] = str[j];
    }
    // On termine la chaîne
    str[i] = '\0';
    return str;
}


int main(int argc, char *argv[])
{
    // Initialisation des paramètres par défaut de la vache
    Settings default_settings = {
        .height = 1,
        .tongue_content = "__",
        .eyes_content = "00",
        .is_dead = 0,
    };

    // On boucle sur les arguments
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];

        // Si l'argument est un paramètre
        if (arg[0] == '-')
        {
            // Paramètre des yeux
            if (arg[1] == 'e')
            {
                if (argc <= i + 1)
                {
                    printf("Argument manquant après -e\n");
                    return 1;
                }
                if (strlen(argv[i + 1]) != 2)
                {
                    printf("Le contenu des yeux (-e option) ne doit pas dépasser deux charactères\n");
                    return 1;
                }
                default_settings.eyes_content = argv[i + 1];
            }

            // Paramètre de la langue
            if (arg[1] == 'T')
            {
                if (argc <= i + 1)
                {
                    printf("Argument manquant après -T\n");
                    return 1;
                }
                if (strlen(argv[i + 1]) != 2)
                {
                    printf("Le contenu de la langue (-T option) doit être de deux charactères\n");
                    return 1;
                }
                default_settings.tongue_content = argv[i + 1];
            }

            // Paramètre de mort
            if (arg[1] == 'd')
            {
                default_settings.is_dead = 1;
            }

            // Paramètre supplémentaire de la hauteur des pattes
            if (arg[1] == 'H')
            {
                if (argc <= i + 1)
                {
                    printf("Argument manquant après -H\n");
                    return 1;
                }
                default_settings.height = atoi(argv[i + 1]);
            }
        }
    }

    affiche_vache(default_settings);

    return 0;
}
