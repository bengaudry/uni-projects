#include "generation_terrains.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int nb_cases_occupees(Terrain *T)
{
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++)
  {
    for (y = 0; y < hauteur(T); y++)
    {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv)
{
  int i, N, l, h;
  int cases_occupees;
  int terrains_generes, terrains_corrects_generes;
  float dObst, dObst_reelle;
  float densite_totale;
  FILE *resFile;
  Terrain T;

  if (argc < 6)
  {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0)
  {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0)
  {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0))
  {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[5], "w");

  T.hauteur = h;
  T.largeur = l;

  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  srand(getpid());

  densite_totale = 0;
  terrains_corrects_generes = 0;
  terrains_generes = 0;
  fprintf(resFile, "%d\n", h);
  fprintf(resFile, "%d\n", l);
  for (i = 1; i <= N; i++)
  {
    // Crée des terrains tant qu'ils ne sont pas corrects
    do
    {
      generation_aleatoire(&T, l, h, dObst);
      terrains_generes++;
    } while (!existe_chemin_vers_sortie(&T));

    // Ecriture du terrain dans le fichier
    ecrire_terrain(resFile, &T, l / 2, h / 2);

    // Calcul des statistiques
    cases_occupees = nb_cases_occupees(&T);
    dObst_reelle = (float)cases_occupees / ((float)l * (float)h);
    densite_totale += dObst_reelle;
    fprintf(resFile, "%3.2f\n", dObst_reelle);
    terrains_corrects_generes++;
  }

  // Affichage des statistiques
  fprintf(resFile, "%3.2f\n", densite_totale / N);
  fprintf(resFile, "%3.0f%%\n", 100 * ((float)terrains_corrects_generes / (float)terrains_generes));

  fclose(resFile);
  return 0;
}
