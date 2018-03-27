
typedef struct a *parc_t ;

/*
  definition des types noeud et pointeur de noeud
  un graphe est constitué d'une liste de noeuds
*/

typedef struct n
{
  int        label ; // label du noeud/sommet
  parc_t     liste_arcs ; // arcs sortants du noeud
  struct n   *noeud_suivant ; // noeud/sommet suivant du graphe
  
} noeud_t, *pnoeud_t ;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortant d'un noeud sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre
  a une distance
*/

typedef struct a {
  
                  int         poids ; // poids de l arc
                  pnoeud_t    noeud ; // identificateur du noeud destinataire
                  struct a *  arc_suivant ; // arc suivant
  
} arc_t, *parc_t ;

/*
  pgraphe_t: pointeur vers le premier noeud d'un graphe
*/

typedef pnoeud_t pgraphe_t ;


/*
  DEFINIR LE TYPE chemin_t (examen 2017)
*/
