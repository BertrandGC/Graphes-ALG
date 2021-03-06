/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

pnoeud_t chercher_noeud(pgraphe_t g, int label) {
  pnoeud_t p;

  p = g;

  while ((p != NULL) && (p->label != label)) {
    p = p->noeud_suivant;
  }
  return p;
}

parc_t existence_arc(parc_t l, pnoeud_t n) {
  parc_t p = l;

  while (p != NULL) {
    if (p->noeud == n)
      return p;
    p = p->arc_suivant;
  }
  return p;
}

void ajouter_arc(pnoeud_t o, pnoeud_t d, int distance) {
  parc_t parc;

  parc = (parc_t)malloc(sizeof(arc_t));

  if (existence_arc(o->liste_arcs, d) != NULL) {
    fprintf(stderr, "ajout d'un arc deja existant\n");
    exit(-1);
  }

  parc->poids = distance;
  parc->noeud = d;
  parc->arc_suivant = o->liste_arcs;
  o->liste_arcs = parc;
  return;
}

void lire_graphe(char *file_name, pgraphe_t *g) {
  pnoeud_t p = NULL; /* premier noeud du graphe */
  pnoeud_t l = NULL; /* dernier noeud du graphe */
  FILE *f;
  int nb_nodes;
  int i;
  pnoeud_t c;
  int origine, destination, distance;

  printf("fichier %s\n", file_name);
  f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "Le fichier %s n'existe pas\n", file_name);
    exit(-1);
  }

  fscanf(f, "%d", &nb_nodes);

  for (i = 0; i < nb_nodes; i++) {
    c = (pnoeud_t)malloc(sizeof(noeud_t));
    c->noeud_suivant = NULL;

    if (fscanf(f, "%d", &c->label) == EOF) {
      fprintf(stderr, "erreur dans le contenu du fichier label %d\n", c->label);
      exit(-1);
    }

    if (chercher_noeud(p, c->label) != NULL) {
      fprintf(stderr, "erreur label deja dans le graphe %d\n", c->label);
      exit(-1);
    }

    if (p == NULL) {
      p = c;
      l = c;
    } else {
      l->noeud_suivant = c;
      l = c;
    }
  }

  while (fscanf(f, "%d %d %d", &origine, &destination, &distance) != EOF) {
    pnoeud_t o, d;

    o = chercher_noeud(p, origine);
    if (o == NULL) {
      fprintf(stderr, "erreur noeud origine %d\n", origine);
      exit(-1);
    }
    d = chercher_noeud(p, destination);
    if (d == NULL) {
      fprintf(stderr, "erreur noeud destination %d\n", destination);
      exit(-1);
    }

    ajouter_arc(o, d, distance);
  }

  *g = p;
}

void ecrire_graphe(pnoeud_t p) {

  int i;
  parc_t arc;

  while (p != NULL) {
    printf("Noeud %d: ", p->label);
    arc = p->liste_arcs;
    while (arc != NULL) {
      printf(" (%d %d) ", arc->noeud->label, arc->poids);
      arc = arc->arc_suivant;
    }
    printf("\n");
    p = p->noeud_suivant;
  }
}

// ===================================================================

int nombre_arcs(pgraphe_t g) {
  /*
    cette fonction renvoie le nombre d'arcs du graphe g
  */
  parc_t arc;
  int nb_arcs = 0;
  pnoeud_t p = g;

  while (p != NULL) {
    arc = p->liste_arcs;
    while (arc != NULL) {
      nb_arcs++;
      arc = arc->arc_suivant;
    }
    p = p->noeud_suivant;
  }

  return nb_arcs;
}

int nombre_sommets(pgraphe_t g) {
  /*
     cette fonction renvoie le nombre de noeuds du graphe g
  */
  pnoeud_t p = g;
  int nb_noeuds = 0;

  while (p != NULL) {
    nb_noeuds++;
    p = p->noeud_suivant;
  }

  return nb_noeuds;
}

int degre_sortant_noeud(pgraphe_t g, pnoeud_t n) {
  /*
    Cette fonction retourne le nombre d'arcs sortants
    du noeud n dans le graphe g
  */
  pnoeud_t p = g;
  parc_t arc = n->liste_arcs;
  int nb_arcs = 0;

  while (arc != NULL) {
    nb_arcs++;
    arc = arc->arc_suivant;
  }

  return nb_arcs;
}

int degre_entrant_noeud(pgraphe_t g, pnoeud_t n) {
  /*
    Cette fonction retourne le nombre d'arcs entrants
    dans le noeud n dans le graphe g
  */
  pnoeud_t p = g;
  parc_t arc;
  int nb_arcs = 0;

  while (p != NULL) {
    arc = p->liste_arcs;
    while (arc != NULL && arc->noeud != n) {
      arc = arc->arc_suivant;
    }
    if (arc != NULL) {
      nb_arcs++;
    }
    p = p->noeud_suivant;
  }

  return nb_arcs;
}

