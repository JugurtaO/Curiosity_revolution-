#include"listes.h"
#define TAILLE_MAX 100

typedef enum
{
  ENT,
  PNT
} Genre;

struct Celpil
{
  int n;
  cellule_t* pointeur;
  Genre g;
  struct Celpil *suivant;
};
typedef struct Celpil Celpile;

struct Pile {
    Celpile *tete;
};
typedef struct Pile PileCel;
/* Constructeurs */
Genre type_sommet(PileCel *p);
void afficher_pile(PileCel *p);
/* Créer une pile vide */
void vider_pile(PileCel *p);
Celpile *nouvelleCellule_P(void);

/* Opérations d'accès */


/* Retourne vrai ssi p est vide */
int est_vide(PileCel *p);


/* Opérations de modification */


/* Empiler un entier x */
void empiler_entier(PileCel *p, int x);
void empiler_pointeur(PileCel *p, cellule_t *cel);

/* Supprimer et renvoyer l'entier en haut de la pile */
/* Précondition : p non vide */
int depiler_entier(PileCel *p);

cellule_t *depiler_pointeur(PileCel *p);

void inserer(cellule_t *cel, cellule_t *p);
void groupe_commandes(cellule_t **cel);

void rotate1pas(Celpile tab[], int x, int n,PileCel*p);
