README - Projet Ecosystème

Description :
  Ce projet implémente un modèle d'écosystème dans lequel les proies et les prédateurs évoluent dans un environnement en utilisant des règles de déplacement, de reproduction et d'interaction. Les proies consomment de l'énergie provenant du monde (herbe), tandis que les prédateurs consomment les proies pour survivre.

  Le code utilise un modèle simple basé sur des listes chaînées pour gérer les animaux et un tableau représentant l'environnement.

Composants :
  - ecosys.c : contient la logique du système d'écosystème (création et gestion des animaux, reproduction, mouvement, rafraîchissement des listes, affichage, lecture et écriture de l'écosystème).
  - main_ecosys.c : programme principal qui initialise les proies et les prédateurs, effectue des tests, et simule l'écosystème.
  - main_tests.c et maint_tests2.c : différents tests pour vérifier les fonctionnalités principales comme la création d'animaux, la suppression, la lecture et l'écriture dans des fichiers.

Compilation et Exécution :
1. Compilation : make <nom_executable> ou simplement make pour gérer les dépendances. 

2. Exécution : ./<nom_executable> pour démarrer la simulation de l'écosystème.

Le programme simule un environnement avec des proies et des prédateurs dans un monde de taille définie (variables SIZE_X et SIZE_Y).

Fonctionnalités :

    Création des animaux : Position, direction et énergie des proies et prédateurs.
    Mouvement : Déplacement dans un monde torique (les bords sont connectés).
    Reproduction : Les animaux se reproduisent avec une probabilité donnée.
    Interaction : Les prédateurs mangent les proies pour récupérer de l'énergie.
    Affichage : L'état de l'écosystème est affiché à chaque itération.
    Sauvegarde / Chargement : Sauvegarde de l'état dans un fichier texte via ecrire_ecosys() et lire_ecosys().


Tests : 

Les tests valident la création, la gestion des listes chaînées, la reproduction et les interactions entre les animaux. Ils sont situés dans main_tests.c et maint_tests2.c.
Fichiers

    liste.txt : Fichier pour sauvegarder et charger l'état de l'écosystème.
    ecosys.h : Déclarations des structures et fonctions du projet.


Variables Globales :

    p_ch_dir : Probabilité de changement de direction des animaux.
    p_reproduce_proie : Probabilité de reproduction des proies.
    p_reproduce_predateur : Probabilité de reproduction des prédateurs.
    temps_repousse_herbe : Énergie fournie par l'herbe aux proies.


Configuration :

Modifiez les tailles du monde (SIZE_X et SIZE_Y) dans ecosys.h et ajustez les paramètres de reproduction et de mouvement pour personnaliser la simulation.
Dépendances

    Bibliothèque standard C : stdio.h, stdlib.h, string.h, assert.h.
    unistd.h pour usleep, permettant de simuler les cycles avec des pauses.


Conclusion :

Ce projet est une simulation d'écosystème, illustrant les dynamiques entre prédateurs et proies dans un environnement contrôlé.
