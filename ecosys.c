
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

/* PARTIE 1*/

/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  if(!na){
    printf("Erreur lors de l'allocation mémoire\n");
    return NULL;
  }

  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  /*A Completer*/
  assert(x >= 0 && x <= SIZE_X);
  assert(y >= 0 && y <= SIZE_Y);

  *liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
  return ;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/

  assert(liste);
  assert(animal);
  //1er element:
  Animal *prec = NULL;
  Animal *actuel = *liste;

  if(actuel == animal){
    *liste = actuel->suivant;
    free(actuel);
    return ;
  }


  while(actuel){
    if (actuel == animal){
      prec->suivant = actuel->suivant;
      free(actuel);
      return ;
    }

    prec = actuel;
    actuel = actuel->suivant;
  }

    fprintf(stderr, "Erreur : L'animal à supprimer n'a pas été trouvé dans la liste.\n");
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal *liberer_liste_animaux(Animal *liste)
{
  Animal *suiv;

  while (liste)
  {
    suiv= liste->suivant;
    free(liste); 
    liste = suiv;
  }
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  /*Erreur : les SIZE_X et SIZE_Y etaient inversés : lignes 74-75, 100-105-107-113*/
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");

  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

//Fonction d'écriture
void ecrire_ecosys(const char* nom_fichier,Animal *liste_proie, Animal *liste_predateur){

  FILE *fe = fopen(nom_fichier, "w");
  if (!fe) {
    printf("Erreur lors de l'ouverture du fichier.");
    exit(1);
  }

  fprintf(fe, "<proies>\n");
  Animal *listeproie = liste_proie;

  while(listeproie){
    fprintf(fe, "x=%d y=%d dir=[%d %d] e=%f\n", listeproie->x, listeproie->y, listeproie->dir[0], listeproie->dir[1], listeproie->energie);
    listeproie = listeproie->suivant;
  }
  fprintf(fe, "</proies>\n");

  fprintf(fe, "<predateurs>\n");
  Animal *listepredateur = liste_predateur;

  while(listepredateur){
    fprintf(fe, "x=%d y=%d dir=[%d %d] e=%f\n", listepredateur->x, listepredateur->y, listepredateur->dir[0], listepredateur->dir[1], listepredateur->energie);
    listepredateur = listepredateur->suivant;
  }
  fprintf(fe, "</predateurs>\n");

  fclose(fe);
}


//Fonction de lecture
void lire_ecosys(const char *nom_fichier, Animal **liste_proie, Animal **liste_predateur){
	FILE *f = fopen(nom_fichier, "r");
	if (f == NULL){
		printf("Erreur lors de l'ouverture.");
		exit(1);
	}

	char buffer[256]; 
	fgets(buffer, 256, f);
	assert(strncmp(buffer, "<proies>", 8) == 0);

	int x_lu, y_lu, dir0, dir1; float e_lu;
	fgets(buffer, 256, f);
	while(strncmp(buffer, "</proies>", 9) != 0){
		sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0, &dir1, &e_lu);
		Animal *a = creer_animal(x_lu, y_lu, e_lu);
		a->dir[0] = dir0; 
		a->dir[1] = dir1;
		a->suivant = *liste_proie;
		*liste_proie = a;
		fgets(buffer, 256, f);
	}

	fgets(buffer, 256, f);
	assert(strncmp(buffer, "<predateurs>", 12) == 0);

	fgets(buffer, 256, f);
	while(strncmp(buffer, "</predateurs>", 13) != 0){
		sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0, &dir1, &e_lu);
		Animal *a = creer_animal(x_lu, y_lu, e_lu);
		a->dir[0] = dir0; 
		a->dir[1] = dir1;
		a->suivant = *liste_predateur;
		*liste_predateur = a;
		fgets(buffer, 256, f);
	}

	fclose(f);
}

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    Animal *temp = la;
    
    while(temp){
      float prob = (float)rand() / RAND_MAX;
      if (prob < p_ch_dir){ //chaque animal peut operer un changement de direction avec une probabilite p_ch_dir
        temp->dir[0] = rand() % 3 - 1;
        temp->dir[1] = rand() % 3 - 1;
      }

      //Gestion du monde torique pour les bords
      temp->x = (temp->x + temp->dir[0] + SIZE_X) % SIZE_X;
      temp->y = (temp->y + temp->dir[1] + SIZE_Y) % SIZE_Y;

      temp=temp->suivant;
      
    }
  return ;
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
  assert(liste_animal);
  assert(p_reproduce >= 0.0 && p_reproduce <= 1.0);

  Animal *temp = *liste_animal;
  while(temp){
    if ( (float)rand() / RAND_MAX < p_reproduce){
      ajouter_animal(temp->x, temp->y, (float)temp->energie/2, liste_animal);
      temp->energie=(float)temp->energie/2;
    }
    temp=temp->suivant;
   }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
  assert(liste_proie);

  bouger_animaux(*liste_proie);
  Animal *temp = *liste_proie;
  Animal *suiv;
  while (temp){
    suiv = temp->suivant;
    temp->energie--;
    if (temp->energie < 0){
        enlever_animal(liste_proie, temp);
    }
    else if(monde[temp->x][temp->y] >= 0){
    	
    	  temp->energie += monde[temp->x][temp->y];
    	  monde[temp->x][temp->y] = temps_repousse_herbe;
    	}
    temp = suiv;
  }
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
    Animal *temp = l;
    while(temp){
      if (temp->x == x && temp->y == y)
        return temp;
      temp = temp -> suivant;
    }

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/
  assert(liste_predateur);

  bouger_animaux(*liste_predateur);
  Animal *temp = *liste_predateur;
  Animal *suiv;
  while (temp){
    suiv = temp->suivant;
    temp->energie--;
    if (temp->energie < 0){
        enlever_animal(liste_predateur, temp);
    }
    else{
      Animal *proie = animal_en_XY(*liste_proie, temp->x, temp->y);
      if (proie){
        temp->energie += proie->energie;
        enlever_animal(liste_proie, proie);
      }
    }
    temp = suiv;
  }
  reproduce(liste_predateur,p_reproduce_predateur);

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
   /*A Completer*/
  int i, j;
  for (i = 0; i < SIZE_X; i++)
    for (j = 0; j < SIZE_Y; j++)
      monde[i][j]++;

}

