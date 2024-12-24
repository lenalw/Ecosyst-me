#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000



int main(void) {
 
  /* A completer. Part 2:
   * exercice 4, questions 2 et 4 
   * exercice 6, question 2
   * exercice 7, question 3
   * exercice 8, question 1
   */

  srand(time(NULL));

      /*Test de deplacement */
  Animal *animal_test = creer_animal( SIZE_X - 1, SIZE_Y-1, 10);
  printf("Position initiale de l'animal de test: x=%d, y=%d\n", animal_test->x, animal_test->y);
  // Définir une direction pour tester la toricité
  animal_test->dir[0] = 1;
  animal_test->dir[1] = 1;

  bouger_animaux(animal_test);

  //nouvelle position
  printf("Nouvelle position de l'animal de test: x=%d, y=%d\n", animal_test->x, animal_test->y);
  free(animal_test);


      /*Test de reproduction*/
  Animal *liste_reproduction = NULL;

  ajouter_animal(5, 5, 10, &liste_reproduction);
  ajouter_animal(7, 7, 10, &liste_reproduction);

  for (int i = 0; i < 3; i++) {
      printf("Iteration %d : Nombre d'animaux avant reproduction = %d\n", i, compte_animal_it(liste_reproduction));
      reproduce(&liste_reproduction, 1.0); // p_reproduce à 1.0
      printf("Iteration %d : Nombre d'animaux après reproduction = %d\n", i, compte_animal_it(liste_reproduction));
  }

  liste_reproduction = liberer_liste_animaux(liste_reproduction);


  //qst 3 exo 6
  //creation des proies et prédateurs
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie = 10;
  for (int i = 0; i < 20 ; i++){
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie, &liste_proie); //passage de la liste par adresse obligatoire
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie, &liste_predateur);  
    }

  int nbproie = compte_animal_rec(liste_proie);
  int nbpred = compte_animal_rec(liste_predateur);

  printf("Le nombre de prédateurs est : %d et le nombre de proies est : %d\n", nbpred, nbproie);

  afficher_ecosys(liste_proie, liste_predateur);
  
  //Initialisation du monde
  int monde[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; ++i)
    for (int j = 0; j < SIZE_Y; ++j)
      monde[i][j] = 0;
  

  int iter = 0;
  while (liste_proie && liste_predateur && iter < 200) {
    afficher_ecosys(liste_proie, liste_predateur);
    usleep(T_WAIT);
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    rafraichir_monde(monde);
    
    iter++;
  }


  /*
  int iter = 0;
  while(liste_proie && iter < 200){
    rafraichir_proies(&liste_proie, monde);
    afficher_ecosys(liste_proie, liste_predateur);
    usleep(T_WAIT);
    iter++;
  }
  
  iter = 0;
  while(liste_predateur && iter < 200){
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    afficher_ecosys(liste_proie, liste_predateur);
    usleep(T_WAIT);
    iter++;
  }
  */

  liste_predateur = liberer_liste_animaux(liste_predateur);
  liste_proie = liberer_liste_animaux(liste_proie);

  if(!liste_predateur) printf("liste_predateur libérée\n");
  if(!liste_proie) printf("liste_proie libérée\n");
  return 0;
}