int degre_maximal_graphe(pgraphe_t g) {
  /*
    Max des degres des noeuds du graphe g
  */
  pnoeud_t p = g;
  int max = 0;
  int nb_arcs;
  parc_t arc;

  while (p != NULL) {
    arc = p->liste_arcs;
    nb_arcs = 0;
    while (arc != NULL) {
      nb_arcs++;
      arc = arc->arc_suivant;
    }
    if (nb_arcs > max) {
      max = nb_arcs;
    }
    p = p->noeud_suivant;
  }

  return max;
}

int degre_minimal_graphe(pgraphe_t g) {
  /*
    Min des degres des noeuds du graphe g
  */
  pnoeud_t p = g;
  int min = INT_MAX;
  int nb_arc;
  parc_t arc;

  while (p != NULL) {
    arc = p->liste_arcs;
    nb_arc = 0;
    while (arc != NULL) {
      nb_arc++;
      arc = arc->arc_suivant;
    }
    if (nb_arc < min) {
      min = nb_arc;
    }
    p = p->noeud_suivant;
  }
}

int independant(pgraphe_t g) {
  /* Les aretes du graphe n'ont pas de sommet en commun */
}

int complet(pgraphe_t g) {
  /* Toutes les paires de sommet du graphe sont jointes par un arc */
  /* Chaque sommet peut accéder à tous les autres */

  pnoeud_t p = g;
  int sommet = nombre_sommets(p);
  parc_t arc;
  int nb_arc;
  int estComplet = 1;

  while (p != NULL && estComplet) {
    arc = p->liste_arcs;
    nb_arc = 0;
    while (arc != NULL) {
      nb_arc++;
      arc = arc->arc_suivant;
    }
    if (nb_arc != sommet - 1) {
      estComplet = 0;
    }
    p = p->noeud_suivant;
  }
  return estComplet;
}

int regulier(pgraphe_t g) {
  /*
     graphe regulier: tous les noeuds ont le meme degre
     g est le ponteur vers le premier noeud du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */
  int nb_arc_reference;
  int nb_arc;
  parc_t arc;
  int estRegulier = 1;
  pnoeud_t p = g;

  // Initialisation du nombre d'arc du premier noeuds
  if (p != NULL) {
    nb_arc_reference = degre_sortant_noeud(g, p);
  }
  // On avance au noeud suivant maintenant que l'on a notre reference
  p = p->noeud_suivant;

  while (p != NULL && estRegulier) {
    nb_arc = degre_sortant_noeud(p, p);
    if (nb_arc_reference != nb_arc) {
      estRegulier = 0;
    }
    // On avance dans le parcours de notre graphe
    p = p->noeud_suivant;
  }

  return estRegulier;
}

void afficher_graphe_profondeur(pgraphe_t g) {
  /*
    afficher les noeuds du graphe avec un parcours en profondeur
  */
  return;
}

void colorier_graphe(pgraphe_t g, int *couleurs) {
  /*
    coloriage du graphe g
    Les couleurs des noeuds du graphe sont dans le tableau couleurs
  */
}

void afficher_graphe_largeur(pgraphe_t g) {
  /*
    afficher les noeuds du graphe avec un parcours en largeur
  */
  return;
}

int plus_court_chemin(pgraphe_t g, int origine, int destination, int *chemin,
                      int *nb_noeuds) {
  /*
     Calcul de la longueur du plus court chemin
     entre origine et destination
     La variable chemin contient les noeuds du chemin le plus court
     nb_noeuds indique le nombre de noeuds du chemin
  */
}

/*
  placer les fonctions de l'examen 2017 juste apres
*/

int main(int argc, char **argv) {
  pgraphe_t g;

  if (argc != 2) {
    fprintf(stderr, "erreur parametre \n");
    exit(-1);
  }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...)
    et lit les donnees du fichier passe en parametre
  */

  lire_graphe(argv[1], &g);

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */

  ecrire_graphe(g);

  printf("Nombre arc : %d\n", nombre_arcs(g));

  printf("Nombre sommet : %d\n", nombre_sommets(g));

  printf("Degre sortant pour le noeud 2 : %d\n",
         degre_sortant_noeud(g, g->noeud_suivant));

  printf("Degre entrant pour le noeud 2 : %d\n",
         degre_entrant_noeud(g, g->noeud_suivant));

  printf("Degre minimal graphe: %d\n", degre_minimal_graphe(g));

  printf("Degre maximal graphe: %d\n", degre_maximal_graphe(g));

  printf("Est complet: %d\n", complet(g));

  printf("Est régulier %d\n", regulier(g));
}
