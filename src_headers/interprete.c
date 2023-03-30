#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "type_pile.h" 


/*
 *  Auteur(s) : OURZIK Jugurta, MIEL Nils
 *  Date :20/10/2022
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug)
{
    
    char commande;
     debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();
  
    // À partir d'ici, beaucoup de choses à modifier dans la suite.
 //à modifier: premiere commande de la sequence
    int ret;

    cellule_t *aux1, *aux2,*pa,*pb;
    int x, x1, x2,a,b,n;
    Genre genre, genre2,genre3;

    PileCel *Pile=malloc(sizeof(PileCel));
    Pile->tete = NULL;
    // vider_pile(Pile); // utilisée pour les valeurs de retour
    cellule_t *cel =seq->tete;
    
    commande = cel->command;
    // cellule_t *save2;
    while (cel != NULL)
    { //à modifier: condition de boucler
         cel = seq->tete;
         commande = cel->command;
       
        printf("command : %c \n",commande);
        switch (commande)
        {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

        case 'A':
            ret = avance();
            if (ret == VICTOIRE){
                seq->tete = NULL;
                return VICTOIRE; /* on a atteint la cible */
            }
            if (ret == RATE){
                seq->tete = NULL;
                return RATE; /* tombé dans l'eau ou sur un rocher */
            }
            printf("check");
            break; /* à ne jamais oublier !!! */

        case 'G':
            gauche();
            break;
        case 'D':
            printf("SEQ \n");
                    afficher(seq);
            droite();
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            x = (int)commande-(int)'0';
            empiler_entier(Pile, x);
            printf("check");
            break;

        case '+':
            x1 = depiler_entier(Pile);
            x2 = depiler_entier(Pile);
            empiler_entier(Pile, x2 + x1);
            break;
        case '-':
            x1 = depiler_entier(Pile);
            x2 = depiler_entier(Pile);
            printf("Pile : ");
            empiler_entier(Pile, x2 - x1);
            break;
        case '*':
            x1 = depiler_entier(Pile);
            x2 = depiler_entier(Pile);
            empiler_entier(Pile, x2 * x1);
            break;

        case 'P':
             x = depiler_entier(Pile);
            pose(x);
            break;
        case 'M':
             x = depiler_entier(Pile);
            empiler_entier(Pile, mesure(x));
            printf("check");
            break;
        case '?':
            aux1 = depiler_pointeur(Pile);
            printf("depiler_pointeur = OK");
            aux2 = depiler_pointeur(Pile);
             printf("depiler_pointeur = OK");
            x = depiler_entier(Pile);
            if (x == 0){
                inserer(cel, aux1);
                printf("inserer = OK");
            }else{
                inserer(cel, aux2);
                printf("depiler_pointeur = OK");
            }
            printf("check");
            break;

        case '{':
            // save2 = cel;
            if (cel->suivant->command!='}')
                empiler_pointeur(Pile, cel->suivant);
            else
                empiler_pointeur(Pile, NULL);
            groupe_commandes(&cel);
            // detruireCellule(save2);
            printf("check");
            break;
              // on ne peut pas lire '}' car après groupe_commandes cel->commande='}' et avec le break on passe directement au suivant.
        case 'X':
            genre = type_sommet(Pile);
            if (genre==ENT){
                a = depiler_entier(Pile);
            }else{
                pa = depiler_pointeur(Pile);
            }
            genre2=type_sommet(Pile);
            if (genre2==ENT){
                 b = depiler_entier(Pile);
            }else{
                pb = depiler_pointeur(Pile);
            }
            if (genre==ENT&&genre2==ENT)
            {
                empiler_entier(Pile, a);
                empiler_entier(Pile, b);
            }else if (genre==ENT&&genre2==PNT){
                empiler_entier(Pile, a);
                empiler_pointeur(Pile, pb);
            }else if (genre==PNT&&genre2==ENT){
                empiler_pointeur(Pile, pa);
                empiler_entier(Pile, b);
            }else{
                empiler_pointeur(Pile, pa);
                empiler_pointeur(Pile, pb);
            }
            break;
        case '!':
            
            genre3 = type_sommet(Pile);
            if (genre3==PNT){
                aux1 = depiler_pointeur(Pile);
                inserer(cel, aux1);
                printf("check");
            }
            break;
        case 'C':
            genre = type_sommet(Pile);
            if (genre==ENT){
                a = depiler_entier(Pile);
                empiler_entier(Pile, a);
                empiler_entier(Pile, a);
            
            }
            else
            {
                pa = depiler_pointeur(Pile);
                empiler_pointeur(Pile, pa);
                printf("empiler_pointeur check\n");
                int taille2 = taille_seq(pa);
                char tab[taille2];
                printf("taille seq = %d \n",taille2);
                deconversion(pa, tab);
                printf("tab = %s", tab);
                sequence_t seq_clone = {.tete=NULL};
                conversion(tab, &seq_clone);
                empiler_pointeur(Pile, (&seq_clone)->tete);
            }
            break;
        case 'I':
            genre = type_sommet(Pile);
            if (genre==ENT){
             depiler_entier(Pile);
            }
            else
            {
                depiler_pointeur(Pile);
            }
            break;
        case 'B':
            a = depiler_entier(Pile);
            if (a>0){
                char tabboucle[10];
                sequence_t seq_boucle = {.tete = NULL};
                tabboucle[0] = 'C';
                tabboucle[1] = '!';
                a--;
                printf("n =%d",a);
                tabboucle[2] = a+'0';
                tabboucle[3] = 'B';
                tabboucle[4] = '\0';
                printf("%s", tabboucle);
                conversion(tabboucle, &seq_boucle);
                inserer(cel, (&seq_boucle)->tete);
            }else{
                depiler_pointeur(Pile);
            }
            break;

        case 'R':
            x1 = depiler_entier(Pile);
            n = depiler_entier(Pile);
            afficher(seq);
            if (taille_seq(cel) >= n)
            {
                Celpile tab[100];
                Genre genra;
                for (int i = n - 1; i >= 0; i--)
                {
                    Celpile modal;
                    genra = type_sommet(Pile);
                    if (genra == ENT)
                        modal.n = depiler_entier(Pile);
                    else
                        modal.pointeur = depiler_pointeur(Pile);

                    tab[i] = modal;
                }
                if (x1 > 0)
                {
                    for (int i = 0; i < x1; i++)
                    {
                        rotate1pas(tab, x1, n, Pile);
                    }
                    
                }
            }

            break;

         default:
             eprintf("Caractère inconnu: '%c'\n", commande);
         }
        //  cellule_t *save = cel;
         seq->tete = cel->suivant;
        //  detruireCellule(save);
        
         /* Affichage pour faciliter le debug */
         afficherCarte();
         printf("Programme:");
         afficher(seq);
         printf("\n");
         if (debug)
             stop();
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */
    seq->tete = NULL;
    return CIBLERATEE;
    
}
