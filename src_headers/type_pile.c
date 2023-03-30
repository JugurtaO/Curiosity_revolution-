#include "type_pile.h" 
#define TAILLE_MAX 100
#include <stdio.h>
#include <stdlib.h>

Genre type_sommet(PileCel *p){
    return p->tete->g;
}
void afficher_pile(PileCel*p){
    Celpile *current = p->tete;
    while (current!=NULL){
        printf("%d ", current->n);
        current = current->suivant;
    }
}
/* Créer une pile vide */
void vider_pile(PileCel *p){
    Celpile *cel = p->tete;
    while(cel!=NULL){
        Celpile *save = cel;
        cel = cel->suivant;
        free(save);
    }
    p->tete = NULL;
}
Celpile* nouvelleCellule_P (void)
{
    /* À compléter (utiliser malloc) */
    Celpile*newcel = malloc(sizeof(Celpile));
    return newcel;
}

/* Opérations d'accès */

/* Retourne vrai ssi p est vide */
int est_vide(PileCel *p){
    return (p->tete==NULL);
}


/* Opérations de modification */



/* Empiler un entier x */
/* Précondition : taille(p) < TAILLE_MAX */
void empiler_entier(PileCel *p, int x){
    Celpile* newcel = nouvelleCellule_P();
    newcel->n = x;
    newcel->g = ENT;
    newcel->suivant = p->tete;
    p->tete = newcel;
 }
void empiler_pointeur(PileCel *p,cellule_t*cel){
    Celpile* newcel = nouvelleCellule_P();
    newcel->pointeur = cel;
    newcel->g = PNT;
    newcel->suivant = p->tete;
    p->tete = newcel;
}

/* Supprimer et renvoyer l'entier en haut de la pile */
/* Précondition : p non vide */
// genre type_sommet(PileCel *p){
//     return (p->tete->g);
// }
int depiler_entier(PileCel *p){
   
        int x = p->tete->n;
        Celpile *save = p->tete;
        p->tete = p->tete->suivant;
        free(save);
        return x;
    
   
}
cellule_t * depiler_pointeur(PileCel* p){

        cellule_t* x = p->tete->pointeur;
        Celpile *save = p->tete;
        p->tete = p->tete->suivant;
        free(save);
        return x;
    
    
}

void inserer(cellule_t *cel, cellule_t*p){
    if (p!=NULL){
        cellule_t *save = cel->suivant;
        cel->suivant = p;
        cellule_t *current;
        current = p;
        while(current->suivant!=NULL)
            current=current->suivant;

        current->suivant = save;
    }
}
void groupe_commandes(cellule_t** cel){
    cellule_t *current = (*cel)->suivant;
    cellule_t *prec = (*cel);
    int cpt1 = 1;
    int cpt2 = 0;
    cellule_t *save = NULL;
    while (cpt1 != cpt2)
    {
        if (current->command=='{')
            cpt1++;
        else if (current->command=='}')
            cpt2++;
        if (cpt1==cpt2){
            save = current;
            prec->suivant = NULL;
        }
        prec = prec->suivant;
        current = current->suivant;
    }
    (*cel) = save;
}


void rotate1pas(Celpile tab[],int x,int n,PileCel *p){
    Celpile tmp;
    tmp = tab[0];
   

    for (int i = 0; i < n; i++)
        tab[i] = tab[i + 1];
      

    tab[n - 1] = tmp;
    for (int i =0; i<n ;i++){
        Genre genre = tab[i].g;
        if (genre==ENT)
            empiler_entier(p, tab[i].n);
        else
            empiler_pointeur(p, tab[i].pointeur);
    }
    // printf("rotation checked");
}
