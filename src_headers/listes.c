#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include <string.h>


/*
 *  Auteur(s) : 
 *  Date : 13/10/22
 *  Suivi des Modifications :
 * all
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void)
{
    /* À compléter (utiliser malloc) */
    cellule_t*newcel = malloc(sizeof(cellule_t));
    return newcel;
}


void detruireCellule (cellule_t* cel)
{
    /* À compléter (utiliser free) */
    free(cel);
}

void Ajouter_Fin_lc(sequence_t *l,char c){
    cellule_t* new_cel=nouvelleCellule();
    new_cel->command=c;
    new_cel->suivant=NULL;
    
    if (l->tete==NULL){
        l->tete=new_cel;
    }
    else{
        cellule_t *current;
        current = l->tete;
        while(current->suivant!=NULL)
            current=current->suivant;

         current->suivant = new_cel;
    }   
    
}
int longueur_string(char* txt){
    int i=0;
    while(txt[i]!='\0'){
        i++;
    }
    return i;
}

void conversion (char *texte, sequence_t *seq)
{
  /* À compléter */
   seq->tete = NULL;
   int taille = longueur_string(texte);
   cellule_t *current= seq->tete;
   for (int i = 0; i <taille ; i++)
   {
    cellule_t* new_cel=nouvelleCellule();
    new_cel->command=texte[i];
    new_cel->suivant=NULL;
        
    if (current==NULL){
        seq->tete=new_cel;
        current = new_cel;
    }
    else{
        current->suivant = new_cel;
        current = current->suivant;
    }
   }
}
// cellule_t* copie_seq(cellule_t*aux1){
//     cellule_t *res = NULL;
//     cellule_t *current = aux1;
//     cellule_t *current
// }

void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    
    cellule_t *current = seq->tete;
    while(current!=NULL){
        printf("%c ", current->command);
        current = current->suivant;
    }
}
int taille_seq(cellule_t* cel)
{
     /* Le pointeur doit être valide */
    int cpt = 0;
    cellule_t *current = cel;
    while(current!=NULL){
        cpt++;
        current = current->suivant;
    }
    return cpt;
}
void deconversion(cellule_t* cel,char tab[])
{
     /* Le pointeur doit être valide */
    int i = 0;
    cellule_t *current = cel;
    while(current!=NULL){
        tab[i]=current->command;
        i++;
        current = current->suivant;
    }
    tab[i] = '\0';
}


// int main(){
//     char tab[7] = "Bonjour";
//     printf("tab = %s\n", tab);
//     sequence_t seq = {.tete=NULL};
//     conversion(tab, &seq);
//     printf(" seq = ");
//     afficher(&seq);
//     printf("\n");
//     char tab2[taille_seq((&seq)->tete)];
//     deconversion((&seq)->tete, tab2);
//     printf("tab = %s\ntab2= %s\n", tab, tab2);
// }
