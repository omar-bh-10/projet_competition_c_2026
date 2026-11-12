#include <stdio.h>
#include <stdlib.h>
#include "match.h"

Match* creer_match(int id)
{
    Match *m = malloc(sizeof(Match));

    if(m == NULL)
    {
        return NULL;
    }

    m->id = id;

    m->joueur1 = NULL;
    m->joueur2 = NULL;
    m->vainqueur = NULL;

    m->gauche = NULL;
    m->droite = NULL;

    return m;
}

int match_complet(Match *m)
{
    if(m == NULL)
    {
        return 0;
    }

    return (m->joueur1 != NULL && m->joueur2 != NULL);
}

int match_termine(Match *m)
{
    if(m == NULL)
    {
        return 0;
    }

    return (m->vainqueur != NULL);
}

int enregistrer_vainqueur(Match *m, Competiteur *vainqueur)
{
    if(m == NULL || vainqueur == NULL)
    {
        return 0;
    }

    /* Les deux joueurs doivent être connus */
    if(!match_complet(m))
    {
        printf("Match incomplet.\n");
        return 0;
    }

    /* Résultat déjà enregistré */
    if(m->vainqueur != NULL)
    {
        printf("Le vainqueur est deja defini.\n");
        return 0;
    }

    /* Le vainqueur doit être un des deux joueurs */
    if(vainqueur != m->joueur1 &&
       vainqueur != m->joueur2)
    {
        printf("Ce joueur ne participe pas a ce match.\n");
        return 0;
    }

    m->vainqueur = vainqueur;

    printf("Vainqueur du match %d : %s\n",
           m->id,
           vainqueur->pseudo);

    return 1;
}

void afficher_match(Match *m)
{
    if(m == NULL)
    {
        return;
    }

    printf("\n===== MATCH %d =====\n", m->id);

    printf("Joueur 1 : ");

    if(m->joueur1 != NULL)
    {
        printf("%s\n", m->joueur1->pseudo);
    }
    else
    {
        printf("NON DEFINI\n");
    }

    printf("Joueur 2 : ");

    if(m->joueur2 != NULL)
    {
        printf("%s\n", m->joueur2->pseudo);
    }
    else
    {
        printf("NON DEFINI\n");
    }

    printf("Vainqueur : ");

    if(m->vainqueur != NULL)
    {
        printf("%s\n", m->vainqueur->pseudo);
    }
    else
    {
        printf("AUCUN\n");
    }
}

void detruire_match(Match *m)
{
    if(m == NULL)
    {
        return;
    }

    free(m);
}