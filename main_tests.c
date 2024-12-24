#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "ecosys.h"

int main(void) {
  //int i; (variable inutilisée)
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie=10;

  srand(time(NULL));

  Animal *a1 = creer_animal(0,10, energie);
  assert(a1->x >= 0 && a1->y >=0 && a1->energie == 10);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  a1->suivant=a2;
  a2->suivant=a3;
  a3->suivant=a4;

  liste_proie=a1;
  assert(liste_proie != NULL);

  Animal *a5 = creer_animal(2,5, energie);
  Animal *a6 = creer_animal(15,35, energie);
  Animal *a7 = creer_animal(9,22, energie);
  Animal *a8 = creer_animal(17,3, energie);
  
  a5->suivant=a6;
  a6->suivant=a7;
  a7->suivant=a8;

  liste_predateur=a5;
  assert(liste_predateur != NULL);
  afficher_ecosys(liste_proie,liste_predateur);  

  ajouter_animal(2,3,5,&liste_proie);
  afficher_ecosys(liste_proie,liste_predateur); 
  ajouter_animal(2,3,5,&liste_predateur); 
  afficher_ecosys(liste_proie,liste_predateur);

  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);

  if(!liste_predateur) printf("liste_predateur libérée\n");
  if(!liste_proie) printf("liste_proie libérée\n");

  return 0;
}
