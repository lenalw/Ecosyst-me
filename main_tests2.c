//Lena Lalaoui

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


int main(void) {

  srand(time(NULL)); 
  
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;

  // Ajout de 20 proies et 20 predateurs dans l'ecosysteme
  for (int i = 0; i < NB_PROIES; i++) {
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, (float)(rand() % 10) + 5, &liste_proie);
  }

  for (int i = 0; i < NB_PREDATEURS; i++) {
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, (float)(rand() % 10) + 5, &liste_predateur);
  }

  int nbproie = compte_animal_rec(liste_proie);
  int nbpred = compte_animal_rec(liste_predateur);

  printf("Le nombre de prédateurs est : %d et le nombre de proies est : %d\n", nbpred, nbproie);
  afficher_ecosys(liste_proie, liste_predateur);

  //Ecriture des deux listes dans un fichier
  ecrire_ecosys("liste.txt", liste_proie, liste_predateur);
  printf("Écriture de l'écosystème dans le fichier 'liste.txt' terminée.\n");


  //Lecture des deux listes depuis un fichier
  Animal *new_liste_proie = NULL;
  Animal *new_liste_predateur = NULL;
  lire_ecosys("liste.txt", &new_liste_proie, &new_liste_predateur);
  printf("Lecture de l'écosystème depuis le fichier 'liste.txt' terminée.\n");
  printf("Affichage de l'ecosysteme lu depuis le fichier : \n");
  afficher_ecosys(new_liste_proie, new_liste_predateur);

  //supprimer un element
  if (liste_predateur) {
    printf("Suppression du premier prédateur\n");
    enlever_animal(&liste_predateur, liste_predateur);
    afficher_ecosys(liste_proie, liste_predateur);
  }

  //liberation des listes 
  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);
  new_liste_proie = liberer_liste_animaux(new_liste_proie);
  new_liste_predateur = liberer_liste_animaux(new_liste_predateur);

  if (!liste_proie) printf("Liste de proies libérée.\n");
  
  if (!liste_predateur) printf("Liste de prédateurs libérée.\n");

  return 0;
}
